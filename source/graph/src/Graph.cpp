#include "graph/Graph.hpp"

#include <onnx/onnx-ml.pb.h>

#include "graph/Tensor.hpp"
#include "GraphOnnxCreator/GraphOnnxCreator.hpp"
#include "utils/common.hpp"

namespace tenpiler {
namespace graph {

Graph::Graph() = default;

Graph::Graph(
    std::unordered_map<std::string, Tensor> tensors,
    std::vector<Node> nodes,
    std::vector<std::string> input,
    std::vector<std::string> output
)   :   tensors_ (std::move(tensors)) 
    ,   nodes_   (std::move(nodes))
    ,   input_   (std::move(input))
    ,   output_  (std::move(output))
{}


void Graph::LoadFromOnnx(std::istream& input_onnx)
{
    if (!input_onnx.good()) {
        utils::THROW("Input stream is in a bad state before parsing");
    }

    onnx::ModelProto model;

    if (!model.ParseFromIstream(&input_onnx)) {
        utils::THROW("Failed to parse ONNX file");
    }

    const auto& onnx_graph = model.graph();

    *this = onnx_parse::CreateGraph(onnx_graph);
}

const std::vector<Node>& Graph::getNodes()                          const noexcept {
    return nodes_;
}

const std::unordered_map<std::string, Tensor>& Graph::getTensors()  const noexcept {
    return tensors_;
}

const std::vector<std::string>& Graph::getInputs()                  const noexcept {
    return input_;
}

const std::vector<std::string>& Graph::getOutputs()                 const noexcept {
    return output_;
}

const Tensor& Graph::getTensor(const std::string& name) const {
    return tensors_.at(name);
}

}
}