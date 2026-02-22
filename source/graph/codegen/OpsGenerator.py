import argparse
import sys
import json
from pathlib import Path


def parse_arguments():
    parser = argparse.ArgumentParser(
        description="Ops header generator",
    )

    parser.add_argument(
        "-i", "--input",
        type=str,
        required=False,
        default="./source/graph/codegen/OpsTableGen.json",
        metavar="FILE",
        help="Входной JSON файл с описанием классов операций "
             "(по умолчанию: ./source/graph/OpsTableGen.json)"
    )

    parser.add_argument(
        "-o", "--output",
        type=str,
        required=False,
        default="./source/graph/include/graph/Node/Ops.hpp",
        metavar="FILE",
        help="Выходной файл .hpp для сгенерированного кода (по умолчанию: "
             "./source/graph/include/graph/Node/GENERATE_Ops.hpp)"
    )
    
    parser.add_argument(
        "-v", "--verbose",
        action="store_true",
        help="Включить подробный вывод процесса генерации"
    )
    
    args = parser.parse_args()

    return args


def validate_paths(args):
    input_path = Path(args.input)
    output_path = Path(args.output)

    if not input_path.exists():
        print(f"Ошибка: Входной файл не найден: {input_path}", file=sys.stderr)
        sys.exit(1)

    if not input_path.is_file():
        print(f"Ошибка: Входной путь не является файлом: {input_path}", file=sys.stderr)
        sys.exit(1)

    if input_path.suffix != ".json":
        print(f"Предупреждение: Входной файл не имеет расширения .json", file=sys.stderr)

    if output_path.suffix != ".hpp":
        print(f"Предупреждение: Выходной файл не имеет расширения .hpp", file=sys.stderr)

    output_dir = output_path.parent
    if not output_dir.exists():
        print(f"Ошибка: Директория для выходного файла не существует: {output_dir}", file=sys.stderr)
        sys.exit(1)

    return input_path, output_path


