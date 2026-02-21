#include "graph/Node/Ops.hpp"

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


Conv Conv::create(
    std::vector<std::string> inputs, 
    std::vector<std::string> outputs,
    std::vector<uint64_t> kernel_shape,
    std::vector<uint64_t> strides,
    std::vector<uint64_t> pads,
    std::vector<uint64_t> dilations,
    uint64_t groups,
    Conv::PadType auto_pad
) {
    detail::CheckSize(inputs.size(), MIN_INPUTS_SIZE, MAX_INPUTS_SIZE, std::string(OnnxName), "input parametrs");
    detail::CheckSize(outputs.size(), OUTPUTS_SIZE, std::string(OnnxName), "output parametrs");

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

    return Conv(
        std::move(inputs), std::move(outputs), std::move(kernel_shape), std::move(strides), 
        std::move(pads), std::move(dilations), groups, auto_pad
    );
}

Conv::Conv(std::vector<std::string> inputs, 
           std::vector<std::string> outputs,
           std::vector<uint64_t> kernel_shape,
           std::vector<uint64_t> strides,
           std::vector<uint64_t> pads,
           std::vector<uint64_t> dilations,
           uint64_t groups ,
           PadType auto_pad
)   :    meta_({std::string(OnnxName), std::move(inputs), std::move(outputs)})
    ,   kernel_shape_(std::move(kernel_shape))
    ,   strides_(std::move(strides))
    ,   pads_(std::move(pads))
    ,   dilations_(std::move(dilations))
    ,   groups_(groups)
    ,   auto_pad_(auto_pad)
{}


}
}