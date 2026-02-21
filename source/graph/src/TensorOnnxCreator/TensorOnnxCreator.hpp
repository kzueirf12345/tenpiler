#pragma once

#include <onnx/onnx-ml.pb.h>

#include "graph/Tensor.hpp"

namespace tenpiler {
namespace graph {
namespace onnx_parse {

Tensor CreateTensor(const onnx::ValueInfoProto& onnx_tensor);
Tensor CreateTensor(const onnx::TensorProto&    onnx_tensor);

}
}
}