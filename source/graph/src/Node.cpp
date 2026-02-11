#include "graph/Node.hpp"
#include <cmath>
#include <stdexcept>
#include <string_view>

namespace tenpiler {
namespace graph {

std::string_view Node::getOpType() const {
    return op_type_;
}

const std::vector<std::string>& Node::getInputs() const {
    return inputs_;
}

const std::vector<std::string>& Node::getOutputs() const {
    return inputs_;
}

Node::Node(std::string op_type, std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   op_type_(std::move(op_type))
    ,   inputs_(std::move(inputs))
    ,   outputs_(std::move(outputs))
{}

static void CheckSize(size_t size, size_t req_size, const std::string& op_name, 
    const std::string& param_name) 
{
    if (size != req_size) {
        throw std::runtime_error(
            "'" + op_name + "' must have " + std::to_string(req_size) + " " + param_name + 
            ", but has " + std::to_string(size)
        );
    }
}

static void CheckSize(size_t size, size_t min_req_size, size_t max_req_size, 
    const std::string& op_name, const std::string& param_name) 
{
    if (size < min_req_size || size > max_req_size) {
        throw std::runtime_error(
            "'" + op_name + "' must have from" + std::to_string(min_req_size) + " to " 
            + std::to_string(max_req_size) + " " + param_name + 
            ", but has " + std::to_string(size)
        );
    }
}

Add::Add(std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   Node("add", std::move(inputs), std::move(outputs))
{
    CheckSize( inputs_.size(),  INPUTS_SIZE, "Add",  "input parametrs");
    CheckSize(outputs_.size(), OUTPUTS_SIZE, "Add", "output parametrs");
}

Mul::Mul(std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   Node("add", std::move(inputs), std::move(outputs))
{
    CheckSize( inputs_.size(),  INPUTS_SIZE, "Mul",  "input parametrs");
    CheckSize(outputs_.size(), OUTPUTS_SIZE, "Mul", "output parametrs");
}

Conv::Conv(std::vector<std::string> inputs, 
           std::vector<std::string> outputs,
           std::vector<uint64_t> kernel_shape,
           std::vector<uint64_t> strides,
           std::vector<uint64_t> pads,
           std::vector<uint64_t> dilations,
           int64_t groups ,
           PadType auto_pad
)   :   Node("conv", std::move(inputs), std::move(outputs))
    ,   kernel_shape_(std::move(kernel_shape))
    ,   strides_(std::move(strides))
    ,   pads_(std::move(pads))
    ,   dilations_(std::move(dilations))
    ,   groups_(groups)
    ,   auto_pad_(auto_pad)
{
    CheckSize(inputs_.size(), MIN_INPUTS_SIZE, MAX_INPUTS_SIZE, "Conv", "input parametrs");
    CheckSize(outputs_.size(), OUTPUTS_SIZE, "Conv", "output parametrs");

    if (groups < 1) {
        throw std::runtime_error("'Conv' groups must be >= 1, but has " + std::to_string(groups));
    }

    if (auto_pad_ != PadType::NotSet && !pads_.empty()) {
        throw std::runtime_error(
            "'Conv' can't have both auto_pad != NOTSET and non-empty pads"
        );
    }
}

Relu::Relu(std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   Node("relu", std::move(inputs), std::move(outputs))
{
    CheckSize( inputs_.size(),  INPUTS_SIZE, "Relu",  "input parametrs");
    CheckSize(outputs_.size(), OUTPUTS_SIZE, "Relu", "output parametrs");
}

MatMul::MatMul(std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   Node("relu", std::move(inputs), std::move(outputs))
{
    CheckSize( inputs_.size(),  INPUTS_SIZE, "MatMul",  "input parametrs");
    CheckSize(outputs_.size(), OUTPUTS_SIZE, "MatMul", "output parametrs");
}

Gemm::Gemm(std::vector<std::string> inputs, 
           std::vector<std::string> outputs,
           float alpha,
           float betta,
           bool transA,
           bool transB
)   :   Node("gemm", std::move(inputs), std::move(outputs))
    ,   alpha_(alpha)
    ,   betta_(betta)
    ,   transA_(transA)
    ,   transB_(transB)
{
    CheckSize(inputs_.size(), MIN_INPUTS_SIZE, MAX_INPUTS_SIZE, "Gemm", "input parametrs");
    CheckSize(outputs_.size(), OUTPUTS_SIZE, "Gemm", "output parametrs");

    if (std::isnan(alpha)) {
        throw std::runtime_error("'Gemm' alpha is NaN");
    }
    if (std::isnan(betta)) {
        throw std::runtime_error("'Gemm' betta is NaN");
    }
}

}
}
