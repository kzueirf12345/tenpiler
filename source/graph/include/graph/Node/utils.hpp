#pragma once

#include "graph/Graph.hpp"
#include "graph/Tensor.hpp"
#include <cstddef>
#include <optional>
#include <string>

#include <onnx/onnx-ml.pb.h>

namespace tenpiler {
namespace graph {
namespace detail {

void CheckSize(size_t size, size_t req_size, const std::string& op_name, 
    const std::string& param_name);

void CheckSize(size_t size, size_t min_req_size, size_t max_req_size, 
    const std::string& op_name, const std::string& param_name);


const onnx::AttributeProto*             GetAttribute(
    const onnx::NodeProto& onnx_node, std::string_view name
);
std::optional<uint64_t>                  GetIntAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<float>                    GetFloatAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<std::vector<float>>       GetFloatsAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<std::vector<uint64_t>>    GetIntsAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<std::string>              GetStringAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<std::vector<std::string>> GetStringsAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<Tensor>                   GetTensorAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<std::vector<Tensor>>      GetTensorsAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<Graph>                   GetGraphAttribute(
    const onnx::NodeProto& node, std::string_view name
);
std::optional<std::vector<Graph>>      GetGraphsAttribute(
    const onnx::NodeProto& node, std::string_view name
);

}
}
}
