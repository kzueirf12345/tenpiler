###===========================================CODEGEN===============================================
find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(CODEGEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/codegen)
set(OPS_GENERATOR ${CODEGEN_DIR}/OpsGenerator.py)

file(GLOB_RECURSE CODEGEN_DEP_FILES CONFIGURE_DEPENDS 
    "${CODEGEN_DIR}/*.py" 
    "${CODEGEN_DIR}/*.json"
)

set(CODEGEN_STAMP ${CMAKE_CURRENT_BINARY_DIR}/ops_codegen.stamp)

add_custom_command(
    OUTPUT ${CODEGEN_STAMP}
    COMMAND Python3::Interpreter ${OPS_GENERATOR}
    COMMAND ${CMAKE_COMMAND} -E touch ${CODEGEN_STAMP}

    DEPENDS ${CODEGEN_DEP_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Run OpsGenerator..."

    VERBATIM    # типа независимость от операционки хз
)

add_custom_target(generate_ops DEPENDS ${CODEGEN_STAMP})


# чтобы смейк не упал в случае когда файлы не сгенерены
# в момент вызова 'cmake -B build -S .'
set_source_files_properties(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Node/OpsDumb.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Node/OpsAttr.cpp

    PROPERTIES 
        GENERATED TRUE
)


###===========================================graph=================================================
add_library(graph STATIC
    src/Graph.cpp
    src/Dumber.cpp    

    src/TensorOnnxCreator/TensorOnnxCreator.cpp
    src/NodeOnnxCreator/NodeOnnxCreator.cpp
    src/NodeOnnxCreator/NodeFactory.cpp
    src/GraphOnnxCreator/GraphOnnxCreator.cpp

    src/Node/Node.cpp
    src/Node/utils.cpp
    src/Node/OpsDumb.cpp
    src/Node/OpsAttr.cpp
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
    RLogSU
    utils
    onnx::onnx
    onnx::onnx_proto
    ${Protobuf_LIBRARIES}
)

set_target_properties(graph PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

add_dependencies(graph generate_ops)

target_compile_definitions(graph PUBLIC ONNX_ML=1)
