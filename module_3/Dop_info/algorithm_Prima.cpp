class ListGraph {

    struct Node;

public:
    explicit ListGraph(size_t _size) : m_amount_of_vertices(_size) {
        m_list.resize(_size);
    }

    void add_edge(int from, int to, int weight);

    int vertices_count() const;

    std::vector <Node> get_next_vertices(int vertex) const { return m_list[vertex]; }

    size_t calculate_tree_prima();

    size_t calculate_tree_kruskal();

private:
    struct Node {
        Node(int _id, int _weight) : id(_id), weight(_weight) {};

        int id;
        int weight;

        bool operator>(const Node &right) const { return weight > right.weight; }

        bool operator==(const Node &right) const { return id == right.id; }
    };

    std::vector <std::vector<Node>> m_list;
    size_t m_amount_of_vertices = 0;
};

void ListGraph::add_edge(int from, int to, int weight) {
    auto iterator = std::find(m_list[from].begin(), m_list[from].end(), Node(to, weight));

    if (iterator == m_list[from].end()) {
        m_list[from].push_back(Node(to, weight));
        m_list[to].push_back(Node(from, weight));
    } else if (iterator->weight > weight) {
        iterator.base()->weight = weight;

        iterator = std::find(m_list[to].begin(), m_list[to].end(), Node(from, weight));
        assert(iterator != m_list[to].end());

        iterator.base()->weight = weight;
    }
}

int ListGraph::vertices_count() const {
    return m_amount_of_vertices;
}

size_t ListGraph::calculate_tree_prima() {
    std::vector<bool> visited(m_amount_of_vertices, false);
    std::vector<int> prev_vertex(m_amount_of_vertices, -1);

    std::vector<int> distance(m_amount_of_vertices, 2147483647);
    distance[0] = 0;

    std::priority_queue <Node, std::vector<Node>, std::greater<Node>> unvisited;
    unvisited.push(Node(0, 0));

    while (!unvisited.empty()) {
        Node current = unvisited.top();
        unvisited.pop();
        visited[current.id] = true;

        for (const auto &neighbour: get_next_vertices(current.id)) {

            if (!visited[neighbour.id]) {
                int new_distance = neighbour.weight;

                if (new_distance < distance[neighbour.id]) {
                    distance[neighbour.id] = new_distance;
                    prev_vertex[neighbour.id] = current.id;
                }

                if (!visited[neighbour.id]) {
                    unvisited.push(neighbour);
                }
            }
        }
    }
    return std::accumulate(distance.begin(), distance.end(), 0);
}

size_t ListGraph::calculate_tree_kruskal() {
    ;
}

void processing(std::istream &input, std::ostream &output) {
    size_t vertices = 0;
    size_t edges = 0;

    input >> vertices >> edges;
    assert(vertices > 0);

    auto graph = ListGraph(vertices);
    int from = 0;
    int to = 0;
    int weight;

    for (size_t iterator = 0; iterator < edges; ++iterator) {
        input >> from >> to >> weight;
        graph.add_edge(from - 1, to - 1, weight);
    }
    output << graph.calculate_tree_prima() << std::endl;
}

int main() {
    processing(std::cin, std::cout);
    return 0;
}
