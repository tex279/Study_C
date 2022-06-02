#include <iostream>

#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"

#include "Utils.hpp"

void check(const IGraph &left_graph, const IGraph &right_graph, const std::string &left_message, const std::string &right_message) {
    std::vector<int> left;
    mainBFS(left_graph, [&left](int vertex){ left.push_back(vertex); });

    std::vector<int> right;
    mainBFS(right_graph, [&right](int vertex){ right.push_back(vertex); });

    std::cout << "Check_result: " << left_message;

    if (left == right) {
        std::cout << " = ";
    } else {
        std::cout << " WARNING != ";
    }

    std::cout << right_message << std::endl;

//    for (auto value: left) {
//        std::cout << value << " ";
//    }
//    std::cout << std::endl;
//
//    for (auto value: right) {
//        std::cout << value << " ";
//    }
//    std::cout << std::endl;
}

void run_output(const IGraph &graph, const std::string &message) {
    std::cout << message << std::endl;

    mainBFS(graph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;

    mainDFS(graph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl;
}

void test_structs_graph() {
    ListGraph list_graph_1(10);
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

    list_graph_1.AddEdge(7, 8);
    list_graph_1.AddEdge(8, 9);

    run_output(list_graph_1, "ListGraph:");

    ListGraph list_graph_2(list_graph_1);
    run_output(list_graph_2, "Copy_ListGraph:");

    check(list_graph_1, list_graph_2, "ListGraph", "Copy_ListGraph");
    std::cout << "-------------------" << std::endl;

    MatrixGraph matrix_graph_1(list_graph_2);
    run_output(matrix_graph_1, "MatrixGraph:");

    check(list_graph_2, matrix_graph_1, "Copy_ListGraph", "MatrixGraph");

    MatrixGraph matrix_graph_2(matrix_graph_1);
    run_output(matrix_graph_2, "Copy_MatrixGraph:");

    check(matrix_graph_1, matrix_graph_2, "MatrixGraph", "Copy_MatrixGraph");
    std::cout << "-------------------" << std::endl;

    SetGraph set_graph_1(matrix_graph_2);
    run_output(set_graph_1, "SetGraph:");

    check(matrix_graph_2, set_graph_1, "Copy_MatrixGraph", "SetGraph");

    SetGraph set_graph_2(set_graph_1);
    run_output(set_graph_2, "Copy_SetGraph:");

    check(set_graph_1, set_graph_2, "SetGraph", "Copy_SetGraph");
    std::cout << "-------------------" << std::endl;

    ArcGraph arc_graph_1(set_graph_2);
    run_output(arc_graph_1, "ArcGraph:");

    check(set_graph_2, arc_graph_1, "Copy_SetGraph", "ArcGraph");

    ArcGraph arc_graph_2(arc_graph_1);
    run_output(arc_graph_2, "Copy_ArcGraph:");

    check(arc_graph_1, arc_graph_1, "ArcGraph", "Copy_ArcGraph");
    std::cout << "-------------------" << std::endl;
}

int main() {
    test_structs_graph();

    return EXIT_SUCCESS;
}
