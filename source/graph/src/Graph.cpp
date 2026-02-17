#include "graph/Graph.hpp"
#include "graph/NodeFactory.hpp"

namespace tenpiler {
namespace graph {

Graph::Graph(const onnx::GraphProto& onnx_graph)
{
    const auto& onnx_input = onnx_graph.input();
    const auto& onnx_output = onnx_graph.output();
    const auto& onnx_internal = onnx_graph.initializer();

    input_.reserve(onnx_input.size());
    output_.reserve(onnx_output.size());
    tensors_.reserve(onnx_input.size() + onnx_output.size() + onnx_internal.size());

    for (const auto& onnx_input_tensor: onnx_input)
    {
        const Tensor input_tensor(onnx_input_tensor);
        const std::string input_tensor_name(input_tensor.name);
        input_.push_back(input_tensor_name);
        tensors_.emplace(std::move(input_tensor_name), std::move(input_tensor));
    }

    for (const auto& onnx_output_tensor: onnx_output)
    {
        const Tensor output_tensor(onnx_output_tensor);
        const std::string output_tensor_name(output_tensor.name);
        output_.push_back(output_tensor_name);
        tensors_.emplace(std::move(output_tensor_name), std::move(output_tensor));
    }

    for (const auto& onnx_internal_tensor: onnx_internal)
    {
        const Tensor internal_tensor(onnx_internal_tensor);
        const std::string internal_tensor_name(internal_tensor.name);
        tensors_.emplace(std::move(internal_tensor_name), std::move(internal_tensor));
    }

    const auto& onnx_nodes = onnx_graph.node();

    nodes_.reserve(onnx_nodes.size());

    for (const auto& onnx_node: onnx_nodes) {
        nodes_.push_back(NodeFactory::Create(onnx_node));
    }
}

const std::vector<std::unique_ptr<Node>>& Graph::getNodes() const noexcept {
    return nodes_;
}
const std::unordered_map<std::string, Tensor>& Graph::getTensors() const noexcept {
    return tensors_;
}
const std::vector<std::string>& Graph::getInputs() const noexcept {
    return input_;
}
const std::vector<std::string>& Graph::getOutputs() const noexcept {
    return output_;
}
const Tensor& Graph::getTensor(const std::string& name) const noexcept {
    return tensors_.at(name);
}

}
}