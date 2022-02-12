#include <iostream>
#include <string>

#define MAX_LENGTH_STR 100
#define MIN_LENGTH_STR 1

#define SUCCESS 0

#define ERROR_INPUT -1

#define FATAL_LIMITS(low_limit, max_limit, message) {                   \
    std::cerr << "Bad input: " << message << " must be in interval " << \
    low_limit << "-" << max_limit << std::endl;                         \
    exit(ERROR_INPUT);                                                  \
}

int main(void) {
    std::string jewelry;

    std::cin >> jewelry;

    size_t jewelry_l = jewelry.length();
    if (MIN_LENGTH_STR > jewelry_l || jewelry_l > MAX_LENGTH_STR) {
        FATAL_LIMITS(MIN_LENGTH_STR, MAX_LENGTH_STR, "string length");
    }

    std::string stone;

    std::cin >> stone;

    size_t stone_l = stone.length();
    if (MIN_LENGTH_STR > stone_l || stone_l > MAX_LENGTH_STR) {
        FATAL_LIMITS(MIN_LENGTH_STR, MAX_LENGTH_STR, "string length");
    }

    size_t res = 0;

    for (const char ch : stone) {
        res += jewelry.find(ch) != std::string::npos;
    }

    std::cout << res << std::endl;

    return SUCCESS;
}

