#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

#define MAX_VER 500000
#define MIN_VER 1

#define MAX_COUNT_RULE 200000
#define MIN_COUNT_RULE 0

#define A 1
#define B 2
#define C 3

#define ERROR_INPUT -1
#define SUCCESS 0

typedef struct Rule {
    size_t module;
    size_t version;

    size_t needed_module;
    size_t needed_version;
} Rule_t;

class SystemVersion {
public:
    size_t max_version_A;
    size_t max_version_B;
    size_t max_version_C;

    size_t count_rules;

    std::vector <Rule_t> rules;

    int input_max_version();
    int input_rules();

    bool*** create_net();
    int del_net(bool*** net);

    void print(bool*** net);

    void get_res_count();

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


bool*** SystemVersion::create_net() {
    bool*** net = new bool ** [max_version_A];
    for (size_t i = 0; i < max_version_A; i++) {
        net[i] = new bool * [max_version_B];

        for (size_t j = 0; j < max_version_B; j++) {
            net[i][j] = new bool [max_version_C];
        }
    }

    return net;
}

int SystemVersion::del_net(bool*** net) {
    for (size_t i = 0; i < max_version_A; i++) {
        for (size_t j = 0; j < max_version_B; j++) {
            delete [] net[i][j];
        }
        delete[] net[i];
    }

    delete [] net;

    return SUCCESS;
}


void set_block(bool*** net, size_t i, size_t max_i, size_t j, size_t max_j, size_t k, size_t max_k) {
    for (size_t ii = i - 1; ii < max_i; ii++) {
        for (size_t jj = j - 1; jj < max_j; jj++) {
            for (size_t kk = k - 1; kk < max_k; kk++) {
                net[ii][jj][kk] = true;
            }
        }
    }
}

void SystemVersion::print(bool*** net) {
    std::cout << "\n";
    std::cout << "B-вниз C-право\n";
    for (size_t i = 0; i < max_version_A; i++) {
        std::cout << "Новый слой - А\n";
        for (size_t j = 0; j < max_version_B; j++) {
            for (size_t k = 0; k < max_version_C; k++) {
                std::cout << net[i][j][k] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    std::cout << std::endl;

}

void SystemVersion::get_res_count() {
    size_t res_max_combination = max_version_A * max_version_B * max_version_C;

    bool*** net = create_net();

    for (size_t i = 0; i < count_rules; i++) {
        if (rules[i].module == C) {
            if (rules[i].needed_module == B) {
                set_block(net,
                          1, max_version_A,
                          1, rules[i].needed_version - 1,
                          rules[i].version, max_version_C);
            }

            if (rules[i].needed_module == A) {
                set_block(net,
                          1, rules[i].needed_version - 1,
                          1, max_version_B,
                          rules[i].version, max_version_C);
            }
        }

        if (rules[i].module == A) {
            if (rules[i].needed_module == B) {
                set_block(net,
                          rules[i].version, max_version_A,
                          1, rules[i].needed_version - 1,
                          1, max_version_C);
            }

            if (rules[i].needed_module == C) {
                set_block(net,
                          rules[i].version, max_version_A,
                          1, max_version_B,
                          1, rules[i].needed_version - 1);
            }
        }

        if (rules[i].module == B) {
            if (rules[i].needed_module == C) {
                set_block(net,
                          1, max_version_A,
                          rules[i].version, max_version_B,
                          1, rules[i].needed_version - 1);

            }

            if (rules[i].needed_module == A) {
                set_block(net,
                          1, rules[i].needed_version - 1,
                          rules[i].version, max_version_B,
                          1, max_version_C);
            }
        }
    }

    for (size_t i = 0; i < max_version_A; i++) {
        for (size_t j = 0; j < max_version_B; j++) {
            for (size_t k = 0; k < max_version_C; k++) {
                if (net[i][j][k] == true) {
                    res_max_combination--;
                }
            }
        }
    }

    print(net);

    del_net(net);

    std::cout << res_max_combination << std::endl;
}


int main() {
    SystemVersion ver;

    ver.get_res_count();

    return SUCCESS;
}

