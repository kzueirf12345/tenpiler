#include "GraphOnnxCreator.hpp"

#include <onnx/onnx-ml.pb.h>

#include "TensorOnnxCreator/TensorOnnxCreator.hpp"
#include "NodeOnnxCreator/NodeFactory.hpp"
#include "graph/Graph.hpp"


namespace tenpiler {
namespace graph {
namespace onnx_parse {

Graph CreateGraph(const onnx::GraphProto& onnx_graph) {
    const auto& onnx_input      = onnx_graph.input();
    const auto& onnx_output     = onnx_graph.output();
    const auto& onnx_internal   = onnx_graph.initializer();
    const auto& onnx_value_info = onnx_graph.value_info();
    const auto& onnx_nodes      = onnx_graph.node();

    std::unordered_map<std::string, Tensor> tensors;
    
    std::vector<Node> nodes;
    
    std::vector<std::string> input;
    std::vector<std::string> output;

    input  .reserve(onnx_input .size());
    output .reserve(onnx_output.size());
    tensors.reserve(onnx_input .size() + onnx_output.size() + onnx_internal.size() + onnx_value_info.size());
    nodes  .reserve(onnx_nodes .size());

    for (const auto& onnx_input_tensor: onnx_input)
    {
        Tensor input_tensor = onnx_parse::CreateTensor(onnx_input_tensor);
        std::string input_tensor_name(input_tensor.name);
        input.push_back(input_tensor_name);
        tensors.emplace(std::move(input_tensor_name), std::move(input_tensor));
    }

    for (const auto& onnx_output_tensor: onnx_output)
    {
        Tensor output_tensor = onnx_parse::CreateTensor(onnx_output_tensor);
        std::string output_tensor_name(output_tensor.name);
        output.push_back(output_tensor_name);
        tensors.emplace(std::move(output_tensor_name), std::move(output_tensor));
    }

    for (const auto& onnx_internal_tensor: onnx_internal)
    {
        Tensor internal_tensor = onnx_parse::CreateTensor(onnx_internal_tensor);
        std::string internal_tensor_name(internal_tensor.name);
        tensors.emplace(std::move(internal_tensor_name), std::move(internal_tensor));
    }

    for (const auto& onnx_val_info: onnx_value_info)
    {
        Tensor val_tensor = onnx_parse::CreateTensor(onnx_val_info);
        std::string val_tensor_name(val_tensor.name);
        tensors.emplace(std::move(val_tensor_name), std::move(val_tensor));
    }

for (const auto& onnx_node: onnx_nodes) {
        nodes.push_back(onnx_parse::NodeFactory::Create(onnx_node));

        for (const auto& out_name : onnx_node.output()) {
            if (tensors.find(out_name) == tensors.end()) {
                Tensor dummy_tensor;
                dummy_tensor.name = out_name;
                dummy_tensor.type = Tensor::Type::Unknown;
                tensors.emplace(out_name, std::move(dummy_tensor));
            }
        }
    }

    return Graph(std::move(tensors), std::move(nodes), std::move(input), std::move(output));
}

}
}
}