#include <cassert>

#include "ListGraph.hpp"

ListGraph::ListGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++)
        adjacencyLists[i] = graph.GetNextVertices(i);
}

void ListGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < (int)adjacencyLists.size());

    assert(0 <= to && to < (int)adjacencyLists.size());

    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return (int) adjacencyLists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int)adjacencyLists.size());

    return adjacencyLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int)adjacencyLists.size());
    std::vector<int> prevVertices;

    for (int from = 0; from < (int)adjacencyLists.size(); from++) {
        for (int to: adjacencyLists[from]) {
            if (to == vertex)
                prevVertices.push_back(from);
        }
    }

    return prevVertices;
}