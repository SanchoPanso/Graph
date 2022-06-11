#include<iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>
#include <tuple>
#include "../include/graph_dijkstra.h"
#include "../include/explixit_instantiation.h"

EXPLICIT_INSTANTIATION(GraphDijkstra);


//receives start node and finds the shortest distances from it
template<typename T>
std::vector<T> GraphDijkstra<T>::dijkstra_from_one_vertex(int origin) {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    origin--;
    std::vector<T> shortest_distances;
    // Checking correct input of the matrix and origin
    if (origin > vertices) return shortest_distances;
    //vector to store passed nodes
    std::vector<bool> passed(vertices);
    //vector to store the shortest distance from origin to all nodes
    shortest_distances.resize(vertices);
    //initializing vectors
    passed[origin] = true;
    for (int node = 0; node < vertices; node++) {
        shortest_distances[node] = BaseGraph<T>::adjacency_matrix[origin][node];
    }
    //Dijkstra algorithm realization
    for (int in_cln = 1; in_cln < vertices; in_cln++) {
        T min = INF<T>;
        int next_node = -1;
        //Finding the nearest node
        for (int node = 0; node < vertices; node++) {
            //We can't go through passed nodes
            if (!passed[node]) {
                if (min > shortest_distances[node]) {
                    min = shortest_distances[node];
                    next_node = node;
                }
            }
        }
        if (next_node == -1) return shortest_distances;
        passed[next_node] = true;
        //Finding the shortest paths through this node
        for (int node = 0; node < vertices; node++) {
            // We can't go through passed nodes
            if (!passed[node]) {
                if (BaseGraph<T>::adjacency_matrix[next_node][node] != INF<T>) {
                    if (min + BaseGraph<T>::adjacency_matrix[next_node][node] < shortest_distances[node]) {
                        shortest_distances[node] = min + BaseGraph<T>::adjacency_matrix[next_node][node];
                    }
                }
            }
        }
    }
    return shortest_distances;
}

template<typename T>
int GraphDijkstra<T>::dijkstra_log(int top_from, int top_to)
{
    //number of tops of the graph
    int tops = BaseGraph<T>::adjacency_matrix.size();
    top_from--;
    top_to--;
    // vector of infs
    std::vector <int> distances(tops, INF<T>);
    distances[top_from] = 0;
    std::priority_queue <std::pair <int, int > > q;
    q.push(std::make_pair(0, top_from));
    while (!q.empty())
    {
        int first_length = -q.top().first;
        int first_top = q.top().second;
        q.pop();
        if (first_length > distances[first_top]) continue;
        for (int i = 0; i < tops; i++)
        {
            int to = i;
            int length = BaseGraph<T>::adjacency_matrix[first_top][i];
            if (distances[to] > distances[first_top] + length)
            {
                distances[to] = distances[first_top] + length;
                q.push(std::make_pair(-distances[to], to));
            }
        }
    }
    if (distances[top_to] == INF<T>) return -1;
    else return distances[top_to];
}

//Applies Dijkstra algorithm for every node to make paths matrix
template<typename T>
std::vector<std::vector<T>> GraphDijkstra<T>::dijkstra() {
    int vertices = BaseGraph<T>::adjacency_matrix.size();
    std::vector<std::vector<T>> paths_matrix(vertices, std::vector<T>(vertices));
    for (int i = 1; i <= vertices; i++) {
        paths_matrix[i - 1] = dijkstra_from_one_vertex(i);
    }
    BaseGraph<T>::adjacency_matrix = paths_matrix;
    return BaseGraph<T>::adjacency_matrix;
}

