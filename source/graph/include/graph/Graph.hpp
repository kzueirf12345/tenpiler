#pragma once

#include <istream>
#include <vector>
#include <string>
#include <unordered_map>

#include "graph/Tensor.hpp"
#include "graph/Node/Node.hpp"

namespace tenpiler {
namespace graph {

class Graph {

public:

    Graph();

    Graph(
        std::unordered_map<std::string, Tensor> tensors,
        std::vector<Node> nodes,
        std::vector<std::string> input,
        std::vector<std::string> output
    );

    void LoadFromOnnx(std::istream& input_onnx);

    [[nodiscard]] const std::vector<Node>&                       getNodes  () const noexcept;
    [[nodiscard]] const std::unordered_map<std::string, Tensor>& getTensors() const noexcept;
    [[nodiscard]] const std::vector<std::string>&                getInputs () const noexcept;
    [[nodiscard]] const std::vector<std::string>&                getOutputs() const noexcept;

    [[nodiscard]] const Tensor& getTensor(const std::string& name) const;

private:

    std::unordered_map<std::string, Tensor> tensors_;
    
    std::vector<Node> nodes_;
    
    std::vector<std::string> input_;
    std::vector<std::string> output_;
    
};

}

}