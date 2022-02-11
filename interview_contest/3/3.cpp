#include <iostream>
#include <vector>

#define MAX_LENGTH 1000000
#define MIN_LENGTH 0

#define SUCCESS 0

#define ERROR_INPUT -1

#define FATAL_LIMITS(low_limit, max_limit, message) {                   \
    std::cerr << "Bad input: " << message << " must be in interval " << \
    low_limit << "-" << max_limit << std::endl;                         \
    exit(ERROR_INPUT);                                                  \
}

int main(void) {
    size_t count = 0;

    std::cin >> count;

    if (MIN_LENGTH > count || count > MAX_LENGTH) {
        FATAL_LIMITS(MIN_LENGTH, MAX_LENGTH, "count array");
    }

    size_t buf = 0;

    std::vector <size_t> res;

    for (size_t i = 0; i < count; i++) {
        std::cin >> buf;

        if (i == 0) {
            res.push_back(buf);
        }

        if (buf != res.back()) {
            res.push_back(buf);
        }
    }

    for (size_t i = 0; i < res.size(); i++) {
        std::cout << res[i] << std::endl;
    }

    return SUCCESS;
}
