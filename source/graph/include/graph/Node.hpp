#pragma once

#include <string_view>
#include <string>
#include <vector>

namespace tenpiler {
namespace graph {

class Node {

public:

    virtual std::string_view getOpType() const;

    virtual const std::vector<std::string>& getInputs() const;
    virtual const std::vector<std::string>& getOutputs() const;

    virtual ~Node() = default;

protected:

    Node(std::string op_type, std::vector<std::string> inputs, std::vector<std::string> outputs);

    std::string op_type_;

    std::vector<std::string> inputs_;
    std::vector<std::string> outputs_;
};

class Add final: public Node {

public:

    static constexpr size_t INPUTS_SIZE = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    Add(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Mul final: public Node {

public:

    static constexpr size_t INPUTS_SIZE = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    Mul(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Conv final: public Node {

private:

    enum class PadType {
        NotSet,
        SameUpper,
        SameLower,
        Valid
    };

public:

    static constexpr size_t MIN_INPUTS_SIZE = 2;
    static constexpr size_t MAX_INPUTS_SIZE = 3;
    static constexpr size_t OUTPUTS_SIZE = 1;

    Conv(std::vector<std::string> inputs, 
         std::vector<std::string> outputs,
         std::vector<uint64_t> kernel_shape,
         std::vector<uint64_t> strides,
         std::vector<uint64_t> pads,
         std::vector<uint64_t> dilations,
         int64_t groups = 1,
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

    static constexpr size_t INPUTS_SIZE = 1;
    static constexpr size_t OUTPUTS_SIZE = 1;

    Relu(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class MatMul final: public Node {

public:

    static constexpr size_t INPUTS_SIZE = 2;
    static constexpr size_t OUTPUTS_SIZE = 1;

    MatMul(std::vector<std::string> inputs, std::vector<std::string> outputs);

};

class Gemm final: public Node {

public:

    static constexpr size_t MIN_INPUTS_SIZE = 2;
    static constexpr size_t MAX_INPUTS_SIZE = 3;
    static constexpr size_t OUTPUTS_SIZE = 1;

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