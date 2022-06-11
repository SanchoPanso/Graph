#include "../include/vertex.h"
#include "../include/explixit_instantiation.h"

EXPLICIT_INSTANTIATION(Vertex);

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
