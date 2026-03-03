#include <gtest/gtest.h>

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph/Graph.hpp"
#include "graph/Node/Ops.hpp"
#include "graph/Tensor.hpp"

#include "graph_test_data.hpp"

#include "print_to/print_to.hpp"

namespace tenpiler {
namespace tests    {

using namespace graph;


class GraphParserTest : public ::testing::TestWithParam<GraphTestData> {};

TEST_P(GraphParserTest, ParseCorrectness) {

    const GraphTestData& param = GetParam();

    std::ifstream file(param.filepath, std::ios::binary);
    ASSERT_TRUE(file.is_open());

    Graph graph;
    ASSERT_NO_THROW(graph.LoadFromOnnx(file)) 
        << "LoadFromOnnx throwed exception";

    EXPECT_EQ(graph.getTensors(), param.expected_tensors) 
        << "The set of parsed tensors does not match the expected one";

    auto node_cmp = [](const tenpiler::graph::Node& lhs, const tenpiler::graph::Node& rhs) {
        return lhs.sayMyName () == rhs.sayMyName () &&
               lhs.getInputs () == rhs.getInputs () &&
               lhs.getOutputs() == rhs.getOutputs();
    };

    // std::is_permutation игнорирует порядок элементов в std::vector
    const auto& parsed_nodes = graph.getNodes();
    EXPECT_TRUE(std::is_permutation(
        parsed_nodes.begin(), parsed_nodes.end(),
        param.expected_nodes.begin(), param.expected_nodes.end(),
        node_cmp
    )) 
        << "The set of parsed nodes does not match the expected one";

    EXPECT_EQ(graph.getInputs (), param.expected_input);
    EXPECT_EQ(graph.getOutputs(), param.expected_output);
}

// GraphTestData{
//             // std::string filepath
//             "onnx_simple/add.onnx", 

//             // std::vector<Node> expected_nodes
//             {
//                 // Внимание: требуется наличие конструктора Node(std::string, std::vector<std::string>, std::vector<std::string>)
//                 Add{{"x", "y"}, {"sum"}} 
//             },

//             // std::unordered_map<std::string, Tensor> expected_tensors
//             {
//                 {"x",   Tensor{"x",   {3, 4, 5}, Tensor::Type::Float32}},
//                 {"y",   Tensor{"y",   {3, 4, 5}, Tensor::Type::Float32}},
//                 {"sum", Tensor{"sum", {3, 4, 5}, Tensor::Type::Float32}}
//             },

//             // std::vector<std::string> expected_input
//             {"x", "y"}, 

//             // std::vector<std::string> expected_output
//             {"sum"}
//         },
INSTANTIATE_TEST_SUITE_P(
    SimpleOnnxFiles,
    GraphParserTest,
    ::testing::Values(

        GraphTestData{
            // std::string filepath
            "onnx_simple/add.onnx",

            // std::vector<Node> expected_nodes
            { Add{{"x", "y"}, {"sum"}} },

            // std::unordered_map<std::string, Tensor> expected_tensors
            {
                {"x",   Tensor{"x",   {3, 4, 5}, Tensor::Type::Float32}},
                {"y",   Tensor{"y",   {3, 4, 5}, Tensor::Type::Float32}},
                {"sum", Tensor{"sum", {3, 4, 5}, Tensor::Type::Float32}}
            },

            // std::vector<std::string> expected_input
            {"x", "y"}, 
            // std::vector<std::string> expected_output
            {"sum"}
        },

        GraphTestData{
            "onnx_simple/mul.onnx", 
            { Mul{{"x", "y"}, {"z"}} },
            {
                {"x", Tensor{"x", {3, 4, 5}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {3, 4, 5}, Tensor::Type::Float32}},
                {"z", Tensor{"z", {3, 4, 5}, Tensor::Type::Float32}}
            },
            {"x", "y"}, 
            {"z"}
        },

        GraphTestData{
            "onnx_simple/matmul.onnx", 
            { MatMul{{"a", "b"}, {"c"}} },
            {
                {"a", Tensor{"a", {1, 2, 3, 4}, Tensor::Type::Float32}},
                {"b", Tensor{"b", {1, 2, 4, 3}, Tensor::Type::Float32}},
                {"c", Tensor{"c", {1, 2, 3, 3}, Tensor::Type::Float32}}
            },
            {"a", "b"}, 
            {"c"}
        },

        GraphTestData{
            "onnx_simple/maxpool0.onnx", 
            { MaxPool{{"x"}, {"y"}, /*plug*/ {0}} },
            {
                {"x", Tensor{"x", {1, 3, 32}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {1, 3, 31}, Tensor::Type::Float32}}
            },
            {"x"}, 
            {"y"}
        },

        GraphTestData{
            "onnx_simple/maxpool1.onnx", 
            { MaxPool{{"x"}, {"y"}, /*plug*/ {0}} },
            {
                {"x", Tensor{"x", {1, 1, 4, 4}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {1, 1, 2, 2}, Tensor::Type::Float32}}
            },
            {"x"}, 
            {"y"}
        },

        GraphTestData{
            "onnx_simple/conv0.onnx", 
            { Conv{{"x", "W"}, {"y"}, /*plug*/ {0}} },
            {
                {"x", Tensor{"x", {1, 1, 5, 5}, Tensor::Type::Float32}},
                {"W", Tensor{"W", {1, 1, 3, 3}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {1, 1, 3, 3}, Tensor::Type::Float32}}
            },
            {"x", "W"}, 
            {"y"}
        },

        GraphTestData{
            "onnx_simple/conv1.onnx", 
            { Conv{{"x", "W"}, {"y"}, /*plug*/ {0}} },
            {
                {"x", Tensor{"x", {1, 1, 7, 5}, Tensor::Type::Float32}},
                {"W", Tensor{"W", {1, 1, 3, 3}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {1, 1, 4, 3}, Tensor::Type::Float32}}
            },
            {"x", "W"}, 
            {"y"}
        },

        GraphTestData{
            "onnx_simple/conv2.onnx", 
            { Conv{{"x", "W"}, {"y"}, /*plug*/ {0}} },
            {
                {"x", Tensor{"x", {1, 1, 7, 5}, Tensor::Type::Float32}},
                {"W", Tensor{"W", {1, 1, 3, 3}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {1, 1, 4, 2}, Tensor::Type::Float32}}
            },
            {"x", "W"}, 
            {"y"}
        },

        GraphTestData{
            "onnx_simple/conv3.onnx", 
            { Conv{{"x", "W"}, {"y"}, /*plug*/ {0}} },
            {
                {"x", Tensor{"x", {1, 1, 7, 5}, Tensor::Type::Float32}},
                {"W", Tensor{"W", {1, 1, 3, 3}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {1, 1, 3, 2}, Tensor::Type::Float32}}
            },
            {"x", "W"}, 
            {"y"}
        },

        GraphTestData{
            "onnx_simple/div.onnx", 
            { Div{{"x", "y"}, {"z"}} },
            {
                {"x", Tensor{"x", {3, 4, 5}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {3, 4, 5}, Tensor::Type::Float32}},
                {"z", Tensor{"z", {3, 4, 5}, Tensor::Type::Float32}}
            },
            {"x", "y"}, 
            {"z"}
        },

        GraphTestData{
            "onnx_simple/gemm.onnx", 
            { Gemm{{"a", "b", "c"}, {"y"}} },
            {
                {"a", Tensor{"a", {4, 3}, Tensor::Type::Float32}},
                {"b", Tensor{"b", {5, 4}, Tensor::Type::Float32}},
                {"c", Tensor{"c", {1, 5}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {3, 5}, Tensor::Type::Float32}}
            },
            {"a", "b", "c"}, 
            {"y"}
        },

        GraphTestData{
            "onnx_simple/relu.onnx", 
            { Relu{{"x"}, {"y"}} },
            {
                {"x", Tensor{"x", {3, 4, 5}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {3, 4, 5}, Tensor::Type::Float32}}
            },
            {"x"}, 
            {"y"}
        },

        GraphTestData{
            "onnx_simple/sub.onnx", 
            { Sub{{"x", "y"}, {"z"}} },
            {
                {"x", Tensor{"x", {3, 4, 5}, Tensor::Type::Float32}},
                {"y", Tensor{"y", {3, 4, 5}, Tensor::Type::Float32}},
                {"z", Tensor{"z", {3, 4, 5}, Tensor::Type::Float32}}
            },
            {"x", "y"}, 
            {"z"}
        }
    )
);

} // namespace tests
} // namespace tenpiler 