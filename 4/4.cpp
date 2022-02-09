#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

#define MAX_SIZE 500
#define MIN_SIZE 1

#define MAX_COUNT_NODE MAX_SIZE * MIN_SIZE
#define MIN_COUNT_NODE 1

#define ERROR_INPUT -1
#define SUCCESS 1

typedef struct node {
    size_t x;
    size_t y;
} Node_t;

class Net {
public:
    size_t x;
    size_t y;

    size_t count_node;

    std::vector <Node_t> nodes;

    int input_size();
    int input_nodes();

    size_t** create_net();
    void del_net(size_t** net);

    void set_black(size_t** net, size_t start, size_t end, size_t const const_index, size_t direction);

    void filling(size_t** net);

    void print(size_t** net);

    size_t check_1(size_t** net);

    size_t check_0(size_t** net);

    void get_res_count();

    Net();
    ~Net() = default;
};

int Net::input_size() {
    std::cin >> x >> y >> count_node;

    if (MIN_SIZE > x || x > MAX_SIZE) {
        std::cerr << "Wrong input: x must be in interval " <<
        MIN_SIZE << "-" << MAX_SIZE << std::endl;
        return ERROR_INPUT;
    }

    if (MIN_SIZE > y || y > MAX_SIZE) {
        std::cerr << "Wrong input: y must be in interval " <<
        MIN_SIZE << "-" << MAX_SIZE << std::endl;
        return ERROR_INPUT;
    }

    if (MIN_COUNT_NODE > count_node || count_node > MAX_COUNT_NODE) {
        std::cerr << "Wrong input: k must be in interval " <<
        MIN_COUNT_NODE << "-" << MAX_COUNT_NODE << std::endl;
        return ERROR_INPUT;
    }
    return SUCCESS;
}

int Net::input_nodes() {
    Node_t node;

    std::cout << std::endl;
    for (size_t i = 0; i < count_node; i++) {
        std::cin >> node.x >> node.y;

        if (MIN_SIZE > node.x || node.x > x) {
            std::cerr << "Wrong input: node x must be in interval " <<
            MIN_SIZE << "-" << x << std::endl;
            return ERROR_INPUT;
        }

        if (MIN_SIZE > node.y || node.y > y) {
            std::cerr << "Wrong input: node y must be in interval " <<
            MIN_SIZE << "-" << y << std::endl;
            return ERROR_INPUT;
        }

        node.y = y - node.y + 1;
        nodes.push_back(node);
    }

    nodes.push_back(nodes[0]);

    return SUCCESS;
}

Net::Net() {
    input_size();
    input_nodes();
}


size_t** Net::create_net() {
    size_t** net = new size_t * [y];
    for (size_t i = 0; i < y; i++) {
        net[i] = new size_t [x];
    }

    return net;
}

void Net::del_net(size_t** net) {
    for (size_t i = 0; i < y; i++) {
        delete[] net[i];
    }

    delete [] net;
}


void Net::print(size_t** net) {
    for (size_t i = 0; i < y; i++) {
        for (size_t j = 0; j < x; j++) {
            std::cout << net[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

//  0 - white block
//  1 - back block
//  2 - full block
//  3 - half block
//  4 - 1/4 block
//  5 - 3/4 block

//  direction
//  0 - empty
//  1 - hor
//  2 - ver

void Net::set_black(size_t** net, size_t start, size_t end, size_t const const_index, size_t direction) {
    size_t max = std::max(start, end);

    size_t min = std::min(start, end);

    if (direction == 1) {
        for (size_t i = min - 1; i < max; i++) {
            net[const_index - 1][i] = 1;
        }

        return;
    }

    if (direction == 2) {
        for (size_t i = min - 1; i < max; i++) {
            net[i][const_index - 1] = 1;
        }

        return;
    }
}

void Net::filling(size_t** net) {
    size_t direction = 0;

    for (size_t i = 0; i < nodes.size(); i++) {
        std::cout << nodes[i].x << " " << nodes[i].y << std::endl;
    }

    for (size_t i = 0; i < nodes.size() - 1; i++) {
        if (nodes[i].x == nodes[i + 1].x) {
            direction = 2;
            set_black(net, nodes[i].y, nodes[i + 1].y, nodes[i].x, direction);
        }

        if (nodes[i].y == nodes[i + 1].y) {
            direction = 1;
            set_black(net, nodes[i].x, nodes[i + 1].x, nodes[i].y, direction);
        }
    }

}

size_t Net::check_1(size_t **net, size_t i_in, size_t in_j) {
    if
}



void Net::get_res_count() {
    size_t** net = create_net();

    filling(net);

    print(net);

    del_net(net);
}


int main() {
    Net net;

    net.get_res_count();

    return SUCCESS;
}
