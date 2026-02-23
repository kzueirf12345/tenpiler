// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/OpsDumb.hpp"

namespace tenpiler {
namespace graph {
namespace dump {

std::string_view GetDot(const Add& n){
	return n.meta().op_type;
}

std::string_view GetDot(const Mul& n){
	return n.meta().op_type;
}

std::string_view GetDot(const Sub& n){
	return n.meta().op_type;
}

std::string_view GetDot(const Div& n){
	return n.meta().op_type;
}

std::string_view GetDot(const Conv& n){
	return n.meta().op_type;
}

std::string_view GetDot(const MaxPool& n){
	return n.meta().op_type;
}

std::string_view GetDot(const Gemm& n){
	return n.meta().op_type;
}

std::string_view GetDot(const Relu& n){
	return n.meta().op_type;
}

std::string_view GetDot(const MatMul& n){
	return n.meta().op_type;
}

} // namespace dump
} // namespace graph
} // namespace tenpiler
