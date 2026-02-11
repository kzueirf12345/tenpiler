#pragma once

#include <string>
#include <vector>

namespace tenpiler {
namespace graph {

struct Tenzor {
    std::string name;
    std::vector<uint64_t> shape;

    enum class Type {
        Unknown,
        Float32,
        Int64
    };

    Type type;
};

}
}