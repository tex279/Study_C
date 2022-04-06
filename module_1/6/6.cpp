#include <cstddef>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#define MIN_COUNT 1
#define MAX_COUNT 3000

#define MIN_TIME 1
#define MAX_TIME 1000

#define ERROR_INPUT -1
#define SUCCESS 0

class CheckCommit {
    size_t short_t;
    size_t long_t;

    size_t count;

    std::string combination;

public:
    int input_combination();
    int input_parameters();

    void get_res_count();

    size_t check_max_length(char type);
    size_t check_count_realise();

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

    //std::cout << count << " " << short_t << " " << long_t << "\n" << combination << std::endl;
}

size_t CheckCommit::check_max_length(char type) {
    size_t max_time = 0;
    bool flag_base_type = false;
    bool flag_second_type = false;
    size_t max_count_type = 0;
    size_t max_count_type_local = 0;

    size_t time;

    char second_type;

    if (type == 'B') {
        second_type = 'S';
        time = long_t;
    } else if (type == 'S') {
        second_type = 'B';
        time = short_t;
    }

    for (size_t i = 0; i < count; i++ ) {
        if (flag_base_type == true) {
            max_count_type_local++;
        }

        if (combination[i] == type && flag_base_type == false) {
            flag_base_type = true;
            flag_second_type = false;

            max_count_type_local++;
        }

        if (combination[i] == second_type && flag_second_type == false) {
            flag_second_type = true;
            flag_base_type = false;

            max_count_type_local = 0;
        }

        if (max_count_type_local > max_count_type) {
            max_count_type = max_count_type_local;
        }
    }


    for (size_t i = 0; i < max_count_type; i++) {
        max_time += time;
    }

    return max_time;
}

size_t CheckCommit::check_count_realise() {
    size_t max_time = 0;
    bool flag_B = false;
    bool flag_S = false;

    std::string zip_combination;

    for (size_t i = 0; i < count; i++ ) {
        if (combination[i] == 'B' && flag_B == false) {
            zip_combination.push_back('B');
            flag_B = true;
            flag_S = false;
        }

        if (combination[i] == 'S' && flag_S == false) {
            zip_combination.push_back('S');
            flag_S = true;
            flag_B = false;
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

    return max_time;
}

void CheckCommit::get_res_count() {
    size_t max = std::max(check_max_length('B'), check_max_length('S'));
    max = std::max(max, check_count_realise());

    std::cout << max << std::endl;

}


int main() {
    CheckCommit cc;

    cc.get_res_count();

    return SUCCESS;
}
