#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>

//    Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
//    Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

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

int get_count_shortest_path(const int from, const int to, const auto &graph) {
    std::vector<int> distance(graph.VerticesCount(), INT_MAX);
    distance[from] = 0;

    std::vector<int> counter(graph.VerticesCount(), 0);
    counter[from] = 1;

    std::queue<int> queue;

    queue.push(from);

    while (!queue.empty()) {
        int curr = queue.front();
        queue.pop();

        for (auto &next: graph.GetNextVertices(curr)) {
            if (distance[curr] + 1 < distance[next]) {
                distance[next] = distance[curr] + 1;

                counter[next] = counter[curr];

                queue.push(next);
            } else if (distance[curr] + 1 == distance[next]) {
                counter[next] += counter[curr];
            }
        }
    }
    return counter[to];
}


void run(std::istream &input, std::ostream &output) {
    int count_vertex = 0;
    int count_edge = 0;

    input >> count_vertex >> count_edge;

    ListGraph graph(count_vertex);

    int from = 0;
    int to = 0;
    for (size_t i = 0; i < count_edge; ++i) {
        input >> from >> to;

        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    int start = 0;
    int end = 0;

    input >> start >> end;

    output << get_count_shortest_path(start, end, graph) << std::endl;
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
