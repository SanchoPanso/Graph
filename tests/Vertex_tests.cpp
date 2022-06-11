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


void vertex_add_edge_test();
void vertex_remove_edge_test();


int main() {

    vertex_add_edge_test();
    vertex_remove_edge_test();

    return 0;
}


void vertex_add_edge_test() {

    std::cout << std::endl << "====== Vertex add edge test ======" << std::endl;

    Vertex<int> vtx;
    size_t num_of_neighbors = 0;

    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(0, num_of_neighbors, "Vertex has 0 edges");

    Vertex<int> neighbor_1;
    vtx.add_edge(&neighbor_1, 0);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(1, num_of_neighbors, "Vertex has 1 edges after adding");

    Vertex<int> neighbor_2;
    vtx.add_edge(&neighbor_2, 0);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(2, num_of_neighbors, "Vertex has 2 edges after adding");
}



void vertex_remove_edge_test() {

    std::cout << std::endl << "====== Vertex remove edge test ======" << std::endl;

    Vertex<int> vtx;
    size_t num_of_neighbors = 0;

    Vertex<int> neighbor_1;
    Vertex<int> neighbor_2;
    vtx.add_edge(&neighbor_1, 0);
    vtx.add_edge(&neighbor_2, 0);
    std::cout << vtx.get_edges().size() << std::endl;

    vtx.remove_edge(&neighbor_2);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(1, num_of_neighbors, "Neighbor_2 removed");

    Vertex<int> neighbor_3;
    vtx.remove_edge(&neighbor_3);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(1, num_of_neighbors, "Neighbor_3 did not remove");

    vtx.remove_edge(&neighbor_1);
    num_of_neighbors = vtx.get_edges().size();
    CHECK_EQUAL(0, num_of_neighbors, "Neighbor_2 removed");
}
