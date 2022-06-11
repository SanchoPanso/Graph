#include<iostream>
#include <vector>
#include <algorithm>
#include "../include/base_graph.h"
#include "../include/explixit_instantiation.h"


EXPLICIT_INSTANTIATION(Vertex);
EXPLICIT_INSTANTIATION(Edge);
EXPLICIT_INSTANTIATION(BaseGraph);


template <typename T>
Vertex<T>::Vertex(int id) {
    this->id = id;
    this->edges = std::list<Edge<T>>();
}


template <typename T>
Vertex<T>::Vertex(const Vertex& other) {
    id = other.id;
    edges = other.edges;
}


template <typename T>
void Vertex<T>::add_edge(Vertex<T>* neighbor, T distance) {
    for (auto it = edges.begin(); it != edges.end(); it++) {
        if (it->get_neighbor() == neighbor) {
            edges.erase(it);
            break;
        }
    }
    Edge<T> edge(neighbor, distance);       //
    edges.push_back(edge);
}

template<typename T>
void Vertex<T>::remove_edge(Vertex<T>* neighbor) {
    for (auto& it : edges) {
        if (it.get_neighbor() == neighbor) {
            edges.remove(it);           // change!!! It works, but very strange
            break;
        }
    }
}


template<typename T>
bool Edge<T>::operator== (const Edge<T>& other) {
    return (neighbor == other.neighbor) && (distance == other.distance);
}

template <typename T>
Edge<T>::Edge(Vertex<T>* neighbor, T distance) {
    this->neighbor = neighbor;
    this->distance = distance;
}

template<typename T>
T get_inf() {
    T inf = std::numeric_limits<T>::infinity();
    if (inf == (T)0) {
        return std::numeric_limits<T>::max();
    }
    return inf;
}


template <typename T>
BaseGraph<T>::BaseGraph(int num_of_vertices) {
    for (id_counter = 0; id_counter < num_of_vertices; id_counter++) {
        auto v = new Vertex<T>(id_counter);
        vertices.push_back(v);
    }
}


template <typename T>
BaseGraph<T>::BaseGraph(std::list<Vertex<T>*>& vertices) {
    this->vertices = vertices;
}

template <typename T>
BaseGraph<T>::BaseGraph(std::vector<std::vector<T>>& adjacency_matrix) {
    this->adjacency_matrix = adjacency_matrix;
    this->id_counter = adjacency_matrix.size();

    for (int i = 0; i < adjacency_matrix.size(); i++) {
        auto v = new Vertex<T>(i);
        vertices.push_back(v);
    }
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        for (int j = 0; j < adjacency_matrix.size(); j++) {
            if (adjacency_matrix[i][j] != INF<T>) {
                auto source = find_vertex(i);
                auto target = find_vertex(j);
                source->add_edge(target, adjacency_matrix[i][j]);
            }
        }
    }
}

template <typename T>
BaseGraph<T>::BaseGraph(std::vector<std::list<int>>& adjacency_list) {
    this->adjacency_list = adjacency_list;
    this->id_counter = adjacency_list.size();

    for (int i = 0; i < adjacency_list.size(); i++) {
        auto v = new Vertex<T>(i);
        vertices.push_back(v);
    }
    for (int i = 0; i < adjacency_list.size(); i++) {
        for (int j = 0; j < adjacency_list.size(); j++) {
            auto it = std::find(adjacency_list[i].begin(), adjacency_list[i].end(), j);
            if (it != adjacency_list[i].end()) {
                auto source = find_vertex(i);
                auto target = find_vertex(j);
                source->add_edge(target, 0);
            }
        }
    }
}

template <typename T>
BaseGraph<T>::BaseGraph(const BaseGraph& other) {
    adjacency_matrix = other.adjacency_matrix;
    adjacency_list = other.adjacency_list;
}

template <typename T>
BaseGraph<T>::BaseGraph(BaseGraph&& other) noexcept {
    adjacency_matrix = other.adjacency_matrix;
    adjacency_list = other.adjacency_list;
}

