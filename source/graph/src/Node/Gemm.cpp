#include "graph/Node/Ops.hpp"

#include "graph/Node/utils.hpp"
#include "utils/common.hpp"
#include <cmath>

namespace tenpiler {
namespace graph {


Gemm Gemm::create(
    std::vector<std::string> inputs, 
    std::vector<std::string> outputs,
    float alpha,
    float betta,
    bool transA,
    bool transB
) {
    detail::CheckSize(inputs.size(), MIN_INPUTS_SIZE, MAX_INPUTS_SIZE, std::string(OnnxName), "input parametrs");
    detail::CheckSize(outputs.size(), OUTPUTS_SIZE, std::string(OnnxName), "output parametrs");

    if (std::isnan(alpha)) {
        utils::THROW("Gemm alpha is NaN");
    }
    if (std::isnan(betta)) {
        utils::THROW("Gemm betta is NaN");
    }
    if (std::isinf(alpha)) {
        utils::THROW("Gemm alpha is Inf");
    }
    if (std::isinf(betta)) {
        utils::THROW("Gemm betta is Inf");
    }
    return Gemm(
        std::move(inputs), std::move(outputs), alpha, betta, transA, transB
    );
}

Gemm::Gemm(std::vector<std::string> inputs, 
           std::vector<std::string> outputs,
           float alpha,
           float betta,
           bool transA,
           bool transB
)   :    meta_({std::string(OnnxName), std::move(inputs), std::move(outputs)})
    ,   alpha_(alpha)
    ,   betta_(betta)
    ,   transA_(transA)
    ,   transB_(transB)
{}


}
}