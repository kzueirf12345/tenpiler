from .utils import get_cpp_type

def generate_node_dumb_hpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация хэдера для дампа...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#pragma once\n" \
        "\n" \
        "#include \"Ops.hpp\"\n" \
        "\n"
    
    namespaces = data["namespace"].split("::")
    namespaces.append("dump")
    
    for namespace in namespaces:
        generated_code += f"namespace {namespace} {{\n"
    
    generated_code += "\n"
    
    operations = data["operations"]
    
    for op_num in range(len(operations)):
        op = operations[op_num]
        generated_code += f"std::string GetDot(const {op['name']}& n);\n"
    
    generated_code += "\n"
    
    for namespace in reversed(namespaces):
        generated_code += f"}} // namespace {namespace}\n"

    if verbose:
        print(f"Запись результата в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)

    if verbose:
        print(f"Хедер записан!")
        
def generate_node_dumb_impl(op_desc, verbose=False):
    name = op_desc["name"]
    attributes = op_desc["attributes"]
         
    impl = \
        f"std::string GetDot(const {name}& n){{\n" \
        f"\treturn " \
        f"std::to_string({name}::MIN_INPUTS_SIZE) + \"-\" + " \
        f"std::to_string({name}::MAX_INPUTS_SIZE) + \" | {{{{\" + " \
        f"n.meta().op_type + " \
            
    for attr in attributes:
        attr_name = attr["name"]
        attr_type = attr["type"]
        
        if attr_type == "enum":
            attr_type = attr["enum_name"]
            
        attr_type = attr_type.replace("<", "\\\\<").replace(">", "\\\\>")
            
        impl += f"\" | {attr_type} {attr_name}\" + "
            
    impl += \
        f"\" }}}} | \" + " \
        f"std::to_string({name}::MIN_OUTPUTS_SIZE) + \"-\" + " \
        f"std::to_string({name}::MAX_OUTPUTS_SIZE)" \
        ";\n" \
        "}\n" \
        "\n"
    
    return impl
        
def generate_node_dumb_cpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация хэдера для дампа...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#include \"graph/Node/OpsDumb.hpp\"\n" \
        "\n"
    
    namespaces = data["namespace"].split("::")
    namespaces.append("dump")
    
    for namespace in namespaces:
        generated_code += f"namespace {namespace} {{\n"
    
    generated_code += "\n"
    
    operations = data["operations"]
    
    for op_num in range(len(operations)):
        op = operations[op_num]
        generated_code += generate_node_dumb_impl(op, verbose)
    
    for namespace in reversed(namespaces):
        generated_code += f"}} // namespace {namespace}\n"

    if verbose:
        print(f"Запись результата в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)

    if verbose:
        print(f"Хедер записан!")