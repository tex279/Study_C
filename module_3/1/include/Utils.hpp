#pragma once  //  NOLINT

#include <deque>
#include <functional>
#include <queue>

#include "IGraph.hpp"

void BFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func) {
    std::queue<int> qu;

    qu.push(vertex);

    visited[vertex] = true;

    while (!qu.empty()) {
        int currentVertex = qu.front();

        qu.pop();

        func(currentVertex);

        for (int nextVertex: graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {

                visited[nextVertex] = true;

                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph &graph, const std::function<void(int)> &func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (auto i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph &graph, int vertex, std::vector<bool> &visited, const std::function<void(int)> &func) {
    visited[vertex] = true;

    func(vertex);

    for (int next_vertex: graph.GetNextVertices(vertex)) {
        if (!visited[next_vertex]) {
            DFS(graph, next_vertex, visited, func);
        }
    }
}

void mainDFS(const IGraph &graph, const std::function<void(int)> &func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) {
            DFS(graph, i, visited, func);
        }
    }
}


void topologicalSortInternal(const IGraph &graph, int vertex, std::vector<bool> &visited, std::deque<int> &sorted) {
    visited[vertex] = true;

    for (auto next_vertex: graph.GetNextVertices(vertex)) {
        if (!visited[next_vertex]) {
            topologicalSortInternal(graph, next_vertex, visited, sorted);
        }
    }

    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph &graph) {
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            topologicalSortInternal(graph, i, visited, sorted);
        }
    }

    return sorted;
}
