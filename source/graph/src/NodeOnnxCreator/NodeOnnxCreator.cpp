// Сгенерированный файл
// Не редактировать вручную

#include "NodeOnnxCreator.hpp"

#include <string>

#include <onnx/onnx_pb.h>

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"

namespace tenpiler {
namespace graph {
namespace onnx_parse {

Node CreateAdd(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	return Add(
		std::move(inputs),
		std::move(outputs)
	);
}

Node CreateMul(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	return Mul(
		std::move(inputs),
		std::move(outputs)
	);
}

Node CreateSub(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	return Sub(
		std::move(inputs),
		std::move(outputs)
	);
}

Node CreateDiv(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	return Div(
		std::move(inputs),
		std::move(outputs)
	);
}

Node CreateConv(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	const auto kernel_shape_opt = detail::GetIntsAttribute(onnx_node, "kernel_shape");
	if (!kernel_shape_opt.has_value()) {
		utils::THROW(
			"Conv can't create from onnx_node without kernel_shape"
		);
	}
	const std::vector<uint64_t> kernel_shape = *kernel_shape_opt;

	const auto strides_opt = detail::GetIntsAttribute(onnx_node, "strides");
	std::vector<uint64_t> strides = {};
	if (strides_opt.has_value()) {
		strides = *strides_opt;
	}

	const auto pads_opt = detail::GetIntsAttribute(onnx_node, "pads");
	std::vector<uint64_t> pads = {};
	if (pads_opt.has_value()) {
		pads = *pads_opt;
	}

	const auto dilations_opt = detail::GetIntsAttribute(onnx_node, "dilations");
	std::vector<uint64_t> dilations = {};
	if (dilations_opt.has_value()) {
		dilations = *dilations_opt;
	}

	const auto groups_opt = detail::GetIntAttribute(onnx_node, "groups");
	uint64_t groups = 1;
	if (groups_opt.has_value()) {
		groups = *groups_opt;
	}

	const auto auto_pad_opt = detail::GetStringAttribute(onnx_node, "auto_pad");
	Conv::PadType auto_pad = Conv::PadType::NOTSET;
	if (auto_pad_opt.has_value()) {
		auto_pad = Conv::ParsePadType(*auto_pad_opt);
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

Node CreateMaxPool(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	const auto kernel_shape_opt = detail::GetIntsAttribute(onnx_node, "kernel_shape");
	if (!kernel_shape_opt.has_value()) {
		utils::THROW(
			"MaxPool can't create from onnx_node without kernel_shape"
		);
	}
	const std::vector<uint64_t> kernel_shape = *kernel_shape_opt;

	const auto strides_opt = detail::GetIntsAttribute(onnx_node, "strides");
	std::vector<uint64_t> strides = {};
	if (strides_opt.has_value()) {
		strides = *strides_opt;
	}

	const auto pads_opt = detail::GetIntsAttribute(onnx_node, "pads");
	std::vector<uint64_t> pads = {};
	if (pads_opt.has_value()) {
		pads = *pads_opt;
	}

	const auto dilations_opt = detail::GetIntsAttribute(onnx_node, "dilations");
	std::vector<uint64_t> dilations = {};
	if (dilations_opt.has_value()) {
		dilations = *dilations_opt;
	}

	const auto auto_pad_opt = detail::GetStringAttribute(onnx_node, "auto_pad");
	MaxPool::PadType auto_pad = MaxPool::PadType::NOTSET;
	if (auto_pad_opt.has_value()) {
		auto_pad = MaxPool::ParsePadType(*auto_pad_opt);
	}

	const auto ceil_mode_opt = detail::GetIntAttribute(onnx_node, "ceil_mode");
	bool ceil_mode = false;
	if (ceil_mode_opt.has_value()) {
		ceil_mode = *ceil_mode_opt;
	}

	return MaxPool(
		std::move(inputs),
		std::move(outputs),
		std::move(kernel_shape),
		std::move(strides),
		std::move(pads),
		std::move(dilations),
		std::move(auto_pad),
		std::move(ceil_mode)
	);
}

Node CreateGemm(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	const auto alpha_opt = detail::GetFloatAttribute(onnx_node, "alpha");
	float alpha = 1.0f;
	if (alpha_opt.has_value()) {
		alpha = *alpha_opt;
	}

	const auto betta_opt = detail::GetFloatAttribute(onnx_node, "betta");
	float betta = 1.0f;
	if (betta_opt.has_value()) {
		betta = *betta_opt;
	}

	const auto transA_opt = detail::GetIntAttribute(onnx_node, "transA");
	bool transA = false;
	if (transA_opt.has_value()) {
		transA = *transA_opt;
	}

	const auto transB_opt = detail::GetIntAttribute(onnx_node, "transB");
	bool transB = false;
	if (transB_opt.has_value()) {
		transB = *transB_opt;
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

Node CreateRelu(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	return Relu(
		std::move(inputs),
		std::move(outputs)
	);
}

Node CreateMatMul(const onnx::NodeProto& onnx_node) {
	std::vector<std::string> inputs (onnx_node. input().begin(), onnx_node. input().end());
	std::vector<std::string> outputs(onnx_node.output().begin(), onnx_node.output().end());

	return MatMul(
		std::move(inputs),
		std::move(outputs)
	);
}

} // namespace onnx_parse
} // namespace graph
} // namespace tenpiler
