#pragma once  //  NOLINT

#include <unordered_set>
#include <cstddef>

#include "IGraph.hpp"

struct SetGraph: public IGraph {
    ~SetGraph() {}

    SetGraph(const size_t size);

    SetGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::unordered_set<int>> adjacency_hash_table;
};
