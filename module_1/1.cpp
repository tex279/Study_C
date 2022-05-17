#include <iostream>
#include <cassert>

//  Инвертируйте значение бита в числе N по его номеру K.
//  Необходимо использование битовых операций.
//  Использование арифметических операций запрещено.

#define MAX_NUMBER (u_int32_t)(2e32 - 1)
#define MAX_BIT (u_int32_t)(32 - 1)

u_int32_t input(u_int32_t max) {
    u_int32_t number = 0;

    std::cin >> number;

    assert(max >= number);

    return number;
}

int main() {
    u_int32_t number = input(MAX_NUMBER);

    u_int32_t bit = input(MAX_BIT);

    u_int32_t res = number ^ (1 << bit);

    std::cout << res << std::endl;

    return EXIT_SUCCESS;
}
