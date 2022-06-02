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
    ListGraph list_graph_1(7);
    list_graph_1.AddEdge(0, 1);
    list_graph_1.AddEdge(0, 5);
    list_graph_1.AddEdge(1, 2);
    list_graph_1.AddEdge(1, 3);
    list_graph_1.AddEdge(1, 5);
    list_graph_1.AddEdge(1, 6);
    list_graph_1.AddEdge(3, 2);
    list_graph_1.AddEdge(3, 4);
    list_graph_1.AddEdge(3, 6);
    list_graph_1.AddEdge(5, 4);
    list_graph_1.AddEdge(5, 6);
    list_graph_1.AddEdge(6, 4);

    run(list_graph_1, "ListGraph");

    ListGraph list_graph_2(list_graph_1);

    run(list_graph_2, "Copy ListGraph");

    MatrixGraph matrix_graph_1(list_graph_2);

    run(matrix_graph_1, "MatrixGraph");

    MatrixGraph matrix_graph_2(matrix_graph_1);

    run(matrix_graph_2, "Copy MatrixGraph");

    return EXIT_SUCCESS;
}
