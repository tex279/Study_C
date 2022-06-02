#include <iostream>

#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"

#include "Utils.hpp"

void run(const IGraph &graph, const std::string &message) {
    std::cout << message << std::endl;

    mainBFS(graph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    mainDFS(graph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
}

int main() {
    ListGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    run(graph, "ListGraph");

    ListGraph graph2(graph);
    run(graph, "Copy ListGraph");

    return EXIT_SUCCESS;
}
