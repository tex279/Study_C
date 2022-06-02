#include <cassert>

#include "ArcGraph.hpp"

ArcGraph::ArcGraph(const size_t size) : vertices_count(size) {}

ArcGraph::ArcGraph(const IGraph &graph) : ArcGraph(graph.VerticesCount()) {
    for (size_t i = 0; i < vertices_count; ++i) {

        std::vector<int> row = graph.GetNextVertices(i);

        for (const auto &j: row) {
            edge_array.emplace_back(i, j);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < (int) vertices_count);

    assert(0 <= to && to < (int) vertices_count);

    edge_array.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return vertices_count;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) vertices_count);

    std::vector<int> next_vertices;

    for (const auto &i: edge_array) {
        if (i.first == vertex) {
            next_vertices.push_back(i.second);
        }
    }

    return next_vertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) vertices_count);

    std::vector<int> prev_vertices;

    for (const auto &i: edge_array) {
        if (i.second == vertex) {
            prev_vertices.push_back(i.first);
        }
    }

    return prev_vertices;
}