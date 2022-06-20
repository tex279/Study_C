#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <set>
#include <queue>

//    Рику необходимо попасть на межвселенную конференцию. За каждую телепортацию он платит бутылками лимонада,
//    поэтому хочет потратить их на дорогу как можно меньше (он же всё-таки на конференцию едет!). Однако после K
//    перелетов подряд Рика начинает сильно тошнить, и он ложится спать на день. Ему известны все существующие телепортации.
//    Теперь Рик хочет найти путь (наименьший по стоимости в бутылках лимонада), учитывая, что телепортация не занимает
//    времени, а до конференции осталось 10 минут (то есть он может совершить не более K перелетов)!

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


int get_shortest_path(const int from, const int to, const auto &graph, const int max_count_traverse) {
    std::vector<int> distance(graph.VerticesCount(), INT_MAX);
    distance[from] = 0;

    std::vector<int> parents(graph.VerticesCount(), -1);

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

                parents[next_vertex] = curr_vertex;
            }
        }
    }

    std::queue<int> path;
    int buf = to;

    while (buf != from) {
        path.push(parents[buf]);

        buf = parents[buf];
    }

    std::queue<int> copy = path;

    if (max_count_traverse < (int) path.size() || !path.size()) {
        return -1;
    }

    return distance[to];
}


void run(std::istream &input, std::ostream &output) {
    int count_vertex = 0;
    int count_edge = 0;
    int max_traverse = 0;

    input >> count_vertex >> count_edge >> max_traverse;

    int start = 0;
    int end = 0;

    input >> start >> end;

    WeightedListGraph graph(count_vertex);

    int from = 0;
    int to = 0;
    int weight = 0;
    for (int i = 0; i < count_edge; ++i) {
        input >> from >> to >> weight;

        graph.AddEdge(from - 1, to - 1, weight);
    }

    output << get_shortest_path(start - 1, end - 1, graph, max_traverse) << std::endl;
}


int main() {
    run(std::cin, std::cout);

    return EXIT_SUCCESS;
}
