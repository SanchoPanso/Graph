#ifndef GRAPH_GRAPH_TARJANS_SCC_ALGORITHM_H
#define GRAPH_GRAPH_TARJANS_SCC_ALGORITHM_H

#include <stack>
#include "base_graph.h"

template<typename T>
class GraphTarjansSCCalgorithm : virtual public BaseGraph<T> {
private:
    void Tarjan_DFS(int current_node,
                    std::vector<int>& queue_num,
                    std::vector<int>& low_link,
                    std::vector<bool>& presents_in_stack,
                    std::stack<int>& stack_of_relatives);
    void Print_SCC(int head_of_SCC, std::stack<int>& stack_of_relatives, std::vector<bool>& presents_in_stack);
public:
    void Tarjan_SCC_algorithm();
};

#endif
