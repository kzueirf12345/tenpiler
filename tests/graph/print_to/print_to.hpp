#pragma once

#include "graph/Graph.hpp"
#include "graph/Tensor.hpp"

#include "../graph_test_data.hpp"

namespace tenpiler {
namespace graph    { 

    void PrintTo(const Tensor& tensor, std::ostream* os);
    void PrintTo(const Node& node, std::ostream* os);
}
}

namespace tenpiler {
namespace tests    {
    
    void PrintTo(const GraphTestData& data, std::ostream* os);
}
}