#ifndef GRAPH_GRAPH_TARJANS_BRIDGES_H
#define GRAPH_GRAPH_TARJANS_BRIDGES_H

#include <vector>
#include "base_graph.h"

template<typename T>
class GraphTarjansBridges : virtual public BaseGraph<T> {
protected:
    int tarjan_s_time = 0;
public:
    std::vector<std::pair<int, int>> tarjans_find_bridges();
private:
    void tarjan_s_bridge_finding_dfs(int u,
                                     std::vector<bool>& visited,
                                     std::vector<int>& disc,
                                     std::vector<int>& low,
                                     std::vector<int>& parent,
                                     std::vector<std::pair<int, int>>& bridges);
};


#endif
