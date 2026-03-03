#pragma once

#include <vector>
#include <string>

struct NodeMeta {
    std::string op_type;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;

    friend bool operator==(const NodeMeta&, const NodeMeta&) = default;
};
