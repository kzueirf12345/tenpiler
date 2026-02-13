#include "graph/Node/Node.hpp"

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"

namespace tenpiler {
namespace graph {

Conv::PadType Conv::ParseAutoPad(std::string_view str_auto_pad) {
    if (str_auto_pad == "NOTSET") {
        return Conv::PadType::NotSet;
    }
    if (str_auto_pad == "SAME_UPPER") {
        return Conv::PadType::SameUpper;
    }
    if (str_auto_pad == "SAME_LOWER") {
        return Conv::PadType::SameLower;
    }
    if (str_auto_pad == "VALID") {
        return Conv::PadType::Valid;
    }

    utils::THROW("Unknown auto_pad str");

    return Conv::PadType::NotSet;
}

static std::unique_ptr<Node> CreateConv(const onnx::NodeProto& onnx_node) {
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

std::unique_ptr<Node> Conv::create(
    std::vector<std::string> inputs, 
    std::vector<std::string> outputs,
    std::vector<uint64_t> kernel_shape,
    std::vector<uint64_t> strides,
    std::vector<uint64_t> pads,
    std::vector<uint64_t> dilations,
    uint64_t groups,
    Conv::PadType auto_pad
) {
    detail::CheckSize(inputs.size(), MIN_INPUTS_SIZE, MAX_INPUTS_SIZE, std::string(Name), "input parametrs");
    detail::CheckSize(outputs.size(), OUTPUTS_SIZE, std::string(Name), "output parametrs");

    if (kernel_shape.empty()) {
        utils::THROW(
            "tenpiler::graph::Conv can't create from onnx_node without kernel shape"
        );
    }

    if (strides.empty()) {
        strides = std::vector<uint64_t>(kernel_shape.size(), 1);
    }
    else if (strides.size() != kernel_shape.size()) {
        utils::THROW(
            "Conv strides size (" + std::to_string(strides.size()) +
            ") must match kernel_shape size (" + std::to_string(kernel_shape.size()) + ")"
        );
    }

    if (pads.empty()) {
        if (auto_pad == PadType::NotSet) {
            pads = std::vector<uint64_t>(kernel_shape.size() * 2, 0);
        }
    } 
    else if (auto_pad != PadType::NotSet) {
        utils::THROW("Conv can't have both auto_pad != NOTSET and non-empty pads");
    }
    else if (pads.size() != 2 * kernel_shape.size()) {
        utils::THROW(
            "Conv pads size (" + std::to_string(pads.size()) +
            ") must be twice the 'kernel_shape' size (" + 
            std::to_string(kernel_shape.size()) + " * 2 = " +
            std::to_string(2 * kernel_shape.size()) + ")"
        );
    }

    if (dilations.empty()) {
        dilations = std::vector<uint64_t>(kernel_shape.size(), 1);
    } 
    else if (dilations.size() != kernel_shape.size()) {
        utils::THROW(
            "Conv dilations size (" + std::to_string(dilations.size()) +
            ") must match kernel_shape size (" + std::to_string(kernel_shape.size()) + ")"
        );
    }

    if (groups < 1) {
        utils::THROW("Conv groups must be >= 1, but has " + std::to_string(groups));
    }

    return std::unique_ptr<Conv>(new Conv(
        std::move(inputs), std::move(outputs), std::move(kernel_shape), std::move(strides), 
        std::move(pads), std::move(dilations), groups, auto_pad
    ));
}

Conv::Conv(std::vector<std::string> inputs, 
           std::vector<std::string> outputs,
           std::vector<uint64_t> kernel_shape,
           std::vector<uint64_t> strides,
           std::vector<uint64_t> pads,
           std::vector<uint64_t> dilations,
           uint64_t groups ,
           PadType auto_pad
)   :   Node(std::string(Name), std::move(inputs), std::move(outputs))
    ,   kernel_shape_(std::move(kernel_shape))
    ,   strides_(std::move(strides))
    ,   pads_(std::move(pads))
    ,   dilations_(std::move(dilations))
    ,   groups_(groups)
    ,   auto_pad_(auto_pad)
{}

void Conv::REGISTER_METHOD_NAME() {
    NodeFactory::Register(std::string(Name), CreateConv);
}


}
}