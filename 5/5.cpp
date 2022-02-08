#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_VER 500000
#define MIN_VER 1

#define MAX_COUNT_RULE 200000
#define MIN_COUNT_RULE 0

#define A 1
#define B 2
#define C 3

#define ERROR_INPUT -1
#define SUCCESS 1

typedef struct Rule {
    size_t module;
    size_t version;

    size_t needed_module;
    size_t needed_version;
} Rule_t;

class SystemVersion {
    size_t max_version_A;
    size_t max_version_B;
    size_t max_version_C;

    size_t count_rules;

    std::vector <Rule_t> rules;
public:
    int input_max_version();
    int input_rules();

    void get_res_count();

    bool* set_block(bool net[][][]);

    SystemVersion();
    ~SystemVersion() = default;
};

int SystemVersion::input_max_version() {
    std::cin >> max_version_A >> max_version_B >> max_version_C;

    if (MIN_VER > max_version_A || max_version_A > MAX_VER) {
        std::cerr << "Wrong input: max_ver must be in interval " <<
        MIN_VER << "-" << MAX_VER << std::endl;
        return ERROR_INPUT;
    }

    if (MIN_VER > max_version_B || max_version_B > MAX_VER) {
        std::cerr << "Wrong input: max_ver must be in interval " <<
                  MIN_VER << "-" << MAX_VER << std::endl;
        return ERROR_INPUT;
    }

    if (MIN_VER > max_version_C || max_version_C > MAX_VER) {
        std::cerr << "Wrong input: max_ver must be in interval " <<
                  MIN_VER << "-" << MAX_VER << std::endl;
        return ERROR_INPUT;
    }

    return SUCCESS;
}

int SystemVersion::input_rules() {
    std::cin >> count_rules;

    if (MIN_COUNT_RULE > count_rules || count_rules > MAX_COUNT_RULE) {
        std::cerr << "Wrong input: count rules must be in interval " <<
        MIN_COUNT_RULE << "-" << MAX_COUNT_RULE << std::endl;
        return ERROR_INPUT;
    }

    Rule_t rule_in;

    for (size_t i = 0; i < count_rules; i++) {
        std::cin >> rule_in.module >> rule_in.version >> rule_in.needed_module >> rule_in.needed_version;

        rules.push_back(rule_in);
    }

    return SUCCESS;
}

SystemVersion::SystemVersion() {
    input_max_version();
    input_rules();
}

bool* set_block(bool net[][][], size_t i, size_t j, size_t k) {
    for (size_t ii = i; ii < i; ii++) {
        for (size_t jj = j; jj < j; jj++) {
            for (size_t kk = k; kk < k; kk++) {
                net[i][j][j] = true;
            }
        }
    }
}

void SystemVersion::get_res_count() {
    size_t res_max_combination = max_version_A * max_version_B * max_version_C;

    bool net_block[max_version_A][max_version_B][max_version_C];
    for (size_t i = 0; i < count_rules; i++) {
        if (rules[i].module == C) {
            if (rules[i].needed_module == B) {
                block_combination = (max_version_C - rules[i].version + 1) * rules[i].needed_module * max_version_A;

                set_block(net_block, max_version_A, )
            }

            if (rules[i].needed_module == A) {
                block_combination = (max_version_C - rules[i].version + 1) * (rules[i].needed_version - 1) * max_version_B;
                res_max_combination -= block_combination;
            }
        }
    }

    std::cout << res_max_combination << std::endl;
}


int main() {
    SystemVersion ver;

    ver.get_res_count();

    return SUCCESS;
}






/*
 *
 for (size_t i = 0; i < count_rules; i++) {

    }
    */
