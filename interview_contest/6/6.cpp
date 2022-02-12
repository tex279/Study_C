#include <iostream>
#include <vector>
#include <set>
#include <cmath>

#define MAX_COUNT 1000
#define MIN_COUNT 2

#define MAX_LENGTH 2000000000
#define MIN_LENGTH 0

#define MAX_COR 1000000000
#define MIN_COR 0

#define SUCCESS 0

#define ERROR_INPUT -1

#define FATAL_LIMITS(low_limit, max_limit, message) {                   \
    std::cerr << "Bad input: " << message << " must be in interval " << \
    low_limit << "-" << max_limit << std::endl;                         \
    exit(ERROR_INPUT);                                                  \
}

typedef struct City {
    int x;
    int y;
} City_t;

size_t get_distance(City_t source, City_t target) {
    return (abs(target.x - source.x) + abs(target.y - source.y));
}

bool check_edge(City_t source, City_t target, size_t max_distance) {
    return (get_distance(source, target) <= max_distance);
}

size_t bfs(size_t start_key, size_t finish_key, size_t count_cities) {
    std::set <size_t> visited;
    visited.push_back(start_key);
}

int main(void) {
    size_t count_city;

    std::cin >> count_city;

    if (MIN_COUNT > count_city || count_city > MAX_COUNT) {
        FATAL_LIMITS(MIN_COUNT, MAX_COUNT, "count city");
    }

    std::vector <City_t> cities;

    City_t buf;

    for (size_t i = 0; i < count_city; i++) {
        std::cin >> buf.x >> buf.y;
        if (abs(buf.x) > MAX_COR || abs(buf.y) > MAX_COR) {
            FATAL_LIMITS(MIN_COR, MAX_COR, "coordinate city");
        }

        cities.push_back(buf);
    }

    size_t max_distance;

    std::cin >> max_distance;

    if (MIN_LENGTH > max_distance || max_distance > MAX_LENGTH) {
        FATAL_LIMITS(MIN_LENGTH, MAX_LENGTH, "distance");
    }

    size_t source;
    size_t target;

    std::cin >> source >> target;




    for (size_t i = 0; i < count_city; i++) {
        for (size_t j = 1; j < count_city - i; j++) {

        }
    }

    return SUCCESS;
}
