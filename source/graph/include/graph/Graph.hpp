#pragma once

#include <unordered_map>
#include <memory>

#include <onnx/onnx-ml.pb.h>

#include "graph/Tensor.hpp"
#include "graph/Node.hpp"

namespace tenpiler {
namespace graph {

class Graph {

public:

    explicit Graph(const onnx::GraphProto& onnx_graph);

private:

    std::unordered_map<std::string, Tensor> tensors_;
    
    std::vector<std::unique_ptr<Node>> nodes_;
    
    std::vector<std::string> input_;
    std::vector<std::string> output_;
    
};

}
}