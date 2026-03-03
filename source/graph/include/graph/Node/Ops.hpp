// Сгенерированный файл
// Не редактировать вручную

#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <cstdint>

#include "graph/Node/NodeMeta.hpp"

namespace tenpiler {
namespace graph {

class Add {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "Add";

	static constexpr size_t MIN_INPUTS_SIZE  = 2;
	static constexpr size_t MAX_INPUTS_SIZE  = 2;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;


public:

	Add(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs
	);

public:

	friend bool operator==(const Add&, const Add&) = default;

};

class Mul {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "Mul";

	static constexpr size_t MIN_INPUTS_SIZE  = 2;
	static constexpr size_t MAX_INPUTS_SIZE  = 2;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;


public:

	Mul(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs
	);

public:

	friend bool operator==(const Mul&, const Mul&) = default;

};

class Sub {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "Sub";

	static constexpr size_t MIN_INPUTS_SIZE  = 2;
	static constexpr size_t MAX_INPUTS_SIZE  = 2;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;


public:

	Sub(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs
	);

public:

	friend bool operator==(const Sub&, const Sub&) = default;

};

class Div {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "Div";

	static constexpr size_t MIN_INPUTS_SIZE  = 2;
	static constexpr size_t MAX_INPUTS_SIZE  = 2;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;


public:

	Div(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs
	);

public:

	friend bool operator==(const Div&, const Div&) = default;

};

class Conv {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "Conv";

	static constexpr size_t MIN_INPUTS_SIZE  = 2;
	static constexpr size_t MAX_INPUTS_SIZE  = 3;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;

public:

	 enum class PadType {
		NOTSET,
		SAME_UPPER,
		SAME_LOWER,
		VALID,
	};

	static Conv::PadType ParsePadType(std::string_view str);


public:

	Conv(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs,
		std::vector<uint64_t> kernel_shape,
		std::vector<uint64_t> strides = {},
		std::vector<uint64_t> pads = {},
		std::vector<uint64_t> dilations = {},
		uint64_t groups = 1,
		PadType auto_pad = PadType::NOTSET
	);

private:

	std::vector<uint64_t> kernel_shape_;
	std::vector<uint64_t> strides_;
	std::vector<uint64_t> pads_;
	std::vector<uint64_t> dilations_;
	uint64_t groups_;
	PadType auto_pad_;

public:

	[[nodiscard]] const std::vector<uint64_t>& get_kernel_shape() const noexcept { return kernel_shape_; };
	[[nodiscard]] const std::vector<uint64_t>& get_strides() const noexcept { return strides_; };
	[[nodiscard]] const std::vector<uint64_t>& get_pads() const noexcept { return pads_; };
	[[nodiscard]] const std::vector<uint64_t>& get_dilations() const noexcept { return dilations_; };
	[[nodiscard]] const uint64_t& get_groups() const noexcept { return groups_; };
	[[nodiscard]] const PadType& get_auto_pad() const noexcept { return auto_pad_; };

public:

	friend bool operator==(const Conv&, const Conv&) = default;

};

class MaxPool {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "MaxPool";

	static constexpr size_t MIN_INPUTS_SIZE  = 1;
	static constexpr size_t MAX_INPUTS_SIZE  = 1;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;

public:

	 enum class PadType {
		NOTSET,
		SAME_UPPER,
		SAME_LOWER,
		VALID,
	};

	static MaxPool::PadType ParsePadType(std::string_view str);


public:

	MaxPool(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs,
		std::vector<uint64_t> kernel_shape,
		std::vector<uint64_t> strides = {},
		std::vector<uint64_t> pads = {},
		std::vector<uint64_t> dilations = {},
		PadType auto_pad = PadType::NOTSET,
		bool ceil_mode = false
	);

private:

	std::vector<uint64_t> kernel_shape_;
	std::vector<uint64_t> strides_;
	std::vector<uint64_t> pads_;
	std::vector<uint64_t> dilations_;
	PadType auto_pad_;
	bool ceil_mode_;

public:

	[[nodiscard]] const std::vector<uint64_t>& get_kernel_shape() const noexcept { return kernel_shape_; };
	[[nodiscard]] const std::vector<uint64_t>& get_strides() const noexcept { return strides_; };
	[[nodiscard]] const std::vector<uint64_t>& get_pads() const noexcept { return pads_; };
	[[nodiscard]] const std::vector<uint64_t>& get_dilations() const noexcept { return dilations_; };
	[[nodiscard]] const PadType& get_auto_pad() const noexcept { return auto_pad_; };
	[[nodiscard]] const bool& get_ceil_mode() const noexcept { return ceil_mode_; };

public:

	friend bool operator==(const MaxPool&, const MaxPool&) = default;

};

class Gemm {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "Gemm";

	static constexpr size_t MIN_INPUTS_SIZE  = 2;
	static constexpr size_t MAX_INPUTS_SIZE  = 3;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;


public:

	Gemm(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs,
		float alpha = 1.0f,
		float betta = 1.0f,
		bool transA = false,
		bool transB = false
	);

private:

	float alpha_;
	float betta_;
	bool transA_;
	bool transB_;

public:

	[[nodiscard]] const float& get_alpha() const noexcept { return alpha_; };
	[[nodiscard]] const float& get_betta() const noexcept { return betta_; };
	[[nodiscard]] const bool& get_transA() const noexcept { return transA_; };
	[[nodiscard]] const bool& get_transB() const noexcept { return transB_; };

public:

	friend bool operator==(const Gemm&, const Gemm&) = default;

};

class Relu {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "Relu";

	static constexpr size_t MIN_INPUTS_SIZE  = 1;
	static constexpr size_t MAX_INPUTS_SIZE  = 1;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;


public:

	Relu(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs
	);

public:

	friend bool operator==(const Relu&, const Relu&) = default;

};

class MatMul {

private:

	NodeMeta meta_;

public:

	[[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; }

	static constexpr std::string_view OnnxName = "MatMul";

	static constexpr size_t MIN_INPUTS_SIZE  = 2;
	static constexpr size_t MAX_INPUTS_SIZE  = 2;
	static constexpr size_t MIN_OUTPUTS_SIZE = 1;
	static constexpr size_t MAX_OUTPUTS_SIZE = 1;


public:

	MatMul(
		std::vector<std::string> inputs,
		std::vector<std::string> outputs
	);

public:

	friend bool operator==(const MatMul&, const MatMul&) = default;

};

} // namespace graph
} // namespace tenpiler
