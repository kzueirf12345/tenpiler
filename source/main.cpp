#include <cstdlib>
#include <fstream>
#include <iostream>

#include <stdexcept>

#include "RLogSU/logger.hpp"

#include "graph/Graph.hpp"
#include "graph/Dumber.hpp"
#include "utils/concole.hpp"

#include <onnx/onnx-ml.pb.h>

//TODO graphiz
//TODO соси хуйка (by твой сокомандник Арсений Шелонини Б01-411)
//TODO switch uint to int
//TODO downlaoad tests and test
//TODO update README

int main() try {
    onnx::ModelProto model;
    // std::ifstream input("models/mnist-8.onnx", std::ios::binary);
    std::ifstream input1("models/tensor_compiler_test.onnx", std::ios::binary);
    
    if (!model.ParseFromIstream(&input1)) {
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
            std::cerr << elem << " ";
        }
        std::cerr << "\ninput: ";
        for (const auto& elem : node.input()) {
            std::cerr << elem << " ";
        }
        std::cerr << std::endl;
    }

    std::cout << std::endl << std::endl;

    std::ifstream input2("models/tensor_compiler_test.onnx", std::ios::binary);
    tenpiler::graph::Graph graph;
    graph.LoadFromOnnx(input2);

    for (size_t i = 0; i < std::min(10ul, graph.getNodes().size()); ++i) {
        const auto& node = graph.getNodes()[i];
        std::cout << "Node " << i << ": " << node.sayMyName() 
                  << " | Inputs: " << node.getInputs().size()
                  << " | Outputs: " << node.getOutputs().size() << std::endl;
        std::cerr << "output: ";
        for (const auto& elem : node.getOutputs()) {
            std::cerr << elem << " ";
        }
        std::cerr << "\ninput: ";
        for (const auto& elem : node.getInputs()) {
            std::cerr << elem << " ";
        }
        std::cerr << std::endl;
    }
    
    std::cerr << "All tensors:\n";
    for (const auto& [name, tensor] : graph.getTensors())
    {
        std::cerr << name << " ";
    }
    std::cerr << std::endl;


    std::cout << std::endl << std::endl << "Graph test" << std::endl;

    for (size_t i = 0; i < std::min(10ul, graph.getNodes().size()); ++i) {
        const auto& node = graph.getNodes()[i];
        std::cout << node.getDot() << std::endl;
    }

    RLSU_DUMP(tenpiler::graph::dump::GraphDumb(graph));

    return EXIT_SUCCESS;
}
catch(const std::logic_error& e) {
    std::cerr <<  RED_TEXT("!!!LOGIC_EXCEPTION!!\n") << e.what() << std::endl;
}
catch(const std::runtime_error& e) {
    std::cerr <<  RED_TEXT("!!!RUNTIME_EXCEPTION!!\n") << e.what() << std::endl;
}
catch(const std::exception& e) {
    std::cerr <<  RED_TEXT("!!!EXCEPTION!!\n") << e.what() << std::endl;
}
catch(...) {
    std::cerr << RED_TEXT("Something went wrong!!!") << std::endl;
}