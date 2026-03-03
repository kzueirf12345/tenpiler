enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(graph_tests 
  parsing.cpp
  
  print_to/print_to.cpp
)

target_link_libraries(graph_tests PRIVATE 
  graph
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(graph_tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
