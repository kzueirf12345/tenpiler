#pragma once
#include <iostream>
#include "Ops.hpp"

namespace tenpiler {
namespace graph {
namespace dump {

inline void draw_impl(const Add& n) {
    std::cout << "[Draw] Add Node: " << n.meta().op_type << std::endl;
}

inline void draw_impl(const Mul& n) {
    std::cout << "[Draw] Mul Node: " << n.meta().op_type << std::endl;
}

inline void draw_impl(const Conv& n) {
    std::cout << "[Draw] Conv Node: " << n.meta().op_type << std::endl;
}

inline void draw_impl(const Gemm& n) {
    std::cout << "[Draw] Gemm Node: " << n.meta().op_type << std::endl;
}

inline void draw_impl(const MatMul& n) {
    std::cout << "[Draw] MatMul Node: " << n.meta().op_type << std::endl;
}

inline void draw_impl(const Relu& n) {
    std::cout << "[Draw] Relu Node: " << n.meta().op_type << std::endl;
}

}
}
}