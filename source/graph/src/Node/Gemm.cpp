#include "graph/Node/Node.hpp"

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"
#include <cmath>

namespace tenpiler {
namespace graph {

static std::unique_ptr<Node> CreateGemm(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

    auto alpha = detail::GetFloatAttribute(onnx_node, "alpha");
    if (!alpha.has_value()) {
        alpha = 1;
    }

    auto betta = detail::GetFloatAttribute(onnx_node, "betta");
    if (!betta.has_value()) {
        betta = 1;
    }

    auto transA = detail::GetFloatAttribute(onnx_node, "transA");
    if (!transA.has_value()) {
        transA = 0;
    }

    auto transB = detail::GetFloatAttribute(onnx_node, "transB");
    if (!transB.has_value()) {
        transB = 0;
    }


    return Gemm::create(std::move(inputs), std::move(outputs), *alpha, *betta, *transA, *transB);
}

std::unique_ptr<Node> Gemm::create(
    std::vector<std::string> inputs, 
    std::vector<std::string> outputs,
    float alpha,
    float betta,
    bool transA,
    bool transB
) {
    detail::CheckSize(inputs.size(), MIN_INPUTS_SIZE, MAX_INPUTS_SIZE, std::string(Name), "input parametrs");
    detail::CheckSize(outputs.size(), OUTPUTS_SIZE, std::string(Name), "output parametrs");

    if (std::isnan(alpha)) {
        utils::THROW("Gemm alpha is NaN");
    }
    if (std::isnan(betta)) {
        utils::THROW("Gemm betta is NaN");
    }
    if (std::isinf(alpha)) {
        utils::THROW("Gemm alpha is Inf");
    }
    if (std::isinf(betta)) {
        utils::THROW("Gemm betta is Inf");
    }
    return std::unique_ptr<Gemm>(new Gemm(
        std::move(inputs), std::move(outputs), alpha, betta, transA, transB
    ));
}

Gemm::Gemm(std::vector<std::string> inputs, 
           std::vector<std::string> outputs,
           float alpha,
           float betta,
           bool transA,
           bool transB
)   :   Node(std::string(Name), std::move(inputs), std::move(outputs))
    ,   alpha_(alpha)
    ,   betta_(betta)
    ,   transA_(transA)
    ,   transB_(transB)
{}

void Gemm::REGISTER_METHOD_NAME() {
    NodeFactory::Register(std::string(Name), CreateGemm);
}


}
}