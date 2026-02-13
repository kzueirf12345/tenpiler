#include "graph/NodeFactory.hpp"

#include <memory>
#include <mutex>

#include "utils/common.hpp"
#include "graph/Node/Node.hpp"


namespace tenpiler {
namespace graph {

std::once_flag NodeFactory::init_registry_flag_ = {};
std::unordered_map<std::string, NodeFactory::CreateFunc_t> NodeFactory::registry_ = {};

void NodeFactory::EnsureInit_() {
    std::call_once(init_registry_flag_, InitRegistry_);
}

void NodeFactory::InitRegistry_() {
    Add::REGISTER_METHOD_NAME();
    Mul::REGISTER_METHOD_NAME();
    Conv::REGISTER_METHOD_NAME();
    Gemm::REGISTER_METHOD_NAME();
    MatMul::REGISTER_METHOD_NAME();
    Relu::REGISTER_METHOD_NAME();
} 

void NodeFactory::Register(const std::string name, const CreateFunc_t create_func) {
    if (!registry_.try_emplace(std::move(name), std::move(create_func)).second) {
        utils::THROW("Can't register " + name + " already exist");
    }
}

std::unique_ptr<Node> NodeFactory::Create(const onnx::NodeProto& onnx_node) {
    EnsureInit_();

    if (!onnx_node.has_op_type()) {
        utils::THROW("Can't create node without op_type");
    }

    const auto& op_type = onnx_node.op_type();
    
    auto it = registry_.find(op_type);
    if (it == registry_.end()) {
        utils::THROW("Unsupported node op_type " + op_type);
    }
    
    return it->second(onnx_node);
}


}
}