#include<iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdint>
#include <tuple>
#include "../include/graph_tarjans_scc_algorithm.h"
#include "../include/explixit_instantiation.h"

EXPLICIT_INSTANTIATION(GraphTarjansSCCalgorithm);


template<typename T>
void GraphTarjansSCCalgorithm<T>::Tarjan_SCC_algorithm() {
    std::vector<bool> presents_in_stack(BaseGraph<T>::id_counter, false);
    std::stack<int> stack_of_relatives;
    std::vector<int> queue_num(BaseGraph<T>::id_counter, -1);
    std::vector<int> low_link(BaseGraph<T>::id_counter, -1);
    for (int i = 0; i < BaseGraph<T>::id_counter; i++) {
        if (queue_num[i] == -1) {
            Tarjan_DFS(i, queue_num, low_link, presents_in_stack, stack_of_relatives);
        }
    }
}

template<typename T>
void GraphTarjansSCCalgorithm<T>::Print_SCC(int head_of_SCC, std::stack<int>& stack_of_relatives,
                                            std::vector<bool>& presents_in_stack) {
    std::cout << "SCC: ";
    while (stack_of_relatives.top() != head_of_SCC) {
        std::cout << stack_of_relatives.top() << ", ";
        presents_in_stack[stack_of_relatives.top()] = false;
        stack_of_relatives.pop();
    }
    std::cout << stack_of_relatives.top() << "\n";
    presents_in_stack[stack_of_relatives.top()] = false;
    stack_of_relatives.pop();
}

template<typename T>
void GraphTarjansSCCalgorithm<T>::Tarjan_DFS(int current_node, std::vector<int>& queue_num, std::vector<int>& low_link,
                                             std::vector<bool>& presents_in_stack, std::stack<int>& stack_of_relatives) {
    static int disc_time = 0;
    queue_num[current_node] = disc_time;
    low_link[current_node] = disc_time;
    disc_time++;
    stack_of_relatives.push(current_node);
    presents_in_stack[current_node] = true;
    for (int descendant = 0; descendant <= BaseGraph<T>::id_counter; descendant++) {
        if (BaseGraph<T>::adjacency_matrix[current_node][descendant] == 0) {
        }
        else if (queue_num[descendant] == -1) {
            Tarjan_DFS(descendant, queue_num, low_link, presents_in_stack, stack_of_relatives);
            low_link[current_node] = std::min(low_link[current_node], low_link[descendant]);
        }
        else if (presents_in_stack[descendant]) {
            low_link[current_node] = std::min(low_link[current_node], queue_num[descendant]);
        }
    }
    if (low_link[current_node] == queue_num[current_node]) {
        Print_SCC(current_node, stack_of_relatives, presents_in_stack);
    }

}