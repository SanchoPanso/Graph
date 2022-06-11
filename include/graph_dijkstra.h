#ifndef GRAPH_GRAPH_DIJKSTRA_H
#define GRAPH_GRAPH_DIJKSTRA_H

#include <vector>
#include "base_graph.h"

template<typename T>
class GraphDijkstra : virtual public BaseGraph<T> {
public:
    std::vector<std::vector<T>> dijkstra();
    int dijkstra_log(int top_from, int top_to);
private:
    std::vector<T> dijkstra_from_one_vertex(int origin);
};

#endif //GRAPH_GRAPH_DIJKSTRA_H
