#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdint>
#include <tuple>
#include "../include/graph_traversal.h"
#include "../include/explixit_instantiation.h"


EXPLICIT_INSTANTIATION(GraphTraversal);


template<typename T>
void GraphTraversal<T>::print_vector(std::vector<T> vector_to_print) {
    std::cout << std::endl;
    for (int i = 0; i < vector_to_print.size(); i++) {
        std::cout << vector_to_print[i] << " ";
    }
}

template<typename T>
std::vector<T> GraphTraversal<T>::bfs_search() { // BFS search
    std::vector<T> bfs_search;
    std::vector<T> nodes(BaseGraph<T>::adjacency_list.size(), 0);
    std::queue<T> Queue;
    Queue.push(0);
    while (!Queue.empty()) {
        T node = Queue.front();
        Queue.pop();
        nodes[node] = 2;
        for (auto iter = BaseGraph<T>::adjacency_list[node].begin();
             iter != BaseGraph<T>::adjacency_list[node].end(); ++iter) {
            if (nodes[*iter] == 0) {
                Queue.push(*iter);
                nodes[*iter] = 1;
            }
        }
        bfs_search.push_back(node);
    }
    return bfs_search;
}

template<typename T>
std::vector<T> GraphTraversal<T>::dfs_search() {  // DFS search
    std::vector<T> dfs_search;
    std::vector<T> nodes(BaseGraph<T>::adjacency_list.size(), 0);
    std::stack<T> Stack;
    Stack.push(0);
    while (!Stack.empty()) {
        T node = Stack.top();
        Stack.pop();
        if (nodes[node] == 2) continue;
        nodes[node] = 2;
        for (auto iter = BaseGraph<T>::adjacency_list[node].rbegin();
             iter != BaseGraph<T>::adjacency_list[node].rend(); ++iter) {
            if (nodes[*iter] != 2) {
                Stack.push(*iter);
                nodes[*iter] = 1;
            }
        }
        dfs_search.push_back(node);
    }
    return dfs_search;
}

template<typename T>
std::vector<T> GraphTraversal<T>::find_path(T from, T to) {   // BFS based find path
    if (from >= BaseGraph<T>::adjacency_list.size() ||
        to >= BaseGraph<T>::adjacency_list.size()) {
        std::cout << "Find min path error. "
                     "Index exceeds the number of vertices. Index must be not more "
                  << BaseGraph<T>::adjacency_list.size() - 1 << "\n";
        return restored_path;
    }
    if (from == to) {
        std::cout << "Find min path error. Check entrance and exit.";
        return restored_path;
    }
    std::vector<T> nodes(BaseGraph<T>::adjacency_list.size(), 0);
    std::queue<T> Queue;
    struct Edge {
        T begin;
        T end;
    };
    Edge Edge_beetween_two_vertices;
    std::stack<Edge> Edges;
    Queue.push(from);
    bool path_found = false;
    while (!Queue.empty() && !path_found) {
        T node = Queue.front();
        Queue.pop();
        nodes[node] = 2;
        for (auto iter = BaseGraph<T>::adjacency_list[node].begin();
             iter != BaseGraph<T>::adjacency_list[node].end(); ++iter) {
            if (nodes[*iter] == 0) {
                nodes[*iter] = 1;
                Queue.push(*iter);
                Edge_beetween_two_vertices.begin = node;
                Edge_beetween_two_vertices.end = *iter;
                Edges.push(Edge_beetween_two_vertices);
                if (*iter == to) {
                    path_found = true;
                    break;
                }
            }
        }
    }
    if (path_found) {
        while (to != from) {
            Edge_beetween_two_vertices = Edges.top();
            Edges.pop();
            if (Edge_beetween_two_vertices.end == to) {
                to = Edge_beetween_two_vertices.begin;
                restored_path.push_back(Edge_beetween_two_vertices.end);
            }
        }
        restored_path.push_back(from);
        std::reverse(restored_path.begin(), restored_path.end());
    }
    else {
        std::cout << "No path from " << from << " to " << to << ".";
    }
    return restored_path;
}

template<typename T>
std::vector<T> GraphTraversal<T>::topological_sort() { // DFS based topological sort
    //graph is DAG check required
    std::vector<T> nodes(BaseGraph<T>::adjacency_list.size(), 0);
    std::stack<T> Stack;
    for (int i = 0; i < BaseGraph<T>::adjacency_list.size(); ++i) {
        Stack.push(i);
        while (!Stack.empty()) {
            T node = Stack.top();
            if (nodes[node] == 2) {
                Stack.pop();
                continue;
            }
            if (nodes[node] == 1) {
                topological_sorted_graph.push_back(node);
                Stack.pop();
                nodes[node] = 2;
                continue;
            }
            nodes[node] = 1;
            bool has_edge = false;
            for (auto iter = BaseGraph<T>::adjacency_list[node].rbegin();
                 iter != BaseGraph<T>::adjacency_list[node].rend(); ++iter) {
                if (nodes[*iter] != 2) {
                    Stack.push(*iter);
                    has_edge = true;
                }
            }
            if (!has_edge) {
                topological_sorted_graph.push_back(node);
                Stack.pop();
                nodes[node] = 2;
            }
        }
    }
    std::reverse(topological_sorted_graph.begin(), topological_sorted_graph.end());
    return topological_sorted_graph;
}
