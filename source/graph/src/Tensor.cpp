#include "graph/Tensor.hpp"

#include <stdexcept>

#include <onnx/onnx-ml.pb.h>

namespace tenpiler {
namespace graph {

static Tensor::Type ParseOnnxTensorType(int onnx_type) {
    switch (onnx_type) {
        case onnx::TensorProto::DataType::TensorProto_DataType_FLOAT:  return Tensor::Type::Float32;
        case onnx::TensorProto::DataType::TensorProto_DataType_UINT8:  return Tensor::Type::Uint8;
        case onnx::TensorProto::DataType::TensorProto_DataType_INT8:   return Tensor::Type::Int8;
        case onnx::TensorProto::DataType::TensorProto_DataType_UINT16: return Tensor::Type::Uint16;
        case onnx::TensorProto::DataType::TensorProto_DataType_INT16:  return Tensor::Type::Int16;
        case onnx::TensorProto::DataType::TensorProto_DataType_INT32:  return Tensor::Type::Int32;
        case onnx::TensorProto::DataType::TensorProto_DataType_INT64:  return Tensor::Type::Int64;
        case onnx::TensorProto::DataType::TensorProto_DataType_STRING: return Tensor::Type::String;
        case onnx::TensorProto::DataType::TensorProto_DataType_BOOL:   return Tensor::Type::Bool;
        case onnx::TensorProto::DataType::TensorProto_DataType_FLOAT16:return Tensor::Type::Float16;
        case onnx::TensorProto::DataType::TensorProto_DataType_DOUBLE: return Tensor::Type::Float64;
        case onnx::TensorProto::DataType::TensorProto_DataType_UINT32: return Tensor::Type::Uint32;
        case onnx::TensorProto::DataType::TensorProto_DataType_UINT64: return Tensor::Type::Uint64;
        default:
            throw std::runtime_error("Unsopported onnx data type " 
                + onnx::TensorProto::DataType_Name(onnx_type));
    }
}

Tensor::Tensor(const onnx::ValueInfoProto& onnx_tensor) {
    if (!onnx_tensor.has_type() || !onnx_tensor.type().has_tensor_type())
    {
        throw std::runtime_error("tenpiler::graph::Tensor can't ctor from not tensor type");
    }

    if (!onnx_tensor.has_name()) {
        throw std::runtime_error("tenpiler::graph::Tensor can't ctor from tensor without name");
    }
    name = onnx_tensor.name();

    if (!onnx_tensor.type().tensor_type().has_elem_type()) {
        throw std::runtime_error("tenpiler::graph::Tensor can't ctor from tensor without elem type");
    }
    type = ParseOnnxTensorType(onnx_tensor.type().tensor_type().elem_type());

    if (!onnx_tensor.type().tensor_type().has_shape()) {
        shape = {};
    }
    else {
        const auto& shape_onnx = onnx_tensor.type().tensor_type().shape();
        shape.reserve(shape_onnx.dim_size());
        
        for (int dim_ind = 0; dim_ind < shape_onnx.dim_size(); ++dim_ind) {
            const auto& dim = shape_onnx.dim(dim_ind);
            
            if (dim.has_dim_value()) {
                shape.push_back(dim.dim_value());
            } else {
                throw std::runtime_error("Dimension " + std::to_string(dim_ind) + " has no value");
            }
        }
    }
}

Tensor::Tensor(const onnx::TensorProto& onnx_tensor) {
    if (!onnx_tensor.has_name()) {
        throw std::runtime_error("tenpiler::graph::Tensor can't ctor from tensor without name");
    }
    name = onnx_tensor.name();

    if (!onnx_tensor.has_data_type()) {
        throw std::runtime_error("tenpiler::graph::Tensor can't ctor from tensor without elem type");
    }
    type = ParseOnnxTensorType(onnx_tensor.data_type());

    shape.reserve(onnx_tensor.dims_size());
    
    for (int dim_ind = 0; dim_ind < onnx_tensor.dims_size(); ++dim_ind) {
        const auto dim = onnx_tensor.dims(dim_ind);
        
        if (dim > 0) {
            shape.push_back(dim);
        } else {
            throw std::runtime_error("Dimension " + std::to_string(dim_ind) + " has no value");
        }
    }
}

}
}
