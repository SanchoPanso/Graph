#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>
#include <tuple>
#include "../include/graph_floyd_warshall.h"
#include "../include/explixit_instantiation.h"

EXPLICIT_INSTANTIATION(GraphFloydWarshall);


//Floyd-Warshall algorithm without restore matrix
template<typename T>
std::vector<std::vector<T>> GraphFloydWarshall<T>::floyd_warshall() {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < vertices; intermediate++) {
        for (int origin = 0; origin < vertices; origin++) {
            for (int destination = 0; destination < vertices; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                BaseGraph<T>::adjacency_matrix[origin][destination] = min(origin, destination, intermediate);
            }
        }
    }
    return BaseGraph<T>::adjacency_matrix;
}

//Floyd-Warshall algorithm with restore matrix
template<typename T>
std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<int>>> GraphFloydWarshall<T>::floyd_warshall_ways() {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    //initializing vector to restore the paths
    restore_matrix.assign(vertices, std::vector<int>(vertices));
    for (int row = 0; row < vertices; row++) {
        for (int col = 0; col < vertices; col++) {
            if (BaseGraph<T>::adjacency_matrix[row][col] == INF<T>) {
                restore_matrix[row][col] = 0;
            }
            else
                restore_matrix[row][col] = col + 1;
        }
    }
    // Floyd-Warshall algorithm realization
    for (int intermediate = 0; intermediate < vertices; intermediate++) {
        for (int origin = 0; origin < vertices; origin++) {
            for (int destination = 0; destination < vertices; destination++) {
                //let paths_matrix = A, then
                //A(k)[x,y] = min(A(k-1)[x,y], A(k-1)[x,k] + A(k-1)[k,y])
                if (BaseGraph<T>::adjacency_matrix[origin][destination] > min(origin, destination, intermediate)) {
                    BaseGraph<T>::adjacency_matrix[origin][destination] = min(origin, destination, intermediate);
                    //saving previous nodes to restore paths
                    restore_matrix[origin][destination] = restore_matrix[origin][intermediate];
                }
            }
        }
    }
    //Check for negative cycle
    for (int node = 0; node < vertices; node++) {
        if (BaseGraph<T>::adjacency_matrix[node][node] != 0) {
            BaseGraph<T>::adjacency_matrix.clear();
            restore_matrix.clear();
        }
    }
    return make_tuple(BaseGraph<T>::adjacency_matrix, restore_matrix);
}

//Uses restore_matrix from Floyd_Warshall_ways to restore paths
template<typename T>
std::vector<int> GraphFloydWarshall<T>::restore_path(int from, int to) {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    restored_path.clear();
    if ((vertices < from) || (vertices < to)) return restored_path;
    if (restore_matrix.empty()) return restored_path;
    int current = from - 1;
    int destination = to - 1;
    if (BaseGraph<T>::adjacency_matrix[current][destination] == INF<T>) return restored_path;
    while (current != destination) {
        restored_path.push_back(current);
        current = restore_matrix[current][destination] - 1;
        if (current < 0) {
            restored_path.clear();
            return restored_path;
        }
    }
    restored_path.push_back(current);
    return restored_path;
}

//method finds if the way through an intermediate vertex is the shortest or not
template<typename T>
T GraphFloydWarshall<T>::min(int orig, int dest, int med) {
    T actual = BaseGraph<T>::adjacency_matrix[orig][dest];
    T alternative = 0;
    if (BaseGraph<T>::adjacency_matrix[orig][med] == INF<T> || BaseGraph<T>::adjacency_matrix[med][dest] == INF<T>) {
        alternative = INF<T>;
    }
    else {
        alternative = BaseGraph<T>::adjacency_matrix[orig][med] + BaseGraph<T>::adjacency_matrix[med][dest];
    }
    if (actual > alternative) return alternative;
    else return actual;
}
