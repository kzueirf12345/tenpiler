#include <onnx/onnx-ml.pb.h>
#include <fstream>
#include <iostream>

int main() {
    onnx::ModelProto model;
    std::ifstream input("models/mnist-8.onnx", std::ios::binary);
    
    if (!model.ParseFromIstream(&input)) {
        std::cerr << "Failed to parse ONNX file" << std::endl;
        return 1;
    }

    const auto& graph = model.graph();
    std::cout << "Graph name: " << graph.name() << std::endl;
    std::cout << "Nodes count: " << graph.node_size() << std::endl;

    // Выводим типы первых 3 узлов
    for (int i = 0; i < std::min(3, graph.node_size()); ++i) {
        const auto& node = graph.node(i);
        std::cout << "Node " << i << ": " << node.op_type() 
                  << " | Inputs: " << node.input_size()
                  << " | Outputs: " << node.output_size() << std::endl;
    }
}