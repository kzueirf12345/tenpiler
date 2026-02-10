add_library(graph STATIC
    src/graph.cpp
)

target_include_directories(graph
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(graph PRIVATE project_warnings)

if(TARGET project_sanitizers)
    target_link_libraries(graph PRIVATE project_sanitizers)
endif()

# Гарантируем, что библиотека и бинарник используют одинаковые флаги
set_target_properties(graph PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)