#ifndef GRAPH_GRAPH_TRAVERSAL_H
#define GRAPH_GRAPH_TRAVERSAL_H

#include "base_graph.h"

template<typename T>
class GraphTraversal : virtual public BaseGraph<T> {
private:
    std::vector<T> restored_path;                   // Вектор для хранения пути между двумя вершинами
    std::vector<T> topological_sorted_graph;        // Топологически отсортированный граф
public:
    void print_vector(const std::vector<T> vector_to_print);
    std::vector<T> bfs_search();
    std::vector<T> dfs_search();
    std::vector<T> find_path(T from, T to);
    std::vector<T> topological_sort();
};

#endif //GRAPH_GRAPH_TRAVERSAL_H
