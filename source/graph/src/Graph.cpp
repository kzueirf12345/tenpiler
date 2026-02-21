#include <memory>
#include <onnx/onnx-ml.pb.h>

#include "graph/Graph.hpp"
#include "graph/Tensor.hpp"
#include "TensorOnnxCreator/TensorOnnxCreator.hpp"

#include "NodeOnnxCreator/NodeFactory.hpp"
#include "utils/common.hpp"


namespace tenpiler {
namespace graph {

struct Graph::Impl {

    void BuildGraph(std::istream& input_onnx);

    void BuildTensor(const onnx::ValueInfoProto& onnx_tensor);
    void BuildTensor(const onnx::TensorProto&    onnx_tensor);

    std::unordered_map<std::string, Tensor> tensors;
    
    std::vector<Node> nodes;
    
    std::vector<std::string> input;
    std::vector<std::string> output;

};

void Graph::Impl::BuildGraph(std::istream& input_onnx)
{
    if (!input_onnx.good())
    {
        throw std::runtime_error("Input stream is in a bad state before parsing");
    }

    onnx::ModelProto model;

    if (!model.ParseFromIstream(&input_onnx)) {
        utils::THROW("Failed to parse ONNX file");
    }

    const auto& onnx_graph = model.graph();

    const auto& onnx_input    = onnx_graph.input();
    const auto& onnx_output   = onnx_graph.output();
    const auto& onnx_internal = onnx_graph.initializer();

    input  .reserve(onnx_input .size());
    output .reserve(onnx_output.size());
    tensors.reserve(onnx_input .size() + onnx_output.size() + onnx_internal.size());

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

    const auto& onnx_nodes = onnx_graph.node();

    nodes.reserve(onnx_nodes.size());

    for (const auto& onnx_node: onnx_nodes) {
        nodes.push_back(onnx_parse::NodeFactory::Create(onnx_node));
    }
}


Graph::Graph() : pimpl_(std::make_unique<Impl>()) {}

Graph::Graph(const Graph& other) 
    : pimpl_(other.pimpl_ ? std::make_unique<Impl>(*other.pimpl_) : nullptr) 
{}

Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        Graph temp(other);
        
        std::swap(pimpl_, temp.pimpl_);
    }
    return *this;
}

Graph::~Graph()                           = default;
Graph::Graph(Graph&&)            noexcept = default;
Graph& Graph::operator=(Graph&&) noexcept = default;

void Graph::LoadFromOnnx(std::istream& input_onnx)
{
    pimpl_->BuildGraph(input_onnx);
}

const std::vector<Node>& Graph::getNodes()                          const noexcept {
    return pimpl_->nodes;
}

const std::unordered_map<std::string, Tensor>& Graph::getTensors()  const noexcept {
    return pimpl_->tensors;
}

const std::vector<std::string>& Graph::getInputs()                  const noexcept {
    return pimpl_->input;
}

const std::vector<std::string>& Graph::getOutputs()                 const noexcept {
    return pimpl_->output;
}

const Tensor& Graph::getTensor(const std::string& name) const {
    return pimpl_->tensors.at(name);
}

}
}