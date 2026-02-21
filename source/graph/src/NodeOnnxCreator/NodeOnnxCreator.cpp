#include <onnx/onnx-ml.pb.h>

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"
#include "graph/Node/Node.hpp"

namespace tenpiler {
namespace graph {
namespace onnx_parse {


Node CreateAdd(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

    return Add::create(std::move(inputs), std::move(outputs));
}

Node CreateConv(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());
    
    auto kernel_shape = detail::GetIntsAttribute(onnx_node, "kernel_shape");
    if (!kernel_shape.has_value()) {
        utils::THROW(
            "tenpiler::graph::Conv can't create from onnx_node without kernel shape"
        );
    }

    auto strides = detail::GetIntsAttribute(onnx_node, "strides");
    if (!strides.has_value()) {
        strides = std::vector<uint64_t>(kernel_shape->size(), 1);
    }
    
    auto dilations = detail::GetIntsAttribute(onnx_node, "dilations");
    if (!dilations.has_value()) {
        dilations = std::vector<uint64_t>(kernel_shape->size(), 1);
    }

    auto groups = detail::GetIntAttribute(onnx_node, "group");
    if (!groups.has_value()) {
        groups = 1;
    }

    const auto auto_pad_str = detail::GetStringAttribute(onnx_node, "auto_pad");
    const auto pads_opt = detail::GetIntsAttribute(onnx_node, "pads");
    Conv::PadType auto_pad = Conv::PadType::NotSet;
    std::vector<uint64_t> pads{};

    if (auto_pad_str.has_value()) {
        auto_pad = Conv::ParseAutoPad(*auto_pad_str);
    }

    if (pads_opt.has_value()) {
        pads = std::move(*pads_opt);
    }
    else if (auto_pad == Conv::PadType::NotSet) {
        pads = std::vector<uint64_t>(kernel_shape->size() * 2, 0);
    } 
    else {
        assert(pads.empty());
    }

    return Conv::create(std::move(inputs), std::move(outputs), std::move(*kernel_shape), 
        std::move(*strides), std::move(pads), std::move(*dilations), *groups, auto_pad
    );
}

Node CreateGemm(const onnx::NodeProto& onnx_node) {
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

Node CreateMatMul(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

    return MatMul::create(std::move(inputs), std::move(outputs));
}

Node CreateMul(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

    return Mul::create(std::move(inputs), std::move(outputs));
}

Node CreateRelu(const onnx::NodeProto& onnx_node) {
    std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
    std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

    return Relu::create(std::move(inputs), std::move(outputs));
}


}
}
}