#pragma once

#include "graph/Graph.hpp"

namespace tenpiler {
namespace graph    {
namespace dump   {

void GraphDumb(const Graph& graph);

std::string GetTensorLabel(const Tensor& tensor);


} // namespace dump    
} // namespace graph
} // namespace tenplier