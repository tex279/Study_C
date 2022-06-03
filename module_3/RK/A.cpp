#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>

//    Проверить, является ли неориентированный граф деревом.

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


struct ListGraph : public IGraph {
    ~ListGraph() {}

    ListGraph(const size_t size);

    ListGraph(const IGraph &graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector <std::vector<int>> adjacency_lists;
};

ListGraph::ListGraph(const size_t size) : adjacency_lists(size) {}

ListGraph::ListGraph(const IGraph &graph) : ListGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjacency_lists[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < (int) adjacency_lists.size());

    assert(0 <= to && to < (int) adjacency_lists.size());

    adjacency_lists[from].push_back(to);
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

bool BFS(const IGraph &graph, int vertex, std::vector<bool> &visited) {
    std::queue<int> queue;

    queue.push(vertex);

    visited[vertex] = true;

    while (!queue.empty()) {
        int currentVertex = queue.front();

        queue.pop();

        for (int nextVertex: graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;

                queue.push(nextVertex);
            }
        }
    }

    return true;
}

bool mainBFS(const IGraph &graph) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    BFS(graph, 0, visited);

    for (const auto &status: visited) {
        if (!status) {
            return false;
        }
    }

    return true;
}

bool check_tree(const auto &graph) {
    return mainBFS(graph);
}


void run(std::istream &input, std::ostream &output) {
    int count_vertex = 0;
    int count_edge = 0;

    input >> count_vertex >> count_edge;

    if (count_vertex - 1 != count_edge) {
        output << "0" << std::endl;

        return;
    }

    ListGraph graph(count_vertex);

    int from = 0;
    int to = 0;
    for (int i = 0; i < count_edge; ++i) {
        input >> from >> to;

        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    output << check_tree(graph) << std::endl;
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
