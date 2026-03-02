

def generate_node_attr_hpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация хэдера для геттеров атрибутов...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#pragma once\n" \
        "\n" \
        "#include <any>\n" \
        "#include <string>\n" \
        "\n" \
        "#include \"graph/Node/Ops.hpp\"\n" \
        "\n"
    
    namespaces = data["namespace"].split("::")
    
    for namespace in namespaces:
        generated_code += f"namespace {namespace} {{\n"
    
    generated_code += "\n"
    
    operations = data["operations"]
    
    for op_num in range(len(operations)):
        op = operations[op_num]
        generated_code += f"std::any GetAttribute(const {op['name']}& node, const std::string& name);\n"
    
    generated_code += "\n"
    
    for namespace in reversed(namespaces):
        generated_code += f"}} // namespace {namespace}\n"

    if verbose:
        print(f"Запись результата в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)

    if verbose:
        print(f"Хедер записан!")
        
def generate_node_attr_impl(op_desc, verbose=False):
    name = op_desc["name"]
    attributes = op_desc["attributes"]
         
    impl = \
        f"std::any GetAttribute(const {name}& node, const std::string& name) {{\n"\
            
    if len(attributes) == 0:
        impl += \
            "\t(void)node;\n" \
            "\t(void)name;\n"

    impl += "\n"
        
    for attr in attributes:
        attr_name = attr["name"]
        impl += f"\tif (name == \"{attr_name}\") return node.get_{attr_name}();\n"
        
    impl += \
        "\treturn {};\n" \
        "}\n\n"
    
    return impl
        
def generate_node_attr_cpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация реализаций функци гета атрибутов...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#include \"graph/Node/" + output_path.stem + ".hpp\"\n" \
        "\n"
    
    namespaces = data["namespace"].split("::")
    
    for namespace in namespaces:
        generated_code += f"namespace {namespace} {{\n"
    
    generated_code += "\n"
    
    operations = data["operations"]
    
    for op_num in range(len(operations)):
        op = operations[op_num]
        generated_code += generate_node_attr_impl(op, verbose)
    
    for namespace in reversed(namespaces):
        generated_code += f"}} // namespace {namespace}\n"

    if verbose:
        print(f"Запись результата в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)

    if verbose:
        print(f"Сорец записан!")