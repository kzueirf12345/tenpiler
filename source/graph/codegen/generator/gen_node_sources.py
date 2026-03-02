import sys
from .utils import get_cpp_type, RIGHT_BORDER, join_with_leading_sep

def generate_op_impl(op_desc, verbose=False):
    name = op_desc["name"]
    constraints = op_desc.get("constraints", [])
    attributes = op_desc.get("attributes", [])
    
    def generate_enum_attrs():
        enum_attrs = [a for a in attributes if a["type"] == "enum"]
        
        if len(enum_attrs) == 0:
            return ""
        
        impl = \
            "#define RET_STR_TO_ENUM_(enum_name, field_name)".ljust(RIGHT_BORDER - 1) + "\\\n" \
            "    do {".ljust(RIGHT_BORDER + 1) + "\\\n" \
            "        if (str == #field_name) {".ljust(RIGHT_BORDER + 1) + "\\\n" \
           f"            return {name}::enum_name::field_name;".ljust(RIGHT_BORDER + 1) + "\\\n" \
            "        }".ljust(RIGHT_BORDER + 1) + "\\\n" \
            "    } while(false)\n" \
            "\n"
            
        for enum_attr in enum_attrs:
            enum_name = enum_attr["enum_name"]
            enum_values = enum_attr["enum_values"]
            
            impl += \
                f"{name}::{enum_name} {name}::Parse{enum_name}(std::string_view str) {{\n" \
                "\n"
            
            for enum_value in enum_values:
                impl += f"\tRET_STR_TO_ENUM_({enum_name}, {enum_value});\n"
                
            impl += "\n"
            
            impl += \
                f"\tutils::THROW(\"Unknown {enum_name} str\");\n" \
                "\n" \
                f"\treturn {name}::{enum_name}::{enum_values[0]};\n" \
                "}\n" \
                "\n"
            
        impl += \
            "#undef RET_STR_TO_ENUM_\n" \
            "\n"
        
        return impl
    
    if verbose:
        print(f"Генерация реализации класса {name}")
        
    create_args_str = \
        "\tstd::vector<std::string> inputs,\n" \
        "\tstd::vector<std::string> outputs"
        
    for attr in attributes:
        attr_type = get_cpp_type(attr)
        attr_name = attr["name"]
        
        create_args_str += ",\n" \
            f"\t{attr_type} {attr_name}"
            
    impl = \
        f"{name}::{name}(\n" \
      + create_args_str + "\n" \
        ")\t:\tmeta_({std::string(OnnxName), {}, {}})\n" \
        "{\n"
        
    impl += \
        "\tdetail::CheckSize(\n" \
        "\t\tinputs.size(),\n" \
        "\t\tMIN_INPUTS_SIZE,\n" \
        "\t\tMAX_INPUTS_SIZE,\n" \
        "\t\tstd::string(OnnxName),\n" \
        "\t\t\"input parametrs\"\n" \
        "\t);\n" \
        "\n" \
        "\tdetail::CheckSize(\n" \
        "\t\toutputs.size(),\n" \
        "\t\tMIN_OUTPUTS_SIZE,\n" \
        "\t\tMAX_OUTPUTS_SIZE,\n" \
        "\t\tstd::string(OnnxName),\n" \
        "\t\t\"outputs parametrs\"\n" \
        "\t);\n" \
        "\n"
        
    for inv in constraints:
        inv_type = inv["type"]
        
        impl += \
            f"\tif ({inv['condition']}) {{\n" \
        
        if inv_type == "check":
            impl += \
                "\t\tutils::THROW(\n" \
                "\t\t\t\"" + inv["description"] + "\"\n" \
                "\t\t);\n"
        elif inv_type == "set_default":
            impl += f"\t\t{inv['attr_name']} = {inv['value']};\n"
        else:
            print(f"Ошибка: Неизвестный тип инварианта: {inv_type}", file=sys.stderr)
            sys.exit(1)
            
        impl += \
            "\t}\n" \
            "\n"
    
    impl += \
        "\tmeta_.inputs = std::move(inputs);\n" \
        "\tmeta_.outputs = std::move(outputs);\n" \
    
    for attr in attributes:
        attr_name = attr["name"]
        impl += f"\t{attr_name}_ = std::move({attr_name});\n"
      
    impl += \
        "\n" \
        "}\n" \
        "\n"
    
    impl += generate_enum_attrs()
    
    return impl

def generate_cpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация сорцов...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#include \"graph/Node/Ops.hpp\"\n" \
        "\n" \
        "#include <cmath>\n" \
        "\n" \
        "#include \"graph/Node/utils.hpp\"\n" \
        "#include \"utils/common.hpp\"\n" \
        "\n"
    
    namespaces = data["namespace"].split("::")
    
    for namespace in namespaces:
        generated_code += f"namespace {namespace} {{\n"
    
    generated_code += "\n"
    
    operations = data["operations"]
    for op_num in range(len(operations)):
        operation = operations[op_num]
        generated_code += generate_op_impl(operation, verbose)
        
    for namespace in reversed(namespaces):
        generated_code += f"}} // namespace {namespace}\n"
    
    if verbose:
        print(f"Запись результата в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)
            
    if verbose:
        print(f"Сорцы записаны!")
       