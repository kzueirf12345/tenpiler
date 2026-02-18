#include "graph/Node/Node.hpp"

#include "graph/Node/utils.hpp"

namespace tenpiler {
namespace graph {

static std::unique_ptr<Node> CreateMatMul(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

    return MatMul::create(std::move(inputs), std::move(outputs));
}

std::unique_ptr<Node> MatMul::create(std::vector<std::string> inputs, 
    std::vector<std::string> outputs
) {
    detail::CheckSize( inputs.size(),  INPUTS_SIZE, std::string(OnnxName),  "input parametrs");
    detail::CheckSize(outputs.size(), OUTPUTS_SIZE, std::string(OnnxName), "output parametrs");
    return std::unique_ptr<MatMul>(new MatMul(std::move(inputs), std::move(outputs)));
}

MatMul::MatMul(std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   Node(std::string(OnnxName), std::move(inputs), std::move(outputs))
{}

void MatMul::REGISTER_METHOD_NAME() {
    NodeFactory::Register(std::string(OnnxName), CreateMatMul);
}

}
}