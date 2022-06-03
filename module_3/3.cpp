#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <set>

//    Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога,
//    которая возвращается в этот же город.
//
//    Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
//    N ≤ 10000, M ≤ 250000.
//    Длина каждой дороги ≤ 10000.

struct WeightedListGraph {
    ~WeightedListGraph() {}

    WeightedListGraph(const size_t size);

    void AddEdge(int from, int to, int weight);

    int VerticesCount() const;

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const;

    std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const;

private:
    std::vector<std::vector<std::pair<int, int>>> adjacency_lists;
};

WeightedListGraph::WeightedListGraph(const size_t size) : adjacency_lists(size) {}

void WeightedListGraph::AddEdge(int from, int to, int weight) {
    assert(0 <= from && from < (int) adjacency_lists.size());

    assert(0 <= to && to < (int) adjacency_lists.size());

    assert(0 <= weight);

    adjacency_lists[from].push_back({weight, to});
}

int WeightedListGraph::VerticesCount() const {
    return (int) adjacency_lists.size();
}

std::vector<std::pair<int, int>> WeightedListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) adjacency_lists.size());

    std::vector<std::pair<int, int>> next_vertices(adjacency_lists[vertex].size());

    for (size_t i = 0; i < adjacency_lists[vertex].size(); ++i) {
        next_vertices[i] = adjacency_lists[vertex][i];
    }

    return next_vertices;
}

std::vector<std::pair<int, int>> WeightedListGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < (int) adjacency_lists.size());

    std::vector<std::pair<int, int>> prev_vertices;

    for (size_t i = 0; i < adjacency_lists.size(); ++i) {
        for (const auto &value : adjacency_lists[i]) {
            if (vertex == value.second) {

                prev_vertices.push_back(adjacency_lists[vertex][i]);

                break;
            }
        }
    }

    return prev_vertices;
}


int get_shortest_path(const int from, const int to, const auto &graph) {
    std::vector<int> distance(graph.VerticesCount(), INT_MAX);
    distance[from] = 0;

    std::set<std::pair<int, int>> queue;

    queue.insert({distance[from], from});

    while (!queue.empty()) {
        auto edge = std::move(queue.extract(queue.begin()).value());

        int curr_vertex = edge.second;

        for (auto &next: graph.GetNextVertices(curr_vertex)) {
            int next_vertex = next.second;

            int new_distance = distance[curr_vertex] + next.first;

            if (distance[next_vertex] > new_distance) {
                queue.erase({distance[next_vertex], next_vertex});

                queue.insert({new_distance, next_vertex});

                distance[next_vertex] = new_distance;
            }
        }
    }

    return distance[to];
}


void run(std::istream &input, std::ostream &output) {
    int count_vertex = 0;
    int count_edge = 0;

    input >> count_vertex >> count_edge;

    WeightedListGraph graph(count_vertex);

    int from = 0;
    int to = 0;
    int weight = 0;
    for (size_t i = 0; i < count_edge; ++i) {
        input >> from >> to >> weight;

        graph.AddEdge(from, to, weight);
        graph.AddEdge(to, from, weight);
    }

    int start = 0;
    int end = 0;

    input >> start >> end;

    output << get_shortest_path(start, end, graph) << std::endl;
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
