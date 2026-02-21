#include "NodeFactory.hpp"

// #include <mutex>

#include "utils/common.hpp"
#include "graph/Node/Node.hpp"


namespace tenpiler {
namespace graph {
namespace onnx_parse {

Node NodeFactory::Create(const onnx::NodeProto& onnx_node) {

    if (!onnx_node.has_op_type()) {
        utils::THROW("Can't create node without op_type");
    }

    const auto& op_type = onnx_node.op_type();
    
    auto it = registry_.find(frozen::string(op_type.data(), op_type.size()));
    if (it == registry_.end()) {
        utils::THROW("Unsupported node op_type " + op_type);
    }
    
    return it->second(onnx_node);
}


}
}
}