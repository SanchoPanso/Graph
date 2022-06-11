#ifndef GRAPH_BASE_GRAPH_H
#define GRAPH_BASE_GRAPH_H

#include <cstdint>
#include <vector>
#include <list>

typedef enum {
    UNDIRECTED,
    DIRECTED,
} EdgeType;

// Получить "бесконечность" для типа T
// (целочисленный тип - максимальное значение, с плавающей запятой - inf)
template<typename T>
T get_inf();

// переменная, содержащая "бесконечность", т.е. такой вес ребра,
// который эквивалентен отсутствию этого ребра
template <typename T>
T INF = get_inf<T>();

template <typename T> class Vertex;
template <typename T> class Edge;
template <typename T> class BaseGraph;

template <typename T>
class Vertex {
    friend BaseGraph<T>;
private:
    int id{};
    std::list<Edge<T>> edges;
public:
    explicit Vertex(int id = 0);
    Vertex(const Vertex& other);
    ~Vertex() = default;
public:
    void add_edge(Vertex<T>* neighbor, T distance);
    void remove_edge(Vertex<T>* neighbor);
public:
    int get_id() { return id; }
    std::list<Edge<T>> get_edges() { return edges; }
};


template <typename T>
class Edge {
private:
    Vertex<T>* neighbor;
    T distance;
public:
    explicit Edge(Vertex<T>* neighbor = nullptr, T distance = 0);
    ~Edge() = default;
public:
    bool operator== (const Edge<T>& other);
public:
    Vertex<T>* get_neighbor() { return neighbor; }
    T get_distance() { return distance; }
};


// Класс графа с базовой функциональностью
template <typename T>
class BaseGraph {
protected:
    int id_counter = 0;
    std::list<Vertex<T>*> vertices;
    std::vector<std::vector<T>> adjacency_matrix;   // Матрица смежности
    std::vector<std::list<int>> adjacency_list;       // Список смежности
public:
    explicit BaseGraph(int num_of_vertices = 0);
    explicit BaseGraph(std::list<Vertex<T>*>& vertices);
    explicit BaseGraph(std::vector<std::vector<T>>& adjacency_matrix);
    explicit BaseGraph(std::vector<std::list<int>>& adjacency_list);
    BaseGraph(const BaseGraph& other);
    BaseGraph(BaseGraph&& other) noexcept;
    virtual ~BaseGraph();

    // Методы для взаимодействия с графом (т.е. геттеры, сеттеры и т.д.)
public:
    Vertex<T>* find_vertex(int id);
    int add_edge(int source_id, int target_id, int weight = 0, EdgeType edge_type = UNDIRECTED);
    int remove_edge(int source_id, int target_id, EdgeType edge_type = UNDIRECTED);
    int add_vertex();
    int remove_vertex(int id);
public:
    int get_id_counter() { return id_counter; }
    std::list<Vertex<T>*> get_vertices() { return vertices; }
    std::vector<std::vector<T>> get_adjacency_matrix() { return adjacency_matrix; }
    std::vector<std::list<int>> get_adjacency_list() { return adjacency_list; }
public:
    void actualize_adjacency_list();
    void actualize_adjacency_matrix();
};


#endif
