from .utils import join_with_leading_sep, get_default_value, get_attr_name, get_cpp_type


def generate_node_onnx_creator_hpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация хэдера функций создания узлов из onnx...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#pragma once\n" \
        "\n" \
        "#include <onnx/onnx_pb.h>\n" \
        "\n" \
        "#include \"graph/Node/Node.hpp\"\n" \
        "\n"
    
    namespaces = data["namespace"].split("::")
    namespaces.append("onnx_parse")
    
    for namespace in namespaces:
        generated_code += f"namespace {namespace} {{\n"
    
    generated_code += "\n"
    
    operations = data["operations"]
    
    for op_num in range(len(operations)):
        op = operations[op_num]
        generated_code += f"Node Create{op['name']}(const onnx::NodeProto& onnx_node);\n"
    
    generated_code += "\n"
    
    for namespace in reversed(namespaces):
        generated_code += f"}} // namespace {namespace}\n"

    if verbose:
        print(f"Запись результата в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)

    if verbose:
        print(f"Хедер записан!")
        
def generate_op_table_hpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация вспомогательного хэдера для автоматической инициалиации реестра нод...")
        
    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n"
        
    operations = data["operations"]
            
    for op_num in range(len(operations)):
        op = operations[op_num]
        generated_code += f"{{{op['name']}::OnnxName, Create{op['name']}}},\n"
            
    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)

    if verbose:
        print(f"Хедер записан!")
        
def generate_op_create_impl(op, verbose=False):
    name = op["name"]
    onnx_name = op["onnx_name"]
    inputs = op["inputs"]
    outputs = op["outputs"]
    attributes = op.get("attributes", [])
    
    impl = \
        f"Node Create{name}(const onnx::NodeProto& onnx_node) {{\n" \
        "\tstd::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());\n" \
        "\tstd::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());\n" \
        "\n"
        
    for attr in attributes:
        attr_name = attr["name"]
        attr_type = attr["type"]
        attr_default = get_default_value(attr)
        attr_cpp_type = get_cpp_type(attr)
        
        impl += \
            f"\tconst auto {attr_name}_opt = detail::Get{get_attr_name(attr_type)}Attribute" \
                f"(onnx_node, \"{attr_name}\");\n"
            
        if attr_default is None:
            impl += \
                f"\tif (!{attr_name}_opt.has_value()) {{\n" \
                "\t\tutils::THROW(\n" \
                f"\t\t\t\"{name} can't create from onnx_node without {attr_name}\"\n" \
                "\t\t);\n" \
                "\t}\n" \
                
            if attr_type == "enum":
                impl += \
                    f"\tconst {attr_cpp_type} {attr_name} = " \
                        f"{name}::Parse{attr_cpp_type}(*{attr_name}_opt);\n"    
            else:
                impl += f"\tconst {attr_cpp_type} {attr_name} = *{attr_name}_opt;\n"  
            
              
            
        else:
            impl += \
                f"\t{(name + '::' if attr_type == 'enum' else '') + attr_cpp_type} " \
                f"{attr_name} = {(name + '::' if attr_type == 'enum' else '') + attr_default};\n" \
                f"\tif ({attr_name}_opt.has_value()) {{\n"
                
            if attr_type == "enum":
                impl += f"\t\t{attr_name} = {name}::Parse{attr_cpp_type}(*{attr_name}_opt);\n"    
            else:
                impl += f"\t\t{attr_name} = *{attr_name}_opt;\n"    
            
            impl += \
                "\t}\n"
                
        impl += "\n"    
    
    impl += \
        f"\treturn {name}(\n" \
        "\t\tstd::move(inputs),\n" \
        "\t\tstd::move(outputs)" \
      + join_with_leading_sep([f"std::move({attr['name']})" for attr in attributes], ",\n\t\t") + "\n" \
        "\t);\n" \
        "}\n"
        
    return impl
    
        
def generate_node_onnx_creator_cpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация функций создания узлов из onnx...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#include \"NodeOnnxCreator.hpp\"\n" \
        "\n" \
        "#include <string>\n" \
        "\n" \
        "#include <onnx/onnx_pb.h>\n" \
        "\n" \
        "#include \"graph/Node/utils.hpp\"\n" \
        "#include \"utils/common.hpp\"\n" \
        "\n"
    
    namespaces = data["namespace"].split("::")
    namespaces.append("onnx_parse")
    
    for namespace in namespaces:
        generated_code += f"namespace {namespace} {{\n"
    
    generated_code += "\n"
    
    operations = data["operations"]
    
    for op_num in range(len(operations)):
        op = operations[op_num]
        generated_code += generate_op_create_impl(op, verbose)
        generated_code += "\n"
    
    for namespace in reversed(namespaces):
        generated_code += f"}} // namespace {namespace}\n"

    if verbose:
        print(f"Запись результата в: {output_path}")

    with open(output_path, "w", encoding="utf-8") as f:
        f.write(generated_code)

    if verbose:
        print(f"Сорец записан!")