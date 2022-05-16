#pragma once

#include <limits>
#include <memory>

namespace dsa {

    template <typename Vertex, typename Weight>
    struct ShortestPathInfo {
        Weight shortestDistance;
        Vertex previousVertex;
    };

    template <typename Vertex, typename Weight>
    void dijkstraAlgorithm(const Vertex start,
                           const Weight *const adjacencyMatrix,
                           ShortestPathInfo<Vertex, Weight> *const outShortestPath,
                           const size_t vertexCount)
    {
        constexpr Weight Inf = std::numeric_limits<Weight>::has_infinity
                                   ? std::numeric_limits<Weight>::infinity()
                                   : std::numeric_limits<Weight>::max();
        auto visited = std::make_unique<bool[]>(vertexCount);
        size_t currVertex = static_cast<size_t>(start);

        // initialize shortest distance to Inf
        for (size_t i = 0; i < vertexCount; i++) {
            auto &vertex = outShortestPath[i];
            if (i == static_cast<size_t>(start)) {
                vertex.shortestDistance = adjacencyMatrix[i * vertexCount + i];
                vertex.previousVertex = start;
                continue;
            }
            vertex.shortestDistance = Inf;
        }

        for (size_t visitedCount = 0; visitedCount < vertexCount; visitedCount++) {
            // get the unvisited vertex with the smallest known distance from the start vertex
            Weight minDistance = Inf;
            for (size_t i = 0; i < vertexCount; i++) {
                const Weight &distFromStart = outShortestPath[i].shortestDistance;
                if (!visited[i] && distFromStart < minDistance) {
                    minDistance = distFromStart;
                    currVertex = i;
                }
            }

            // for all unvisited neighbours
            for (size_t i = 0; i < vertexCount; i++) {
                const Weight &distCurrToNeighbour = adjacencyMatrix[currVertex * vertexCount + i];
                if (visited[i] || currVertex == i || distCurrToNeighbour >= Inf) {
                    continue;
                }

                // update if new distance is less than known distance
                Weight newDistance = outShortestPath[currVertex].shortestDistance +
                                     distCurrToNeighbour;
                auto &neighbour = outShortestPath[i];

                if (newDistance < neighbour.shortestDistance) {
                    neighbour.shortestDistance = newDistance;
                    neighbour.previousVertex = static_cast<Vertex>(currVertex);
                }
            }

            visited[currVertex] = true;
        }
    }

    template <typename Vertex, typename Weight, size_t VertexCount>
    inline void dijkstraAlgorithm(const Vertex start,
                                  const Weight (&adjacencyMatrix)[VertexCount][VertexCount],
                                  ShortestPathInfo<Vertex, Weight> (&outShortestPath)[VertexCount])
    {
        dijkstraAlgorithm(start,
                          reinterpret_cast<const Weight *>(adjacencyMatrix),
                          outShortestPath,
                          VertexCount);
    }

} // namespace dsa