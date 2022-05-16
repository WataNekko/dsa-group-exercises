#include <iostream>
#include <stack>

#include "dsa/dijkstra_algo.hpp"

enum class Vertex {
    A,
    B,
    C,
    D,
    E
};

std::ostream &operator<<(std::ostream &os, const Vertex &vertex)
{
    return os << static_cast<char>(static_cast<char>(vertex) + 'A');
}

template <typename Vertex, typename Weight>
std::ostream &operator<<(std::ostream &os, const dsa::ShortestPathInfo<Vertex, Weight> &info)
{
    return os << "distance: " << info.shortestDistance << ", previous: " << info.previousVertex;
}

int main()
{
    // prepare input

    constexpr size_t VertexCount = 5;
    constexpr int Inf = std::numeric_limits<int>::max();

    Vertex start = Vertex::A;

    int distances[VertexCount][VertexCount] =
        {{0, 6, Inf, 1, Inf},
         {6, 0, 5, 2, 2},
         {Inf, 5, 0, Inf, 5},
         {1, 2, Inf, 0, 1},
         {Inf, 2, 5, 1, 0}};

    dsa::ShortestPathInfo<Vertex, int> result[VertexCount];

    // run algorithm

    dsa::dijkstraAlgorithm(start, distances, result);

    // display result

    std::cout << "Dijkstra's algorithm result:\n\n";
    for (size_t i = 0; i < VertexCount; i++) {
        std::cout << "vertex: " << static_cast<Vertex>(i) << ", " << result[i] << '\n';
    }
    std::cout << '\n';

    std::cout << "Shortest path from " << start << '\n';
    for (size_t i = 0; i < VertexCount; i++) {
        std::stack<Vertex> path;

        path.push(static_cast<Vertex>(i));
        while (path.top() != result[static_cast<size_t>(path.top())].previousVertex) {
            path.push(result[static_cast<size_t>(path.top())].previousVertex);
        }

        std::cout << "To " << static_cast<Vertex>(i) << ": " << path.top();
        path.pop();
        while (!path.empty()) {
            std::cout << " -> " << path.top();
            path.pop();
        }
        std::cout << '\n';
    }
}
