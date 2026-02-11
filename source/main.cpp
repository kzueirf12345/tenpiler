#include <cstdlib>
#include <fstream>
#include <iostream>

#include <onnx/onnx-ml.pb.h>

int main() {
    onnx::ModelProto model;
    std::ifstream input("models/mnist-8.onnx", std::ios::binary);
    
    if (!model.ParseFromIstream(&input)) {
        std::cerr << "Failed to parse ONNX file" << std::endl;
        return EXIT_FAILURE;
    }

    const auto& graph = model.graph();
    std::cout << "Graph name: " << graph.name() << std::endl;
    std::cout << "Nodes count: " << graph.node_size() << std::endl;

    for (int i = 0; i < std::min(10, graph.node_size()); ++i) {
        const auto& node = graph.node(i);
        std::cout << "Node " << i << ": " << node.op_type() 
                  << " | Inputs: " << node.input_size()
                  << " | Outputs: " << node.output_size() << std::endl;
    }
    

    return EXIT_SUCCESS;
}