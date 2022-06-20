#pragma once  //  NOLINT

#include <cstddef>

#include "IGraph.hpp"

struct ListGraph: public IGraph {
    ~ListGraph() {}

    ListGraph(const size_t size);

    ListGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacency_lists;
};
