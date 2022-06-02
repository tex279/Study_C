#pragma once  //  NOLINT

#include "IGraph.hpp"

struct ListGraph: public IGraph {
    ~ListGraph() {}

    ListGraph(int size) : adjacencyLists(size) {}

    ListGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacencyLists;
};
