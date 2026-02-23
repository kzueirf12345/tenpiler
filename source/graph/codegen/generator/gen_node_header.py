from .utils import get_cpp_type, get_default_value

def generate_op_decl(op_desc, verbose=False):
    name = op_desc["name"]
    onnx_name = op_desc["onnx_name"]
    inputs = op_desc["inputs"]
    outputs = op_desc["outputs"]
    attributes = op_desc.get("attributes", [])
    
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
        attr_default = get_default_value(attr)
        
        create_args_str += ",\n" \
            f"\t\t{attr_type} {attr_name}"
            
        if attr_default is not None:
            create_args_str += f" = {attr_default}"
            
    decl += \
        "\n" \
        "public:\n" \
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
        print(f"Генерация хэдера...")

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
        
    if verbose:
        print(f"Хедер записан!")
