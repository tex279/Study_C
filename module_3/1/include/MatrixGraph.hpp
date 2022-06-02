#pragma once  //  NOLINT

#include "IGraph.hpp"

struct MatrixGraph: public IGraph {
    ~MatrixGraph() {}

    MatrixGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
};
