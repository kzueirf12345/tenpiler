// Сгенерированный файл
// Не редактировать вручную

#pragma once

#include <any>
#include <string>

#include "graph/Node/Ops.hpp"

namespace tenpiler {
namespace graph {

std::any GetAttribute(const Add& node, const std::string& name);
std::any GetAttribute(const Mul& node, const std::string& name);
std::any GetAttribute(const Sub& node, const std::string& name);
std::any GetAttribute(const Div& node, const std::string& name);
std::any GetAttribute(const Conv& node, const std::string& name);
std::any GetAttribute(const MaxPool& node, const std::string& name);
std::any GetAttribute(const Gemm& node, const std::string& name);
std::any GetAttribute(const Relu& node, const std::string& name);
std::any GetAttribute(const MatMul& node, const std::string& name);

} // namespace graph
} // namespace tenpiler
