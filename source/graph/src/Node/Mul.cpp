#include "graph/Node/Node.hpp"

#include "graph/Node/utils.hpp"

namespace tenpiler {
namespace graph {

static std::unique_ptr<Node> CreateMul(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

    return Mul::create(std::move(inputs), std::move(outputs));
}

std::unique_ptr<Node> Mul::create(std::vector<std::string> inputs, 
    std::vector<std::string> outputs
) {
    detail::CheckSize( inputs.size(),  INPUTS_SIZE, std::string(Name),  "input parametrs");
    detail::CheckSize(outputs.size(), OUTPUTS_SIZE, std::string(Name), "output parametrs");
    return std::unique_ptr<Mul>(new Mul(std::move(inputs), std::move(outputs)));
}

Mul::Mul(std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   Node(std::string(Name), std::move(inputs), std::move(outputs))
{}

void Mul::REGISTER_METHOD_NAME() {
    NodeFactory::Register(std::string(Name), CreateMul);
}

}
}