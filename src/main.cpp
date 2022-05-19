#include <iostream>
#include <stack>

#include "dsa/dijkstra_algo.hpp"

enum class Vertex : char
{
    S,
    T,
    X,
    Y,
    Z
};

std::ostream &operator<<(std::ostream &os, const Vertex &vertex)
{
    return os << ([&]()
                  {
        switch (vertex) {
        case Vertex::S:
            return 'S';
            break;
        case Vertex::T:
            return 'T';
            break;
        case Vertex::X:
            return 'X';
            break;
        case Vertex::Y:
            return 'Y';
            break;
        default:
            return 'Z';
    } })();
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

    Vertex start = Vertex::S;

    int distances[VertexCount][VertexCount] =
        {{0, 10, Inf, 5, Inf},
         {Inf, 0, 1, 2, Inf},
         {Inf, Inf, 0, Inf, 4},
         {Inf, 8, 9, 0, 2},
         {7, Inf, 6, Inf, 0}};

    dsa::ShortestPathInfo<Vertex, int> result[VertexCount];

    // run algorithm

    dsa::dijkstraAlgorithm(start, distances, result);

    // display result

    std::cout << "Dijkstra's algorithm result:\n\n";
    for (size_t i = 0; i < VertexCount; i++)
    {
        std::cout << "vertex: " << static_cast<Vertex>(i) << ", " << result[i] << '\n';
    }
    std::cout << '\n';

    std::cout << "Shortest path from " << start << '\n';
    for (size_t i = 0; i < VertexCount; i++)
    {
        std::stack<Vertex> path;

        path.push(static_cast<Vertex>(i));
        while (path.top() != result[static_cast<size_t>(path.top())].previousVertex)
        {
            path.push(result[static_cast<size_t>(path.top())].previousVertex);
        }

        std::cout << "To " << static_cast<Vertex>(i) << ": " << path.top();
        path.pop();
        while (!path.empty())
        {
            std::cout << " -> " << path.top();
            path.pop();
        }
        std::cout << " (cost: " << result[i].shortestDistance << ")\n";
    }
}
