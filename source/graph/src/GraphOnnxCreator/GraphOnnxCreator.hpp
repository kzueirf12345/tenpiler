#pragma once

#include <onnx/onnx_pb.h>

#include "graph/Graph.hpp"

namespace tenpiler {
namespace graph {
namespace onnx_parse {

Graph CreateGraph(const onnx::GraphProto& onnx_graph);

}
}
}