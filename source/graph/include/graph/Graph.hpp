#pragma once

#include <unordered_map>
#include <memory>

#include <onnx/onnx-ml.pb.h>

#include "graph/Tensor.hpp"
#include "graph/Node/Node.hpp"

namespace tenpiler {
namespace graph {

class Graph {

public:

    explicit Graph(const onnx::GraphProto& onnx_graph);

    [[nodiscard]] const std::vector<std::unique_ptr<Node>>&      getNodes  () const noexcept;
    [[nodiscard]] const std::unordered_map<std::string, Tensor>& getTensors() const noexcept;
    [[nodiscard]] const std::vector<std::string>&                getInputs () const noexcept;
    [[nodiscard]] const std::vector<std::string>&                getOutputs() const noexcept;

    [[nodiscard]] const Tensor& getTensor(const std::string& name) const noexcept;

private:

    std::unordered_map<std::string, Tensor> tensors_;
    
    std::vector<std::unique_ptr<Node>> nodes_;
    
    std::vector<std::string> input_;
    std::vector<std::string> output_;
    
};

}
}