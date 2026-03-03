#include "graph/Graph.hpp"
#include "graph/Tensor.hpp"
#include "graph/Dumber.hpp"
#include "../graph_test_data.hpp"


namespace tenpiler {
namespace graph    { 

void PrintTo(const Tensor& tensor, std::ostream* os)
{
    *os << dump::GetTensorLabel(tensor);
}


void PrintTo(const Node& node  , std::ostream* os)
{
    *os << node.getDot();
}

} // namespace graph
} // namespace tenpiler


namespace tenpiler {
namespace tests    {
    
void PrintTo(const ::tenpiler::tests::GraphTestData& data, std::ostream* os) 
{
    *os << "{ file: \"" << data.filepath << "\" }";
}

} // namespace tests
} // namespace tenpiler