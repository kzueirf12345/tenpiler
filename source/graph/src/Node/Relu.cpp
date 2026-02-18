#include "graph/Node/Node.hpp"

#include "graph/Node/utils.hpp"

namespace tenpiler {
namespace graph {

static std::unique_ptr<Node> CreateRelu(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

    return Relu::create(std::move(inputs), std::move(outputs));
}

std::unique_ptr<Node> Relu::create(std::vector<std::string> inputs, 
    std::vector<std::string> outputs
) {
    detail::CheckSize( inputs.size(),  INPUTS_SIZE, std::string(OnnxName),  "input parametrs");
    detail::CheckSize(outputs.size(), OUTPUTS_SIZE, std::string(OnnxName), "output parametrs");
    return std::unique_ptr<Relu>(new Relu(std::move(inputs), std::move(outputs)));
}

Relu::Relu(std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   Node(std::string(OnnxName), std::move(inputs), std::move(outputs))
{}

void Relu::REGISTER_METHOD_NAME() {
    NodeFactory::Register(std::string(OnnxName), CreateRelu);
}

}
}