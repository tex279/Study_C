#include <iostream>
#include <unordered_set>
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

    if (MIN_LENGTH > first.length() || first.length() > MAX_LENGTH) {
        FATAL_LIMITS(MIN_LENGTH, MAX_LENGTH, "string 1 length");
    }

    std::string second;

    std::cin >> second;

    if (MIN_LENGTH > second.length() || second.length() > MAX_LENGTH) {
        FATAL_LIMITS(MIN_LENGTH, MAX_LENGTH, "string 2 length");
    }

    std::unordered_set<char> fir;
    std::unordered_set<char> sec;

    for (char ch : first) {
        fir.insert(ch);
    }

    for (char ch : second) {
        sec.insert(ch);
    }

    if (fir == sec) {
        std::cout << 1 << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }

    return SUCCESS;
}
