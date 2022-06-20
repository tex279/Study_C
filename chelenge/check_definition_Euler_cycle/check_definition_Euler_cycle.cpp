#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>
#include <algorithm>

//    Нужно проверить, является ли неориентированный граф эйлеровым.

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual void RmEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


struct ListGraph : public IGraph {
    ~ListGraph() {}

    ListGraph(const size_t size);

    ListGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;

    void RmEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    bool CheckDefinitionEulerCycle() const;

    size_t count_edge;

private:
    std::vector <std::vector<int>> adjacency_lists;
};

ListGraph::ListGraph(const size_t size) : count_edge(0), adjacency_lists(size) {}

ListGraph::ListGraph(const IGraph &graph) : ListGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjacency_lists[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < (int) adjacency_lists.size());

    assert(0 <= to && to < (int) adjacency_lists.size());

    adjacency_lists[from].push_back(to);

    ++count_edge;
}

void ListGraph::RmEdge(int from, int to) {
    assert(0 <= from && from < (int) adjacency_lists.size());

    assert(0 <= to && to < (int) adjacency_lists.size());

    auto pos = std::find(adjacency_lists[from].begin(), adjacency_lists[from].end(), to);
    if (pos == adjacency_lists[from].end()) {
        return;
    }

    adjacency_lists[from].erase(pos);

    --count_edge;
}

int ListGraph::VerticesCount() const {
    return (int) adjacency_lists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) adjacency_lists.size());

    return adjacency_lists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) adjacency_lists.size());

    std::vector<int> prev_vertices;

    for (size_t from = 0; from < adjacency_lists.size(); from++) {
        for (const auto &to: adjacency_lists[from]) {
            if (to == vertex)
                prev_vertices.push_back(from);
        }
    }

    return prev_vertices;
}


bool ListGraph::CheckDefinitionEulerCycle() const {
    for (const auto &vertex: adjacency_lists) {
        if (vertex.size() % 2 != 0) {
            return false;
        }
    }

    return true;
}

void DFS(auto &graph, int vertex, std::vector<bool> &visited, std::vector<int> &path_Euler) {
    if (graph.count_edge == 0) {
        return;
    }

    visited[vertex] = true;

    for (int next_vertex: graph.GetNextVertices(vertex)) {
        graph.RmEdge(vertex, next_vertex);
        graph.RmEdge(next_vertex, vertex);
        DFS(graph, next_vertex, visited, path_Euler);
    }

    path_Euler.push_back(vertex);
}

bool mainDFS(auto &graph, std::vector<int> &path_Euler) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    DFS(graph, 0, visited, path_Euler);

    for (const auto &status: visited) {
        if (!status) {
            return false;
        }
    }

    return true;
}


void run(std::istream &input, std::ostream &output) {
    int count_vertex = 0;
    int count_edge = 0;

    input >> count_vertex >> count_edge;

    ListGraph graph(count_vertex);

    int from = 0;
    int to = 0;
    for (int i = 0; i < count_edge; ++i) {
        input >> from >> to;

        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    if (!graph.CheckDefinitionEulerCycle()) {
        output << "0" << std::endl;

        return;
    }

    std::vector<int> path_Euler;

    output << mainDFS(graph, path_Euler) << std::endl;
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
