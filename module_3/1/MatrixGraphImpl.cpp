#include <cassert>

#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(const size_t size)
        : adjacency_matrix(size, std::vector<bool>(size, false)) {}

MatrixGraph::MatrixGraph(const IGraph &graph) : MatrixGraph(graph.VerticesCount()) {
    for (size_t i = 0; i < adjacency_matrix.size(); ++i) {

        std::vector<int> row = graph.GetNextVertices(i);

        for (auto j: row) {
            adjacency_matrix[i][j] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < (int) adjacency_matrix.size());

    assert(0 <= to && to < (int) adjacency_matrix.size());

    adjacency_matrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return (int) adjacency_matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) adjacency_matrix.size());

    std::vector<int> next_vertices;

    for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
        if (adjacency_matrix[vertex][i]) {
            next_vertices.push_back(i);
        }
    }

    return next_vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) adjacency_matrix.size());

    std::vector<int> next_vertices;

    for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
        if (adjacency_matrix[vertex][i]) {
            next_vertices.push_back(i);
        }
    }

    return next_vertices;
}