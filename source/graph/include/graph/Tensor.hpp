#pragma once

#include <string>
#include <vector>
#include <stdint.h>

namespace tenpiler {
namespace graph {

struct Tensor {

public:

    std::string name;
    std::vector<uint64_t> shape;

    enum class Type {
        Unknown = 0,
        Float16 = 1,
        Float32 = 2,
        Float64 = 3,
        Uint8   = 4,
        Uint16  = 5,
        Uint32  = 6,
        Uint64  = 7,
        Int8    = 8,
        Int16   = 9,
        Int32   = 10,
        Int64   = 11,
        String  = 12,
        Bool    = 13,
    };

    Type type = Tensor::Type::Unknown;
};

}
}