def load_json(path, verbose=False):
    if verbose:
        print(f"Чтение JSON из: {path}")

    try:
        with open(path, "r", encoding="utf-8") as f:
            data = json.load(f)
        
        if verbose:
            print(f"Успешно загружено {len(data['operations'])} операций")
        
        return data
    except json.JSONDecodeError as e:
        print(f"Ошибка парсинга JSON: {e}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"Ошибка чтения файла: {e}", file=sys.stderr)
        sys.exit(1)

def generate_op_decl(op_desc, verbose=False):
    name = op_desc["name"]
    onnx_name = op_desc["onnx_name"]
    inputs = op_desc["inputs"]
    outputs = op_desc["outputs"]
    attributes = op_desc.get("attributes", [])
    
    def get_cpp_type(attr):
        SIMPLE_TYPES = {
            "uint8_t"   : "uint8_t",   
            "uint16_t"  : "uint16_t",
            "uint32_t"  : "uint32_t", 
            "uint64_t"  : "uint64_t",
            "int8_t"    : "int8_t",     
            "int16_t"   : "int16_t", 
            "int32_t"   : "int32_t",   
            "int64_t"   : "int64_t",
            "float"     : "float", 
            "double"    : "double",
            "bool"      : "bool", 
            "string"    : "std::string",
        }
        
        def map_simple(type_name):
            return SIMPLE_TYPES.get(type_name, type_name)
        
        raw_type = attr["type"]
        
        if raw_type.startswith("vector<") and raw_type.endswith(">"):
            inner_type = raw_type[7:-1]
            return f"std::vector<{map_simple(inner_type)}>"
        
        if raw_type == "enum":
            enum_name = attr.get("enum_name")
            return f"{name}::{enum_name}"
        
        return map_simple(raw_type)
    
    def format_default_value(attr):
        value = attr["default"]
        if value is None:
            return None
        if attr["type"] == "enum":
            return f"{attr['enum_name']}::{value}"
        if attr["type"] == "string":
            return f'"{value}"'
        if attr["type"].startswith("vector<"):
            return "{}" if value == "[]" else value
        return str(value)
    
    def generate_enum_attrs():
        enum_attrs = [a for a in attributes if a["type"] == "enum"]
        
        if len(enum_attrs) == 0:
            return ""
         
        decl = \
            "public:\n" \
            "\n"
        
        for enum_attr in enum_attrs:
            enum_name = enum_attr["enum_name"]
            enum_values = enum_attr["enum_values"]
            
            decl += f"\t enum class {enum_name} {{\n"
            
            for enum_value in enum_values:
                decl += f"\t\t{enum_value},\n"
            
            decl += \
                "\t};\n" \
                "\n"
                
        for enum_attr in enum_attrs:
            enum_name = enum_attr["enum_name"]
            decl += f"\tstatic {name}::{enum_name} Parse{enum_name}(std::string_view str);\n"
        
        decl += "\n"
        
        return decl
        
    if verbose:
         print(f"Генерация описания класса {name}")
        
    decl = \
        f"class {name} {{\n" \
        "\n" \
        "private:\n" \
        "\n" \
        "\tNodeMeta meta_;\n" \
        "\n" \
        "public:\n" \
        "\n" \
        "\t[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }\n" \
        "\n" \
        f"\tstatic constexpr std::string_view OnnxName = \"{onnx_name}\";\n" \
        "\n" \
        f"\tstatic constexpr size_t MIN_INPUTS_SIZE  = {inputs['min']};\n" \
        f"\tstatic constexpr size_t MAX_INPUTS_SIZE  = {inputs['max']};\n" \
        f"\tstatic constexpr size_t MIN_OUTPUTS_SIZE = {outputs['min']};\n" \
        f"\tstatic constexpr size_t MAX_OUTPUTS_SIZE = {outputs['max']};\n" \
        "\n"
    
    decl += generate_enum_attrs()
        
    create_args_str = \
        "\t\tstd::vector<std::string> inputs,\n" \
        "\t\tstd::vector<std::string> outputs" 
        
    for attr in attributes:
        attr_type = get_cpp_type(attr)
        attr_name = attr["name"]
        attr_default = format_default_value(attr)
        
        create_args_str += ",\n" \
            f"\t\t{attr_type} {attr_name}"
            
        if attr_default is not None:
            create_args_str += f" = {attr_default}"
            
    decl += \
        "\n" \
        "public:\n" \
        "\n" \
        f"\tstatic {name} create(\n" \
      + create_args_str + "\n"\
        "\t);\n" \
        "\n" \
        "private:\n" \
        "\n" \
        f"\t{name}(\n" \
      + create_args_str + "\n" \
        "\t);\n" \
        "\n"
            
    if len(attributes):
        decl += \
            "private:\n" \
            "\n"
            
        for attr in attributes:
            attr_type = get_cpp_type(attr)
            attr_name = attr["name"]
            
            decl += f"\t{attr_type} {attr_name}_;\n"
        
        decl += "\n"
    
    decl += "};\n"
        
    return decl
        
def generate_hpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация кода...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#pragma once\n" \
        "\n" \
        "#include <string_view>\n" \
        "#include <string>\n" \
        "#include <vector>\n" \
        "#include <cstdint>\n" \
        "\n" \
        "#include \"graph/Node/NodeMeta.hpp\"\n" \
        "\n"
    
    namespaces = data["namespace"].split("::")
    
    for namespace in namespaces:
        generated_code += f"namespace {namespace} {{\n"
    
    generated_code += "\n"
    
    operations = data["operations"]
    for op_num in range(len(operations)):
        if verbose:
            print(f"{op_num + 1}: ", end="")
        generated_code += generate_op_decl(operations[op_num], verbose)
        generated_code += "\n"
    
    for namespace in reversed(namespaces):
        generated_code += f"}} // namespace {namespace}\n"

    if verbose:
        print(f"Запись результата в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)


if __name__ == "__main__":
    args = parse_arguments()

    input_path, output_path = validate_paths(args)

    data = load_json(input_path, args.verbose)

    generate_hpp(data, output_path, args.verbose)

    if args.verbose:
        print("Генерация завершена успешно!")