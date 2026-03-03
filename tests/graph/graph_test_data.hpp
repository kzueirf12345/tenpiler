#pragma once

#include "graph/Graph.hpp"
#include "graph/Node/Ops.hpp"
#include "graph/Tensor.hpp"

namespace tenpiler {
namespace tests    {

using namespace graph;


struct GraphTestData
{
    std::string filepath;

    std::vector<Node>                       expected_nodes;
    std::unordered_map<std::string, Tensor> expected_tensors;

    std::vector<std::string> expected_input;
    std::vector<std::string> expected_output;
};

}
}