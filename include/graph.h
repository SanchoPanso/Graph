#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <list>

#include "base_graph.h"
#include "graph_tarjans_bridges.h"
#include "graph_floyd_warshall.h"
#include "graph_dijkstra.h"
#include "graph_traversal.h"
#include "graph_tarjans_scc_algorithm.h"


// Итоговый класс графа, наследующийся как virtual public от всех классов, реализующих алгоритмы,
// т.е. создающийся с помощью ромбовидного наследования

template<typename T>
class Graph :
        virtual public GraphTarjansBridges<T>,
        virtual public GraphFloydWarshall<T>,
        virtual public GraphDijkstra<T>,
        virtual public GraphTraversal<T>,
        virtual public GraphTarjansSCCalgorithm<T> {
public:
    explicit Graph(int num_of_vertices = 0) : BaseGraph<T>(num_of_vertices) {};
    explicit Graph(std::vector<std::vector<T>>& adjacency_matrix) : BaseGraph<T>(adjacency_matrix) {};
    explicit Graph(std::vector<std::list<int>>& adjacency_list) : BaseGraph<T>(adjacency_list) {};
    Graph(const Graph& other) : BaseGraph<T>(other) {};
    Graph(Graph&& other) noexcept : BaseGraph<T>(other) {};
    virtual ~Graph() = default;
};

#endif