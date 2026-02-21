#include "graph/Node/Ops.hpp"

#include "graph/Node/utils.hpp"

namespace tenpiler {
namespace graph {

MatMul MatMul::create(std::vector<std::string> inputs, 
    std::vector<std::string> outputs
) {
    detail::CheckSize( inputs.size(),  INPUTS_SIZE, std::string(OnnxName),  "input parametrs");
    detail::CheckSize(outputs.size(), OUTPUTS_SIZE, std::string(OnnxName), "output parametrs");
    return MatMul(std::move(inputs), std::move(outputs));
}

MatMul::MatMul(std::vector<std::string> inputs, std::vector<std::string> outputs)
    :    meta_({std::string(OnnxName), std::move(inputs), std::move(outputs)})
{}


}
}