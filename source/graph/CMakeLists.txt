add_library(graph STATIC
    src/Graph.cpp

    src/TensorOnnxCreator/TensorOnnxCreator.cpp
    src/NodeOnnxCreator/NodeOnnxCreator.cpp
    src/NodeOnnxCreator/NodeFactory.cpp

    src/Node/Add.cpp
    src/Node/Conv.cpp
    src/Node/Gemm.cpp
    src/Node/MatMul.cpp
    src/Node/Mul.cpp
    src/Node/Relu.cpp
    src/Node/utils.cpp
)

target_include_directories(graph
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(graph PRIVATE project_warnings)

if(TARGET project_sanitizers)
    target_link_libraries(graph PRIVATE project_sanitizers)
endif()

target_link_libraries(graph 
PRIVATE 
    utils
)

set_target_properties(graph PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)