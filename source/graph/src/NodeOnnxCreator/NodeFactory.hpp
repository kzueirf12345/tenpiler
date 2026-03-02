#pragma once

#include <functional>
#include <onnx/onnx_pb.h>
#include "frozen/unordered_map.h"
#include "frozen/string.h"

#include "graph/Node/Node.hpp"
#include "NodeOnnxCreator.hpp"

namespace tenpiler {
namespace graph {
namespace onnx_parse {


class NodeFactory {

public:
    NodeFactory() = delete;

public:

    static Node Create(const onnx::NodeProto& onnx_node);

public:

    using CreateFunc_t = std::function<Node (const onnx::NodeProto& node_onnx)>;

private:

    inline static constexpr auto registry_ = 
        frozen::make_unordered_map<frozen::string, Node (*)(const onnx::NodeProto&)>({

#include "MAP_NodeOnnxCreator.hpp"

        });

};


}
}
}