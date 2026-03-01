// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/OpsDumb.hpp"

namespace tenpiler {
namespace graph {
namespace dump {

std::string GetDot(const Add& n){
	return std::to_string(Add::MIN_INPUTS_SIZE) + "-" + std::to_string(Add::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " }} | " + std::to_string(Add::MIN_OUTPUTS_SIZE) + "-" + std::to_string(Add::MAX_OUTPUTS_SIZE);
}

std::string GetDot(const Mul& n){
	return std::to_string(Mul::MIN_INPUTS_SIZE) + "-" + std::to_string(Mul::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " }} | " + std::to_string(Mul::MIN_OUTPUTS_SIZE) + "-" + std::to_string(Mul::MAX_OUTPUTS_SIZE);
}

std::string GetDot(const Sub& n){
	return std::to_string(Sub::MIN_INPUTS_SIZE) + "-" + std::to_string(Sub::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " }} | " + std::to_string(Sub::MIN_OUTPUTS_SIZE) + "-" + std::to_string(Sub::MAX_OUTPUTS_SIZE);
}

std::string GetDot(const Div& n){
	return std::to_string(Div::MIN_INPUTS_SIZE) + "-" + std::to_string(Div::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " }} | " + std::to_string(Div::MIN_OUTPUTS_SIZE) + "-" + std::to_string(Div::MAX_OUTPUTS_SIZE);
}

std::string GetDot(const Conv& n){
	return std::to_string(Conv::MIN_INPUTS_SIZE) + "-" + std::to_string(Conv::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " | vector\\<uint64_t\\> kernel_shape" + " | vector\\<uint64_t\\> strides" + " | vector\\<uint64_t\\> pads" + " | vector\\<uint64_t\\> dilations" + " | uint64_t groups" + " | PadType auto_pad" + " }} | " + std::to_string(Conv::MIN_OUTPUTS_SIZE) + "-" + std::to_string(Conv::MAX_OUTPUTS_SIZE);
}

std::string GetDot(const MaxPool& n){
	return std::to_string(MaxPool::MIN_INPUTS_SIZE) + "-" + std::to_string(MaxPool::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " | vector\\<uint64_t\\> kernel_shape" + " | vector\\<uint64_t\\> strides" + " | vector\\<uint64_t\\> pads" + " | vector\\<uint64_t\\> dilations" + " | PadType auto_pad" + " | bool ceil_mode" + " }} | " + std::to_string(MaxPool::MIN_OUTPUTS_SIZE) + "-" + std::to_string(MaxPool::MAX_OUTPUTS_SIZE);
}

std::string GetDot(const Gemm& n){
	return std::to_string(Gemm::MIN_INPUTS_SIZE) + "-" + std::to_string(Gemm::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " | float alpha" + " | float betta" + " | bool transA" + " | bool transB" + " }} | " + std::to_string(Gemm::MIN_OUTPUTS_SIZE) + "-" + std::to_string(Gemm::MAX_OUTPUTS_SIZE);
}

std::string GetDot(const Relu& n){
	return std::to_string(Relu::MIN_INPUTS_SIZE) + "-" + std::to_string(Relu::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " }} | " + std::to_string(Relu::MIN_OUTPUTS_SIZE) + "-" + std::to_string(Relu::MAX_OUTPUTS_SIZE);
}

std::string GetDot(const MatMul& n){
	return std::to_string(MatMul::MIN_INPUTS_SIZE) + "-" + std::to_string(MatMul::MAX_INPUTS_SIZE) + " | {{" + n.meta().op_type + " }} | " + std::to_string(MatMul::MIN_OUTPUTS_SIZE) + "-" + std::to_string(MatMul::MAX_OUTPUTS_SIZE);
}

} // namespace dump
} // namespace graph
} // namespace tenpiler
