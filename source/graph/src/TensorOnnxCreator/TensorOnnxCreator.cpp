#include <onnx/onnx_pb.h>

#include "TensorOnnxCreator.hpp"
#include "graph/Tensor.hpp"
#include "utils/common.hpp"

namespace tenpiler {
namespace graph {
namespace onnx_parse {

static Tensor::Type CreateOnnxTensorType(int onnx_type) {
    switch (onnx_type) {
        case onnx::TensorProto::DataType::TensorProto_DataType_FLOAT  : return Tensor::Type::Float32;
        case onnx::TensorProto::DataType::TensorProto_DataType_UINT8  : return Tensor::Type::Uint8;
        case onnx::TensorProto::DataType::TensorProto_DataType_INT8   : return Tensor::Type::Int8;
        case onnx::TensorProto::DataType::TensorProto_DataType_UINT16 : return Tensor::Type::Uint16;
        case onnx::TensorProto::DataType::TensorProto_DataType_INT16  : return Tensor::Type::Int16;
        case onnx::TensorProto::DataType::TensorProto_DataType_INT32  : return Tensor::Type::Int32;
        case onnx::TensorProto::DataType::TensorProto_DataType_INT64  : return Tensor::Type::Int64;
        case onnx::TensorProto::DataType::TensorProto_DataType_STRING : return Tensor::Type::String;
        case onnx::TensorProto::DataType::TensorProto_DataType_BOOL   : return Tensor::Type::Bool;
        case onnx::TensorProto::DataType::TensorProto_DataType_FLOAT16: return Tensor::Type::Float16;
        case onnx::TensorProto::DataType::TensorProto_DataType_DOUBLE : return Tensor::Type::Float64;
        case onnx::TensorProto::DataType::TensorProto_DataType_UINT32 : return Tensor::Type::Uint32;
        case onnx::TensorProto::DataType::TensorProto_DataType_UINT64 : return Tensor::Type::Uint64;
        default:
            utils::THROW("Unsopported onnx data type " 
                + onnx::TensorProto::DataType_Name(onnx_type));
    }

    return Tensor::Type::Int8;
}

Tensor CreateTensor(const onnx::ValueInfoProto& onnx_tensor) {

    Tensor result;

    if (!onnx_tensor.has_type() || !onnx_tensor.type().has_tensor_type())
    {
        utils::THROW("tenpiler::graph::Tensor can't ctor from not tensor type");
    }

    if (!onnx_tensor.has_name()) {
        utils::THROW("tenpiler::graph::Tensor can't ctor from tensor without name");
    }
    result.name = onnx_tensor.name();

    if (!onnx_tensor.type().tensor_type().has_elem_type()) {
        utils::THROW("tenpiler::graph::Tensor can't ctor from tensor without elem type");
    }
    result.type = CreateOnnxTensorType(onnx_tensor.type().tensor_type().elem_type());

    if (!onnx_tensor.type().tensor_type().has_shape()) {
        result.shape = {};
    }
    else {
        const auto& shape_onnx = onnx_tensor.type().tensor_type().shape();
        result.shape.reserve(shape_onnx.dim_size());
        
        for (int dim_ind = 0; dim_ind < shape_onnx.dim_size(); ++dim_ind) {
            const auto& dim = shape_onnx.dim(dim_ind);
            
            if (dim.has_dim_value()) {
                result.shape.push_back(dim.dim_value());
            } 
            else {
                utils::THROW("Dimension " + std::to_string(dim_ind) + " has no value");
            }
        }
    }

    return result;
}

Tensor CreateTensor(const onnx::TensorProto& onnx_tensor) {

    Tensor result;

    if (!onnx_tensor.has_name()) {
        utils::THROW("tenpiler::graph::Tensor can't ctor from tensor without name");
    }
    result.name = onnx_tensor.name();

    if (!onnx_tensor.has_data_type()) {
        utils::THROW("tenpiler::graph::Tensor can't ctor from tensor without elem type");
    }
    result.type = CreateOnnxTensorType(onnx_tensor.data_type());

    result.shape.reserve(onnx_tensor.dims_size());
    
    for (int dim_ind = 0; dim_ind < onnx_tensor.dims_size(); ++dim_ind) {
        const auto dim = onnx_tensor.dims(dim_ind);
        
        if (dim > 0) {
            result.shape.push_back(dim);
        } else {
            utils::THROW("Dimension " + std::to_string(dim_ind) + " has no value");
        }
    }

    return result;
}

}
}
}