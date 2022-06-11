#include "../include/graph.h"
#include <iostream>


# define CHECK_EQUAL(expected, got, test_name) {                    \
    if ((got) == (expected)) {                                      \
        std::cout << test_name << ":\tpass" << std::endl;           \
    } else {                                                        \
        std::cout << test_name << ":\tfailed" << std::endl;         \
        std::cout << "Expected: " << expected << std::endl;         \
        std::cout << "Got: " << got << std::endl;                   \
        exit(1);                                                    \
    }                                                               \
}                                                                   \


# define CHECK_NOT_EQUAL(expected, got, test_name) {                \
    if ((got) != (expected)) {                                      \
        std::cout << test_name << ":\tpass" << std::endl;           \
    } else {                                                        \
        std::cout << test_name << ":\tfailed" << std::endl;         \
        std::cout << "Expected: " << expected << std::endl;         \
        std::cout << "Got: " << got << std::endl;                   \
        exit(1);                                                    \
    }                                                               \
}                                                                   \



void empty_graph_test();
void graph_without_edges_test(int num_of_vertices);
void chain_graph_test(int num_of_vertices);
void dense_graph_test(int num_of_vertices);


int main() {

    std::cout << "====== Empty graph test ======" << std::endl;
    empty_graph_test();


    std::cout << "====== Graph without edges test ======" << std::endl;
    graph_without_edges_test(1);
    graph_without_edges_test(2);
    graph_without_edges_test(3);
    graph_without_edges_test(4);


    std::cout << "====== Chain graph test ======" << std::endl;
    chain_graph_test(3);
    chain_graph_test(5);
    chain_graph_test(10);


    std::cout << "====== Dense graph test ======" << std::endl;
    dense_graph_test(3);
    dense_graph_test(10);
    dense_graph_test(20);

    return 0;
}


void empty_graph_test() {
    Graph<int> graph;
    auto bridges = graph.tarjans_find_bridges();

    CHECK_EQUAL(true, bridges.empty(), "Test empty graph")
}


void graph_without_edges_test(int num_of_vertices) {
    Graph<int> graph(num_of_vertices);
    auto bridges = graph.tarjans_find_bridges();

    graph.actualize_adjacency_matrix(); //
    std::string message = "Graph with " + std::to_string(num_of_vertices) + " vertices and without edges test";
    CHECK_EQUAL(true, bridges.empty(), message)
}


void chain_graph_test(int num_of_vertices) {
    Graph<int> graph(num_of_vertices);
    for (int i = 0; i < num_of_vertices - 1; i++) {
        graph.add_edge(i, i + 1);
    }
    graph.actualize_adjacency_matrix(); //
    auto bridges = graph.tarjans_find_bridges();

    std::string message = "Chain graph with " + std::to_string(num_of_vertices) + " vertices test";
    CHECK_EQUAL(num_of_vertices - 1, bridges.size(), message);
}


void dense_graph_test(int num_of_vertices) {
    Graph<int> graph(num_of_vertices);
    for (int i = 0; i < num_of_vertices; i++) {
        for (int j = i + 1; j < num_of_vertices; j++) {
            graph.add_edge(i, j);
        }
    }
    graph.actualize_adjacency_matrix(); // change
    auto bridges = graph.tarjans_find_bridges();

    std::string message = "Dense graph with " + std::to_string(num_of_vertices) + " vertices test";
    CHECK_EQUAL(0, bridges.size(), message);
}
