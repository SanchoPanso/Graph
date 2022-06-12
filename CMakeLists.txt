cmake_minimum_required(VERSION 3.20)
project(Graph)

set(CMAKE_CXX_STANDARD 14)

enable_testing()


add_library(graph
        src/base_graph.cpp
        src/graph_traversal.cpp
        src/graph_dijkstra.cpp
        src/graph_floyd_warshall.cpp
        src/graph_tarjans_bridges.cpp
        src/graph_tarjans_scc_algorithm.cpp
        src/graph.cpp)


# define a function to simplify adding tests
function(do_test target path)
    add_executable(${target} ${path})
    target_link_libraries(${target} graph)
    add_test(TestName_${target} ${target})
endfunction()

# do tests
do_test(vertex_test tests/Vertex_tests.cpp)
do_test(base_graph_test tests/BaseGraph_tests.cpp)
do_test(graph_tarjans_bridges_test tests/GraphTarjansBridges_tests.cpp)

# Install Rules
install(TARGETS graph DESTINATION ${PROJECT_SOURCE_DIR}/build/lib)
install(FILES graph.h DESTINATION ${PROJECT_SOURCE_DIR}/build/include)

