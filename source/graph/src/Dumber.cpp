#include <iostream>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

#include "graph/Dumber.hpp"
#include "RLogSU/graph.hpp"
#include "RLogSU/graph_appearance.hpp"
#include "RLogSU/logger.hpp"

#include "graph/Graph.hpp"
#include "graph/Node/Node.hpp"
#include "graph/Tensor.hpp"

namespace tenpiler {
namespace graph    {
namespace dump     {

std::string GetTensorLabel(const Tensor& tensor)
{
    std::string shape_str = (tensor.name + "\n");

    #define TYPE_TO_STR_SWITCH_(type) case Tensor::Type::type: shape_str += #type; break
    switch (tensor.type) {
        TYPE_TO_STR_SWITCH_(Unknown);
        TYPE_TO_STR_SWITCH_(Float16);
        TYPE_TO_STR_SWITCH_(Float32);
        TYPE_TO_STR_SWITCH_(Float64);
        TYPE_TO_STR_SWITCH_(Uint8  );
        TYPE_TO_STR_SWITCH_(Uint16 );
        TYPE_TO_STR_SWITCH_(Uint32 );
        TYPE_TO_STR_SWITCH_(Uint64 );
        TYPE_TO_STR_SWITCH_(Int8   );
        TYPE_TO_STR_SWITCH_(Int16  );
        TYPE_TO_STR_SWITCH_(Int32  );
        TYPE_TO_STR_SWITCH_(Int64  );
        TYPE_TO_STR_SWITCH_(String );
        TYPE_TO_STR_SWITCH_(Bool   );

        default: RLSU_THROW<std::runtime_error>("invalid tensor.type");
    }
    #undef TYPE_TO_STR_SWITCH_

    if (tensor.type == Tensor::Type::Unknown)
    {
        shape_str += "\n[???]";
        return shape_str;
    }

    shape_str += "\n[";

    if (tensor.shape.size() == 0)
    {
        shape_str += "]";
        return shape_str;
    }

    else
    {
        shape_str += std::to_string(tensor.shape[0]);
    }

    for (size_t i = 1; i < tensor.shape.size(); ++i)
    {
        shape_str +=  (" x " + std::to_string(tensor.shape[i]));
    }

    shape_str += "]";

    return shape_str;
}

static void InitTensor(RLSU::Graphics::Graph& dumb_graph, 
                       const Tensor& tensor)
{
    RLSU::Graphics::Graph::Node tensor_dumb(&tensor);
        
    tensor_dumb.SetShape(RLSU::Graphics::Shapes::NODE_DIAMOND);
    tensor_dumb.SetColor(RLSU::Graphics::Colors::GREY);

    tensor_dumb.SetLabel(GetTensorLabel(tensor));

    dumb_graph.AddNode(tensor_dumb);
}

static void InitNode(RLSU::Graphics::Graph& dumb_graph, 
                       const Node& node)
{
    RLSU::Graphics::Graph::Node node_dumb(&node);
    node_dumb.SetShape(RLSU::Graphics::Shapes::NODE_RECORD);
    node_dumb.SetLabel(std::string(node.getDot()));

    dumb_graph.AddNode(node_dumb);
}



void GraphDumb(const Graph& graph)
{
    RLSU::Graphics::Graph dumb_graph;

    for (const Node& node : graph.getNodes())
    {
        InitNode(dumb_graph, node);
    }

    for (const auto& [name, tensor] : graph.getTensors())
    {
        InitTensor(dumb_graph, tensor);
    }

    // InitDumbTensors(dumb_graph, graph.getTensors());

    for (const Node& node : graph.getNodes())
    {
        try {

        const auto& inputs  = node.getInputs();
        const auto& outputs = node.getOutputs();

        for (size_t i = 0; i < inputs.size(); i++)
        {
            const std::string& input_tensor_name = inputs[i];

            RLSU::Graphics::Graph::Edge edge = {.origin_ptr = &graph.getTensor(input_tensor_name) ,
                                                .dest_ptr   = &node                                     ,
                                                .label      = std::to_string(i)                     ,
                                                .arrowhead  = RLSU::Graphics::Shapes::EDGE_END_NORMAL    ,
                                                .arrowtail  = RLSU::Graphics::Shapes::EDGE_END_NONE     };

            dumb_graph.AddEdge(edge);
        }

        for (size_t i = 0; i < outputs.size(); i++)
        {
            const std::string& output_tensor_name = outputs[i];

            RLSU::Graphics::Graph::Edge edge = {.origin_ptr = &node                                     ,
                                                .dest_ptr   = &graph.getTensor(output_tensor_name) ,
                                                .label      = std::to_string(i)                     ,   
                                                .arrowhead  = RLSU::Graphics::Shapes::EDGE_END_NONE      ,
                                                .arrowtail  = RLSU::Graphics::Shapes::EDGE_END_DOT      };

            dumb_graph.AddEdge(edge);
        }


        } catch(std::exception& e)  {
            std::cerr << "exception in GraphDumb edges building: '" << e.what() << "'" << std::endl;
        }
    }

    dumb_graph.LogGraph();
}

} // namespace dump    
} // namespace graph
} // namespace tenplier