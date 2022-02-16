#include <iostream>
#include <algorithm>

#define MAX_LENGTH 10000
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

    size_t res = 0;
    size_t buf = 0;
    size_t tmp = 0;

    for (size_t i = 0; i < count; i++) {
        std::cin >> buf;

        if (buf == 1) {
            tmp++;
        }

        if (buf == 0 || i == count - 1) {
            res = std::max(res, tmp);

            tmp = 0;
        }
    }

    std::cout << res << std::endl;

    return SUCCESS;
}
