// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/Ops.hpp"

#include <cmath>

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"

namespace tenpiler {
namespace graph {

Mul::Mul(
	std::vector<std::string> inputs,
	std::vector<std::string> outputs
)	:	meta_({std::string(OnnxName), std::move(inputs), std::move(outputs)})
{}

Mul Mul::create(
	std::vector<std::string> inputs,
	std::vector<std::string> outputs
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

	return Mul(
		std::move(inputs),
		std::move(outputs)
	);
}

} // namespace graph
} // namespace tenpiler
