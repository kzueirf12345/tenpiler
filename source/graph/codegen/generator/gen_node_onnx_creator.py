

def generate_node_onnx_creator_hpp(data, output_path, verbose=False):
    if verbose:
        print(f"Генерация хэдера функций создания узлов из onnx...")

    generated_code = \
        "// Сгенерированный файл\n" \
        "// Не редактировать вручную\n" \
        "\n" \
        "#pragma once\n" \
        "\n" \
        "#include <onnx/onnx-ml.pb.h>\n" \
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