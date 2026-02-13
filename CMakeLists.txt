cmake_minimum_required(VERSION 3.21)
project(tenpiler LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

###===========================================FLAGS=================================================

option(SANITIZE "Enable Sanitizers" OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_library(project_warnings INTERFACE)
    target_compile_options(project_warnings INTERFACE
        -Wall -Wextra -Werror -Wpedantic
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-O3 -DNDEBUG>
    )
endif()

if(SANITIZE AND NOT MSVC)
    add_library(project_sanitizers INTERFACE)
    target_compile_options(project_sanitizers INTERFACE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-optimize-sibling-calls
    )
    target_link_options(project_sanitizers INTERFACE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
endif()

###===========================================ONNX==================================================

# Find Protobuf 
find_package(Protobuf REQUIRED)
if(NOT Protobuf_FOUND)
    message(FATAL_ERROR "Protobuf not found")
endif()

# Find ONNX
find_path(ONNX_INCLUDE_DIR
    NAMES onnx/onnx-ml.pb.h
    PATHS /usr/local/include /usr/include
    REQUIRED
)

find_library(ONNX_LIBRARY
    NAMES onnx
    PATHS /usr/local/lib /usr/lib
    REQUIRED
)

find_library(ONNX_PROTO_LIBRARY
    NAMES onnx_proto
    PATHS /usr/local/lib /usr/lib
    REQUIRED
)

#Create targets
add_library(onnx::onnx SHARED IMPORTED)
set_target_properties(onnx::onnx PROPERTIES
    IMPORTED_LOCATION "${ONNX_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${ONNX_INCLUDE_DIR}"
)

add_library(onnx::onnx_proto SHARED IMPORTED)
set_target_properties(onnx::onnx_proto PROPERTIES
    IMPORTED_LOCATION "${ONNX_PROTO_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${ONNX_INCLUDE_DIR}"
)

###===========================================SUBDIRECTORY==========================================

add_subdirectory(source/graph)
add_subdirectory(source/utils)

add_executable(tenpiler source/main.cpp)

###===========================================LIB_LINK==============================================

target_link_libraries(tenpiler PRIVATE project_warnings)

if(SANITIZE AND NOT MSVC)
    target_link_libraries(tenpiler PRIVATE project_sanitizers)
endif()

target_link_libraries(tenpiler PRIVATE
    onnx::onnx
    onnx::onnx_proto
    ${Protobuf_LIBRARIES}

    graph
    utils
)