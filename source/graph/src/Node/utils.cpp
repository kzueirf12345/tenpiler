#include "graph/Node/utils.hpp"

#include "utils/common.hpp"

namespace tenpiler {
namespace graph {
namespace detail {

void CheckSize(size_t size, size_t req_size, const std::string& op_name, 
    const std::string& param_name) 
{
    if (size != req_size) {
        utils::THROW(
            "'" + op_name + "' must have " + std::to_string(req_size) + " " + param_name + 
            ", but has " + std::to_string(size)
        );
    }
}

void CheckSize(size_t size, size_t min_req_size, size_t max_req_size, 
    const std::string& op_name, const std::string& param_name) 
{
    if (size < min_req_size || size > max_req_size) {
        utils::THROW(
            "'" + op_name + "' must have from" + std::to_string(min_req_size) + " to " 
            + std::to_string(max_req_size) + " " + param_name + 
            ", but has " + std::to_string(size)
        );
    }
}

const onnx::AttributeProto* GetAttribute(const onnx::NodeProto& onnx_node, std::string_view name)
{
    const auto& onnx_attributes = onnx_node.attribute();
    
    for (const auto& onnx_attribute: onnx_attributes) {
        if (!onnx_attribute.has_name()) {
            continue;
        }
        if (onnx_attribute.name() == name) {
            return &onnx_attribute;
        }
    }
    return nullptr;
}

std::optional<int64_t> GetIntAttribute(const onnx::NodeProto& node, std::string_view name)
{
    const auto* attr = GetAttribute(node, name);
    if (!attr) return std::nullopt;
    
    if (!attr->has_type() || attr->type() != onnx::AttributeProto::INT) {
        utils::THROW(
            "Attribute '" + std::string(name) + "' has wrong type (expected INT)"
        );
    }
    
    return attr->i();
}

std::optional<float> GetFloatAttribute(const onnx::NodeProto& node, std::string_view name)
{
    const auto* attr = GetAttribute(node, name);
    if (!attr) return std::nullopt;
    
    if (!attr->has_type() || attr->type() != onnx::AttributeProto::FLOAT) {
        utils::THROW(
            "Attribute '" + std::string(name) + "' has wrong type (expected FLOAT)"
        );
    }
    
    return attr->f();
}

std::optional<std::vector<uint64_t>> GetIntsAttribute(const onnx::NodeProto& node, 
    std::string_view name)
{
    const auto* attr = GetAttribute(node, name);
    if (!attr) return std::nullopt;
    
    if (!attr->has_type() || attr->type() != onnx::AttributeProto::INTS) {
        utils::THROW(
            "Attribute '" + std::string(name) + "' has wrong type (expected INTS)"
        );
    }
    
    return std::vector<uint64_t>(attr->ints().begin(), attr->ints().end());
}

std::optional<std::string> GetStringAttribute(const onnx::NodeProto& node, std::string_view name)
{
    const auto* attr = GetAttribute(node, name);
    if (!attr) return std::nullopt;
    
    if (!attr->has_type() || attr->type() != onnx::AttributeProto::STRING) {
        utils::THROW(
            "Attribute '" + std::string(name) + "' has wrong type (expected STRING)"
        );
    }
    
    return attr->s();
}

std::optional<std::vector<std::string>> GetStringsAttribute(const onnx::NodeProto& node, 
    std::string_view name)
{
    const auto* attr = GetAttribute(node, name);
    if (!attr) return std::nullopt;
    
    if (!attr->has_type() || attr->type() != onnx::AttributeProto::STRINGS) {
        utils::THROW(
            "Attribute '" + std::string(name) + "' has wrong type (expected STRINGS)"
        );
    }
    
    return std::vector<std::string>(attr->strings().begin(), attr->strings().end());
}

}
}
}