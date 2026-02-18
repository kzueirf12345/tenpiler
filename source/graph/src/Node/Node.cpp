#include "graph/Node/Node.hpp"

#include <cmath>
#include <utility>
#include <vector>

#include "graph/NodeFactory.hpp"

namespace tenpiler {
namespace graph {

const std::string& Node::sayMyName() const noexcept {
    return op_type_;
}

const std::vector<std::string>& Node::getInputs() const noexcept {
    return inputs_;
}

const std::vector<std::string>& Node::getOutputs() const noexcept {
    return outputs_;
}

Node::Node(std::string op_type, std::vector<std::string> inputs, std::vector<std::string> outputs)
    :   op_type_ (std::move(op_type))
    ,   inputs_  (std::move(inputs))
    ,   outputs_ (std::move(outputs))
{}

}
}
