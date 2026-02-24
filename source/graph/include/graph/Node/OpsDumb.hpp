// Сгенерированный файл
// Не редактировать вручную

#pragma once

#include "Ops.hpp"

namespace tenpiler {
namespace graph {
namespace dump {

std::string_view GetDot(const Add& n);
std::string_view GetDot(const Mul& n);
std::string_view GetDot(const Sub& n);
std::string_view GetDot(const Div& n);
std::string_view GetDot(const Conv& n);
std::string_view GetDot(const MaxPool& n);
std::string_view GetDot(const Gemm& n);
std::string_view GetDot(const Relu& n);
std::string_view GetDot(const MatMul& n);

} // namespace dump
} // namespace graph
} // namespace tenpiler