template <typename T>
BaseGraph<T>::~BaseGraph() {
    for (auto& v : vertices) {
        delete v;
    }
}

template <typename T>
int BaseGraph<T>::add_edge(int source_id, int target_id, int weight, EdgeType edge_type) {

    // Edge, where start and end are the same vertex, is unexpected
    if (source_id == target_id) {
        return 1;
    }

    Vertex<T>* source = find_vertex(source_id);
    Vertex<T>* target = find_vertex(target_id);

    // If some vertex is not exists, then an error is considered
    if (source == nullptr || target == nullptr) {
        return 1;
    }


    switch (edge_type) {
        case UNDIRECTED:
            source->add_edge(target, weight);
            target->add_edge(source, weight);
            break;
        case DIRECTED:
            source->add_edge(target, weight);
            break;
        default:
            break;
    }

    return 0;
}

template <typename T>
int BaseGraph<T>::remove_edge(int source_id, int target_id, EdgeType edge_type) {

    // Edge, where start and end are the same vertex, is unexpected
    if (source_id == target_id) {
        return 1;
    }

    Vertex<T>* source = find_vertex(source_id);
    Vertex<T>* target = find_vertex(target_id);

    // If some vertex is not exists, then an error is considered
    if (source == nullptr || target == nullptr) {
        return 1;
    }

    switch (edge_type) {
        case UNDIRECTED:
            source->remove_edge(target);
            target->remove_edge(source);
            break;
        case DIRECTED:
            source->remove_edge(target);
            break;
        default:
            break;
    }

    return 0;
}


template <typename T>
int BaseGraph<T>::add_vertex() {
    auto v = new Vertex<T>(id_counter);
    vertices.push_back(v);
    id_counter++;
    return v->get_id();
}

template <typename T>
int BaseGraph<T>::remove_vertex(int id) {

    auto vtx = find_vertex(id);

    // if `vtx` is not in `vertices`, then just return
    if (vtx == nullptr) {
        return 1;
    }

    // delete all edges linking `vtx` with other vertices
    auto edges = vtx->get_edges();
    for (Edge<T> edge : edges) {
        Vertex<T>* neighbor = edge.get_neighbor();
        neighbor->remove_edge(vtx);
    }

    // delete `vtx` from list of all vertices
    auto it = std::find(vertices.begin(), vertices.end(), vtx);
    vertices.erase(it);

    return 0;
}


template <typename T>
Vertex<T>* BaseGraph<T>::find_vertex(int id) {
    for (auto v = vertices.begin(); v != vertices.end(); v++) {
        if ((*v)->get_id() == id) {
            return *v;
        }
    }
    return nullptr;
}

template <typename T>
void BaseGraph<T>::actualize_adjacency_list() {
    adjacency_list = std::vector<std::list<int>>(id_counter, std::list<int>());

    for (int id = 0; id < id_counter; id++) {
        Vertex<T>* vtx = find_vertex(id);

        if (vtx == nullptr)
            continue;

        std::list<Edge<T>> edges = vtx->get_edges();
        for (Edge<T> edge : edges) {
            Vertex<T>* neighbor = edge.get_neighbor();
            adjacency_list[id].push_back(neighbor->get_id());
        }
    }
}

template <typename T>
void BaseGraph<T>::actualize_adjacency_matrix() {

    // initially adjacency_matrix is filled with infinities
    adjacency_matrix = std::vector<std::vector<T>>(id_counter, std::vector<T>(id_counter, INF<T>));

    for (int id = 0; id < id_counter; id++) {
        Vertex<T>* vtx = find_vertex(id);

        if (vtx == nullptr)
            continue;

        std::list<Edge<T>> edges = vtx->get_edges();
        for (Edge<T> edge : edges) {
            Vertex<T>* neighbor = edge.get_neighbor();
            T distance = edge.get_distance();
            adjacency_matrix[id][neighbor->get_id()] = distance;
        }
    }
}

