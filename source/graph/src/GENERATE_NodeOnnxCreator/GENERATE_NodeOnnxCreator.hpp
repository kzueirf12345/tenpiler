// Сгенерированный файл
// Не редактировать вручную

#pragma once

#include <onnx/onnx-ml.pb.h>

#include "graph/Node/Node.hpp"

namespace tenpiler {
namespace graph {
namespace onnx_parse {

Node CreateAdd(const onnx::NodeProto& onnx_node);
Node CreateMul(const onnx::NodeProto& onnx_node);
Node CreateConv(const onnx::NodeProto& onnx_node);
Node CreateGemm(const onnx::NodeProto& onnx_node);
Node CreateRelu(const onnx::NodeProto& onnx_node);
Node CreateMatMul(const onnx::NodeProto& onnx_node);

} // namespace onnx_parse
} // namespace graph
} // namespace tenpiler
