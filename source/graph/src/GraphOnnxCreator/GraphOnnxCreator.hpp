#pragma once

#include <onnx/onnx-ml.pb.h>

#include "graph/Graph.hpp"

namespace tenpiler {
namespace graph {
namespace onnx_parse {

Graph CreateGraph(const onnx::GraphProto& onnx_graph);

}
}
}