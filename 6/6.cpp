#include <cstddef>
#include <iostream>
#include <algorithm>
#include <string>

#define MIN_COUNT 1
#define MAX_COUNT 3000

#define MIN_TIME 1
#define MAX_TIME 1000


#define ERROR_INPUT -1
#define SUCCESS 1

class CheckCommit {
    size_t short_t;
    size_t long_t;

    size_t count;

    std::string combination;

public:
    int input_combination();
    int input_parameters();

    void get_res_count();

    CheckCommit();
    ~CheckCommit() = default;
};

int CheckCommit::input_parameters() {
    std::cin >> count >> short_t >> long_t;

    if ((MIN_COUNT > count) || (count > MAX_COUNT)) {
        std::cerr << "Wrong input: count must be in interval " <<
        MIN_COUNT << "-" << MAX_COUNT << std::endl;
        return ERROR_INPUT;
    }

    if ((MIN_TIME > short_t) || (short_t > MAX_TIME)) {
        std::cerr << "Wrong input: count must be in interval " <<
        MIN_TIME << "-" << MAX_TIME << std::endl;
        return ERROR_INPUT;
    }

    if ((MIN_TIME > long_t) || (long_t > MAX_TIME)) {
        std::cerr << "Wrong input: count must be in interval " <<
        MIN_TIME << "-" << MAX_TIME << std::endl;
        return ERROR_INPUT;
    }

    return SUCCESS;
}

int CheckCommit::input_combination() {
    std::cin >> combination;

    if ((count != combination.size())) {
        std::cerr << "Wrong input: count combination must be " << count << std::endl;
        return ERROR_INPUT;
    }

    return SUCCESS;
}

CheckCommit::CheckCommit() {
    input_parameters();
    input_combination();
}

void CheckCommit::get_res_count() {
    size_t max_time = 0;
    bool flag_B = false;
    bool flag_S = false;
    size_t max_count_B = 0;
    size_t max_count_B_local = 0;

    std::string zip_combination;

    std::cout << count << " " << short_t << " " << long_t << "\n" << combination << std::endl;

    for (size_t i = 0; i < count; i++ ) {
        if (flag_B == true) {
            max_count_B_local++;
        }

        if (combination[i] == 'B' && flag_B == false) {
            zip_combination.push_back('B');
            flag_B = true;
            flag_S = false;

            max_count_B_local++;
        }

        if (combination[i] == 'S' && flag_S == false) {
            zip_combination.push_back('S');
            flag_S = true;
            flag_B = false;

            max_count_B_local = 0;
        }

        if (max_count_B_local > max_count_B) {
            max_count_B = max_count_B_local;
        }
    }

    for (size_t i = 0; i < zip_combination.size(); i++) {
        if (zip_combination[i] == 'B') {
            max_time += long_t;
        }
    }

    if (zip_combination.find("S") != std::string::npos) {
        max_time += short_t;
    }

    if (max_count_B > 2) {
        for (size_t i = 0; i < max_count_B - 2; i++) {
            max_time += long_t;
        }
    }

    std::cout << max_count_B << std::endl;
    std::cout << zip_combination << std::endl;
    std::cout << max_time << std::endl;
}


int main() {
    CheckCommit cc;

    cc.get_res_count();

    return SUCCESS;
}
