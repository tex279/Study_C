#pragma once  //  NOLINT

#include <cstddef>

#include "IGraph.hpp"

struct ArcGraph: public IGraph {
    ~ArcGraph() {}

    ArcGraph(const size_t size);

    ArcGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> edge_array;

    size_t vertices_count;
};