// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/Ops.hpp"

#include <cmath>

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"

namespace tenpiler {
namespace graph {

Conv::Conv(
	std::vector<std::string> inputs,
	std::vector<std::string> outputs,
	std::vector<uint64_t> kernel_shape,
	std::vector<uint64_t> strides,
	std::vector<uint64_t> pads,
	std::vector<uint64_t> dilations,
	uint64_t groups,
	Conv::PadType auto_pad
)	:	meta_({std::string(OnnxName), std::move(inputs), std::move(outputs)})
	,	kernel_shape_(std::move(kernel_shape))
	,	strides_(std::move(strides))
	,	pads_(std::move(pads))
	,	dilations_(std::move(dilations))
	,	groups_(std::move(groups))
	,	auto_pad_(std::move(auto_pad))
{}

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
	detail::CheckSize(
		inputs.size(),
		MIN_INPUTS_SIZE,
		MAX_INPUTS_SIZE,
		std::string(OnnxName),
		"input parametrs"
	);
	detail::CheckSize(
		outputs.size(),
		MIN_OUTPUTS_SIZE,
		MAX_OUTPUTS_SIZE,
		std::string(OnnxName),
		"outputs parametrs"
	);

	if (kernel_shape.empty()) {
		utils::THROW(
			"kernel shape must not be empty"
		);
	}

	if (strides.empty()) {
		strides = std::vector<uint64_t>(kernel_shape.size(), 1);
	}

	if (strides.size() != kernel_shape.size()) {
		utils::THROW(
			"strides and kernel_shape size must be equal"
		);
	}

	if (!(pads.empty() || (auto_pad == PadType::NOTSET))) {
		utils::THROW(
			"pads and auto_pad can't set at the same time"
		);
	}

	if (pads.empty()) {
		pads = std::vector<uint64_t>(kernel_shape.size() * 2, 0);
	}

	if (pads.size() != 2 * kernel_shape.size()) {
		utils::THROW(
			"pads size must be equal 2 * kernel_shape size"
		);
	}

	if (dilations.empty()) {
		dilations = std::vector<uint64_t>(kernel_shape.size(), 1);
	}

	if (dilations.size() != kernel_shape.size()) {
		utils::THROW(
			"dilations and kernel_shape size must be equal"
		);
	}

	if (groups < 1) {
		utils::THROW(
			"groups must be >= 1"
		);
	}

	return Conv(
		std::move(inputs),
		std::move(outputs),
		std::move(kernel_shape),
		std::move(strides),
		std::move(pads),
		std::move(dilations),
		std::move(groups),
		std::move(auto_pad)
	);
}

#define RET_STR_TO_ENUM_(enum_name, field_name)                                                    \
    do {                                                                                           \
        if (str == #field_name) {                                                                  \
            return Conv::enum_name::field_name;                                                    \
        }                                                                                          \
    } while(false)

Conv::PadType Conv::ParsePadType(std::string_view str) {

	RET_STR_TO_ENUM_(PadType, NOTSET);
	RET_STR_TO_ENUM_(PadType, SAME_UPPER);
	RET_STR_TO_ENUM_(PadType, SAME_LOWER);
	RET_STR_TO_ENUM_(PadType, VALID);

	utils::THROW("Unknown PadType str");

	return Conv::PadType::NOTSET;
}

#undef RET_STR_TO_ENUM_

} // namespace graph
} // namespace tenpiler
