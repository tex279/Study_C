#include <cassert>

#include "SetGraph.hpp"

SetGraph::SetGraph(const size_t size) : adjacency_hash_table(size) {}

SetGraph::SetGraph(const IGraph &graph) : SetGraph(graph.VerticesCount()) {
    for (size_t i = 0; i < adjacency_hash_table.size(); ++i) {
        std::vector<int> row = graph.GetNextVertices(i);

        for (int j: row) {
            adjacency_hash_table[i].insert(j);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < (int) adjacency_hash_table.size());

    assert(0 <= to && to < (int) adjacency_hash_table.size());

    adjacency_hash_table[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return (int) adjacency_hash_table.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) adjacency_hash_table.size());

    std::vector<int> next_vertices;

    for (size_t i = 0; i < adjacency_hash_table.size(); ++i) {
        if (adjacency_hash_table[vertex].find(i) != adjacency_hash_table[vertex].end()) {
            next_vertices.push_back(i);
        }
    }

    return next_vertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) adjacency_hash_table.size());

    std::vector<int> prev_vertices;

    for (size_t i = 0; i < adjacency_hash_table.size(); ++i) {
        if (adjacency_hash_table[i].find(vertex) != adjacency_hash_table[i].end()) {
            prev_vertices.push_back(i);
        }
    }

    return prev_vertices;
}