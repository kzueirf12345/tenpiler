#pragma once

#include <functional>
#include <memory>

#include <onnx/onnx-ml.pb.h>


namespace tenpiler {
namespace graph {

class Node;

class NodeFactory {

public:
    NodeFactory() = delete;

public:

    static std::unique_ptr<Node> Create(const onnx::NodeProto& onnx_node);

public:

#define REGISTER_METHOD_NAME Register

    using CreateFunc_t = std::function<std::unique_ptr<Node>(const onnx::NodeProto& node_onnx)>;

    static void Register(const std::string name, const CreateFunc_t create_func);

private:

    static void EnsureInit_();

    static void InitRegistry_();

    static std::unordered_map<std::string, CreateFunc_t> registry_;

    static std::once_flag init_registry_flag_;
    
};


}
}