// Сгенерированный файл
// Не редактировать вручную

#pragma once

#include "Ops.hpp"

namespace tenpiler {
namespace graph {
namespace dump {

std::string GetDot(const Add& n);
std::string GetDot(const Mul& n);
std::string GetDot(const Sub& n);
std::string GetDot(const Div& n);
std::string GetDot(const Conv& n);
std::string GetDot(const MaxPool& n);
std::string GetDot(const Gemm& n);
std::string GetDot(const Relu& n);
std::string GetDot(const MatMul& n);

} // namespace dump
} // namespace graph
} // namespace tenpiler
