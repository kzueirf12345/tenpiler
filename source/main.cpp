#include <cstdlib>
#include <fstream>
#include <iostream>

#include <onnx/onnx-ml.pb.h>
#include <stdexcept>

#include "graph/Graph.hpp"
#include "utils/concole.hpp"

//TODO generator onnx files
//TODO graphiz
//TODO backtrace in THROW
//TODO соси хуйка (by твой сокомандник Арсений Шелонини Б01-411)

int main() try {
    onnx::ModelProto model;
    std::ifstream input("models/mnist-8.onnx", std::ios::binary);
    
    if (!model.ParseFromIstream(&input)) {
        std::cerr << "Failed to parse ONNX file" << std::endl;
        return EXIT_FAILURE;
    }

    const auto& onnx_graph = model.graph();
    std::cout << "Graph name: " << onnx_graph.name() << std::endl;
    std::cout << "Nodes count: " << onnx_graph.node_size() << std::endl;

    for (int i = 0; i < std::min(10, onnx_graph.node_size()); ++i) {
        const auto& node = onnx_graph.node(i);
        std::cout << "Node " << i << ": " << node.op_type() 
                  << " | Inputs: " << node.input_size()
                  << " | Outputs: " << node.output_size() << std::endl;
        std::cerr << "output: ";
        for (const auto& elem : node.output()) {
            std::cerr << elem << "";
        }
        std::cerr << std::endl;
    }

    const tenpiler::graph::Graph graph(onnx_graph);

    for (size_t i = 0; i < std::min(10ul, graph.getNodes().size()); ++i) {
        const auto& node = graph.getNodes()[i];
        std::cout << "Node " << i << ": " << node->sayMyName() 
                  << " | Inputs: " << node->getInputs().size()
                  << " | Outputs: " << node->getOutputs().size() << std::endl;
        std::cerr << "output: ";
        for (const auto& elem : node->getOutputs()) {
            std::cerr << elem << "";
        }
        std::cerr << std::endl;
    }
    
    return EXIT_SUCCESS;
}
catch(const std::runtime_error& e) {
    std::cerr <<  RED_TEXT("!!!EXCEPTION!!\n") << e.what() << std::endl;
}