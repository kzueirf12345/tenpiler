// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/Ops.hpp"

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
	// TODO codegen this
}

} // namespace graph
} // namespace tenpiler
