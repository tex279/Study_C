#include <iostream>
#include <string>

#define SUCCESS 0

#define ERROR_INPUT -1



int main(void) {
    std::string str;

    std::cin >> str;

    char buf;
    size_t res = 0;
    size_t count_tmp = 0;

    for (auto ch : str) {
        if (count_tmp == 0) {
            buf = ch;
        }

        if (ch == buf) {
            count_tmp++;
        } else {
            if (res < count_tmp || ch == str.back()) {
                res = count_tmp;
            }

            count_tmp = 0;
        }
    }

    if (res < count_tmp) {
        res = count_tmp;
    }

    std::cout << res;
    return SUCCESS;
}
