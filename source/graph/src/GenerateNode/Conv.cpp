// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/Ops.hpp"

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
	// TODO codegen this
}

#define RET_STR_TO_ENUM_(enum_name, field_name)                                                     \
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
