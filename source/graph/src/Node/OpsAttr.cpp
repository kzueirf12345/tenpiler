// Сгенерированный файл
// Не редактировать вручную

#include "graph/Node/OpsAttr.hpp"

namespace tenpiler {
namespace graph {

std::any GetAttribute(const Add& node, const std::string& name) {
	(void)node;
	(void)name;

	return {};
}

std::any GetAttribute(const Mul& node, const std::string& name) {
	(void)node;
	(void)name;

	return {};
}

std::any GetAttribute(const Sub& node, const std::string& name) {
	(void)node;
	(void)name;

	return {};
}

std::any GetAttribute(const Div& node, const std::string& name) {
	(void)node;
	(void)name;

	return {};
}

std::any GetAttribute(const Conv& node, const std::string& name) {

	if (name == "kernel_shape") return node.get_kernel_shape();
	if (name == "strides") return node.get_strides();
	if (name == "pads") return node.get_pads();
	if (name == "dilations") return node.get_dilations();
	if (name == "groups") return node.get_groups();
	if (name == "auto_pad") return node.get_auto_pad();
	return {};
}

std::any GetAttribute(const MaxPool& node, const std::string& name) {

	if (name == "kernel_shape") return node.get_kernel_shape();
	if (name == "strides") return node.get_strides();
	if (name == "pads") return node.get_pads();
	if (name == "dilations") return node.get_dilations();
	if (name == "auto_pad") return node.get_auto_pad();
	if (name == "ceil_mode") return node.get_ceil_mode();
	return {};
}

std::any GetAttribute(const Gemm& node, const std::string& name) {

	if (name == "alpha") return node.get_alpha();
	if (name == "betta") return node.get_betta();
	if (name == "transA") return node.get_transA();
	if (name == "transB") return node.get_transB();
	return {};
}

std::any GetAttribute(const Relu& node, const std::string& name) {
	(void)node;
	(void)name;

	return {};
}

std::any GetAttribute(const MatMul& node, const std::string& name) {
	(void)node;
	(void)name;

	return {};
}

} // namespace graph
} // namespace tenpiler
