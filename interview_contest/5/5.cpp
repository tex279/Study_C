#include <iostream>
#include <string>

#define MAX_LENGTH 100000
#define MIN_LENGTH 0

#define SUCCESS 0

#define ERROR_INPUT -1

#define FATAL_LIMITS(low_limit, max_limit, message) {                   \
    std::cerr << "Bad input: " << message << " must be in interval " << \
    low_limit << "-" << max_limit << std::endl;                         \
    exit(ERROR_INPUT);                                                  \
}

int main(void) {
    std::string first;

    std::cin >> first;

    size_t first_l = first.length();
    if (MIN_LENGTH > first_l || first_l > MAX_LENGTH) {
        FATAL_LIMITS(MIN_LENGTH, MAX_LENGTH, "string length");
    }

    std::string second;

    std::cin >> second;

    size_t second_l = second.length();
    if (MIN_LENGTH > second_l || second_l > MAX_LENGTH) {
        FATAL_LIMITS(MIN_LENGTH, MAX_LENGTH, "string length");
    }

    std::sort(first.begin(), first.end());

    std::sort(second.begin(), second.end());

    if (first == second) {
        std::cout << 1 << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }

    return SUCCESS;
}
