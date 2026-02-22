// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/Ops.hpp"

#include <cmath>

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"

namespace tenpiler {
namespace graph {

Gemm::Gemm(
	std::vector<std::string> inputs,
	std::vector<std::string> outputs,
	float alpha,
	float betta,
	bool transA,
	bool transB
)	:	meta_({std::string(OnnxName), std::move(inputs), std::move(outputs)})
	,	alpha_(std::move(alpha))
	,	betta_(std::move(betta))
	,	transA_(std::move(transA))
	,	transB_(std::move(transB))
{}

Gemm Gemm::create(
	std::vector<std::string> inputs,
	std::vector<std::string> outputs,
	float alpha,
	float betta,
	bool transA,
	bool transB
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

	if (std::isnan(alpha)) {
		utils::THROW(
			"Gemm alpha is NaN"
		);
	}

	if (std::isnan(betta)) {
		utils::THROW(
			"Gemm betta is NaN"
		);
	}

	if (std::isinf(alpha)) {
		utils::THROW(
			"Gemm alpha is Inf"
		);
	}

	if (std::isinf(betta)) {
		utils::THROW(
			"Gemm betta is Inf"
		);
	}

	return Gemm(
		std::move(inputs),
		std::move(outputs),
		std::move(alpha),
		std::move(betta),
		std::move(transA),
		std::move(transB)
	);
}

} // namespace graph
} // namespace tenpiler
