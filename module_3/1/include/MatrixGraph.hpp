#pragma once  //  NOLINT

#include <cstddef>

#include "IGraph.hpp"

struct MatrixGraph: public IGraph {
    ~MatrixGraph() {}

    MatrixGraph(const size_t size);

    MatrixGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> adjacency_matrix;
};
