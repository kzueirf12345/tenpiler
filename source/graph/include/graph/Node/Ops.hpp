#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <stdint.h>

#include "graph/Node/NodeMeta.hpp"

namespace tenpiler {
namespace graph {

class Add {

private:
    NodeMeta meta_;

public:
    [[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; } 

    static constexpr std::string_view OnnxName = "Add";

    static constexpr size_t INPUTS_SIZE = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static Add create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs
    );

private:

    Add(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Mul {

private:
    NodeMeta meta_;

public:
    [[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; } 

    static constexpr std::string_view OnnxName = "Mul";

    static constexpr size_t INPUTS_SIZE  = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static Mul create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs
    );

private:

    Mul(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Conv {

private:
    NodeMeta meta_;

public:
    [[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; } 

    static constexpr std::string_view OnnxName = "Conv";

    static constexpr size_t MIN_INPUTS_SIZE = 2;
    static constexpr size_t MAX_INPUTS_SIZE = 3;
    static constexpr size_t OUTPUTS_SIZE    = 1;

public:

    enum class PadType {
        NotSet,
        SameUpper,
        SameLower,
        Valid
    };

    static Conv::PadType ParseAutoPad(std::string_view str_auto_pad);

public:

    static Conv create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs,
        std::vector<uint64_t> kernel_shape,
        std::vector<uint64_t> strides,
        std::vector<uint64_t> pads,
        std::vector<uint64_t> dilations,
        uint64_t groups = 1,
        PadType auto_pad = PadType::NotSet
    );

private:

    Conv(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs,
        std::vector<uint64_t> kernel_shape,
        std::vector<uint64_t> strides,
        std::vector<uint64_t> pads,
        std::vector<uint64_t> dilations,
        uint64_t groups = 1,
        PadType auto_pad = PadType::NotSet
    );

private:
    
    std::vector<uint64_t> kernel_shape_;
    std::vector<uint64_t> strides_;
    std::vector<uint64_t> pads_;
    std::vector<uint64_t> dilations_;
    uint64_t groups_;
    PadType auto_pad_;

};

class Relu {

private:
    NodeMeta meta_;

public:
    [[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; } 

    static constexpr std::string_view OnnxName = "Relu";

    static constexpr size_t INPUTS_SIZE = 1;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static Relu create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs
    );

private:

    Relu(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class MatMul {

private:
    NodeMeta meta_;

public:
    [[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; } 

    static constexpr std::string_view OnnxName = "MatMul";

    static constexpr size_t INPUTS_SIZE = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static MatMul create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs
    );

private:

    MatMul(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Gemm {

private:
    NodeMeta meta_;

public:
    [[nodiscard]] const NodeMeta& meta() const noexcept { return meta_; } 

    static constexpr std::string_view OnnxName = "Gemm";

    static constexpr size_t MIN_INPUTS_SIZE = 2;
    static constexpr size_t MAX_INPUTS_SIZE = 3;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static Gemm create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs,
        float alpha = 1,
        float betta = 1,
        bool transA = false,
        bool transB = false
    );

private:

    Gemm(std::vector<std::string> inputs, 
         std::vector<std::string> outputs,
         float alpha = 1,
         float betta = 1,
         bool transA = false,
         bool transB = false
    );

private:

    float alpha_;
    float betta_;
    bool transA_;
    bool transB_;

};

}
}