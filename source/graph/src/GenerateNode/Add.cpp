// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/Ops.hpp"

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"

namespace tenpiler {
namespace graph {

Add::Add(
	std::vector<std::string> inputs,
	std::vector<std::string> outputs
)	:	meta_({std::string(OnnxName), std::move(inputs), std::move(outputs)})
{}

Add Add::create(
	std::vector<std::string> inputs,
	std::vector<std::string> outputs
) {
	// TODO codegen this
}

} // namespace graph
} // namespace tenpiler
