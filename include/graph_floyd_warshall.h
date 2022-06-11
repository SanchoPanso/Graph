#ifndef GRAPH_GRAPH_FLOYD_WARSHALL_H
#define GRAPH_GRAPH_FLOYD_WARSHALL_H

#include <vector>
#include "base_graph.h"

template<typename T>
class GraphFloydWarshall : virtual public BaseGraph<T> {
private:
    std::vector<std::vector<int>> restore_matrix;   // Матрица для восстановления кратчайшего пути
    std::vector<int> restored_path;                 // Вектор, в котором хранится путь восстановленный методом restore_path
public:
    std::vector<std::vector<T>> floyd_warshall();   // Базовая реализация алгоритма
public:
    // Дополнительный функционал на основе алгоритма
    std::tuple<std::vector<std::vector<T>>, std::vector<std::vector<int>>> floyd_warshall_ways(); // Дополнительно возвращает
    // матрицу для восстановления
    // пути между узлами
    std::vector<int> restore_path(int from, int to); // Восстанавливает путь между указанными узлами
private:
    T min(int, int, int);
};

#endif //GRAPH_GRAPH_FLOYD_WARSHALL_H
