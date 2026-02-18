#pragma once

#include <memory>
#include <string_view>
#include <string>
#include <vector>

#include "graph/NodeFactory.hpp"

namespace tenpiler {
namespace graph {


class Node {

public:

    [[nodiscard]] const std::string& sayMyName() const noexcept;

    [[nodiscard]] const std::vector<std::string>& getInputs () const noexcept;
    [[nodiscard]] const std::vector<std::string>& getOutputs() const noexcept;

    virtual ~Node() = default;

protected:

    Node(std::string op_type, std::vector<std::string> inputs, std::vector<std::string> outputs);

private:

    std::string op_type_;

    std::vector<std::string> inputs_;
    std::vector<std::string> outputs_;
    
};

class Add final: public Node {

public:

    static constexpr std::string_view OnnxName = "Add";

    static constexpr size_t INPUTS_SIZE = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static std::unique_ptr<Node> create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs
    );

    static void REGISTER_METHOD_NAME();

private:

    Add(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Mul final: public Node {

public:

    static constexpr std::string_view OnnxName = "Mul";

    static constexpr size_t INPUTS_SIZE  = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static std::unique_ptr<Node> create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs
    );

    static void REGISTER_METHOD_NAME();

private:

    Mul(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Conv final: public Node {

public:

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

    static std::unique_ptr<Node> create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs,
        std::vector<uint64_t> kernel_shape,
        std::vector<uint64_t> strides,
        std::vector<uint64_t> pads,
        std::vector<uint64_t> dilations,
        uint64_t groups = 1,
        PadType auto_pad = PadType::NotSet
    );

    static void REGISTER_METHOD_NAME();

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

class Relu final: public Node {

public:

    static constexpr std::string_view OnnxName = "Relu";

    static constexpr size_t INPUTS_SIZE = 1;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static std::unique_ptr<Node> create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs
    );

    static void REGISTER_METHOD_NAME();

private:

    Relu(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class MatMul final: public Node {

public:

    static constexpr std::string_view OnnxName = "MatMul";

    static constexpr size_t INPUTS_SIZE = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static std::unique_ptr<Node> create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs
    );

    static void REGISTER_METHOD_NAME();

private:

    MatMul(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Gemm final: public Node {

public:

    static constexpr std::string_view OnnxName = "Gemm";

    static constexpr size_t MIN_INPUTS_SIZE = 2;
    static constexpr size_t MAX_INPUTS_SIZE = 3;
    static constexpr size_t OUTPUTS_SIZE = 1;

    static std::unique_ptr<Node> create(
        std::vector<std::string> inputs, 
        std::vector<std::string> outputs,
        float alpha = 1,
        float betta = 1,
        bool transA = false,
        bool transB = false
    );

    static void REGISTER_METHOD_NAME();

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