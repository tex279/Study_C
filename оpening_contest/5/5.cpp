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

//  Нужен сет
typedef struct Rule {
    unsigned int module;
    unsigned int version;

    unsigned int needed_module;
    unsigned int needed_version;
} Rule_t;

class SystemVersion {
public:
    unsigned int max_version_A;
    unsigned int max_version_B;
    unsigned int max_version_C;

    unsigned int count_rules;

    std::vector <Rule_t> rules;

    int input_max_version();
    int input_rules();

    bool** create_net();
    int del_net(bool** net);

    void print(bool** net);

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

    for (size_t i = 0; i < count_rules; ++i) {
        std::cin >> rule_in.module >> rule_in.version >> rule_in.needed_module >> rule_in.needed_version;

        rules.push_back(rule_in);
    }

    return SUCCESS;
}

SystemVersion::SystemVersion() {
    input_max_version();
    input_rules();
}


bool** SystemVersion::create_net(size_t one, size_t two) {
    bool** net = new bool * [one];
    for (size_t i = 0; i < one; ++i) {
        net[i] = new bool [two];
    }

    return net;
}

int SystemVersion::del_net(bool** net, size_t one, size_t two) {
    for (size_t i = 0; i < one; ++i) {
        delete[] net[i];
    }

    delete [] net;

    return SUCCESS;
}


void set_block(bool** net, size_t i, size_t max_i, size_t j, size_t max_j) {
    for (size_t ii = i - 1; ii < max_i; ++ii) {
        for (size_t jj = j - 1; jj < max_j; ++jj) {
            net[ii][jj] = true;
        }
    }
}

void SystemVersion::print(bool** net, size_t one, size_t two) {
    std::cout << "\n";
    std::cout << "\n";
    for (size_t i = 0; i < one; ++i) {
        for (size_t j = 0; j < two; ++j) {
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    std::cout << std::endl;

}

void SystemVersion::get_res_count() {
    size_t res_max_combination = max_version_A * max_version_B * max_version_C;

    bool** net_A_B = create_net(max_version_A, max_version_B);
    bool** net_B_C = create_net(max_version_B, max_version_C);
    bool** net_C_A = create_net(max_version_C, max_version_A);

    for (size_t i = 0; i < count_rules; ++i) {
        if (rules[i].module == C) {
            if (rules[i].needed_module == B) {
                //res_max_combination -= (max_version_A) * (rules[i].needed_version - 1) * (max_version_C - rules[i].version + 1);
                /*set_block(net,
                          1, max_version_A,
                          1, rules[i].needed_version - 1,
                          rules[i].version, max_version_C);*/

                set_block(net_B_C, )
            }

            if (rules[i].needed_module == A) {
                //res_max_combination -= (rules[i].needed_version - 1) * (max_version_B) * (max_version_C - rules[i].version + 1);
                /*set_block(net,
                          1, rules[i].needed_version - 1,
                          1, max_version_B,
                          rules[i].version, max_version_C);*/
            }
        }

        if (rules[i].module == A) {
            if (rules[i].needed_module == B) {
                //res_max_combination -= (max_version_A - rules[i].version + 1) * (rules[i].needed_version - 1) * (max_version_C);
                /*set_block(net,
                          rules[i].version, max_version_A,
                          1, rules[i].needed_version - 1,
                          1, max_version_C);*/
            }

            if (rules[i].needed_module == C) {
                //res_max_combination -= (max_version_A - rules[i].version + 1) * (max_version_B) * (rules[i].needed_version - 1);
                /*set_block(net,
                          rules[i].version, max_version_A,
                          1, max_version_B,
                          1, rules[i].needed_version - 1);*/
            }
        }

        if (rules[i].module == B) {
            if (rules[i].needed_module == C) {
                //res_max_combination -= (max_version_A) * (max_version_B - rules[i].version + 1) * (rules[i].needed_version - 1);
                /*set_block(net,
                          1, max_version_A,
                          rules[i].version, max_version_B,
                          1, rules[i].needed_version - 1);*/

            }

            if (rules[i].needed_module == A) {
                //res_max_combination -= (rules[i].needed_version - 1) * (max_version_B - rules[i].version + 1) * (max_version_C);
                /*set_block(net,
                          1, rules[i].needed_version - 1,
                          rules[i].version, max_version_B,
                          1, max_version_C);*/
            }
        }
    }

    /*for (size_t i = 0; i < max_version_A; ++i) {
        for (size_t j = 0; j < max_version_B; ++j) {
            for (size_t k = 0; k < max_version_C; ++k) {
                if (net[i][j][k] == true) {
                    res_max_combination--;
                }
            }
        }
    }*/

    //print(net);

    //del_net(net);

    std::cout << res_max_combination << std::endl;
}


int main() {
    SystemVersion ver;

    ver.get_res_count();

    return SUCCESS;
}
