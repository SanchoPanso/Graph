#include "../include/edge.h"
#include "../include/explixit_instantiation.h"

EXPLICIT_INSTANTIATION(Edge);

template<typename T>
bool Edge<T>::operator== (const Edge<T>& other) {
    return (neighbor == other.neighbor) && (distance == other.distance);
}

template <typename T>
Edge<T>::Edge(Vertex<T>* neighbor, T distance) {
    this->neighbor = neighbor;
    this->distance = distance;
}

