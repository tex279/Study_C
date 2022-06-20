#include <iostream>
#include <array>
#include <algorithm>
#include <iomanip>

#include "greedy.hpp"

#define MAX_WEIGHT 61
#define COUNT_ITEMS 14

size_t backpack_problem() {
    int const count_items = COUNT_ITEMS;

    const std::array<int, count_items> mass   {{26,   9,  1,  6,  8,  11,  3,  9,  27, 10, 19, 21, 26, 23}};
    const std::array<int, count_items> prise  {{32,   13, 38, 37, 16, 31,  38, 20, 27, 31, 11, 2,  39, 9}};


    int net[mass.size() + 1][MAX_WEIGHT + 1];

    //  Индекс i отвечает за предмет
    //  Индекс j отвечает за массу

    for (int i = 0; i <= (int)mass.size(); i++) {
        for (int j = 0; j <= MAX_WEIGHT; j++) {
            //  Строка фейк (нулевой массы)
            if (i == 0 || j == 0) {
                net[i][j] = 0;
            } else {
                //  Если новый предмет превышает промежуточную емкость то принимаем прошлое значение
                if (mass[i - 1] > j) {
                    net[i][j] = net[i - 1][j];
                } else {
                    //  Последнее вычесленное
                    int prev = net[i - 1][j];

                    //  Проверка доп цены
                    int byFormula = prise[i - 1] + net[i - 1][j - mass[i - 1]];

                    // Выбираем новое максимальное
                    net[i][j] = std::max(prev, byFormula);
                }
            }
        }
    }

    // Вывод таблицы без фейка
    for (int i = 1; i <= (int)mass.size(); i++) {
        for (int j = 1; j <= MAX_WEIGHT; j++) {
            std::cout << std::setw(3) << net[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    std::cout << "RES: " << std::setw(7) << std::setw(5) << net[mass.size()][MAX_WEIGHT] << std::endl;

    return net[mass.size()][MAX_WEIGHT];
}
