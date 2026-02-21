#pragma once

#include <istream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

#include "graph/Tensor.hpp"
#include "graph/Node/Node.hpp"

namespace tenpiler {
namespace graph {

class Graph {

public:

    Graph();
    ~Graph();

    Graph(const Graph&);
    Graph& operator=(const Graph&);

    Graph(Graph&&) noexcept;
    Graph& operator=(Graph&&) noexcept;

    void LoadFromOnnx(std::istream& input_onnx);

    [[nodiscard]] const std::vector<Node>&                       getNodes  () const noexcept;
    [[nodiscard]] const std::unordered_map<std::string, Tensor>& getTensors() const noexcept;
    [[nodiscard]] const std::vector<std::string>&                getInputs () const noexcept;
    [[nodiscard]] const std::vector<std::string>&                getOutputs() const noexcept;

    [[nodiscard]] const Tensor& getTensor(const std::string& name) const;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;
    
};

}

}