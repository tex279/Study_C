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

    SystemVersion();
    ~SystemVersion() = default;
};

int SystemVersion::input_max_version() {
    size_t A_max;
    size_t B_max;
    size_t C_max;
    std::cin >> A_max >> B_max >> C_max;

    if (MIN_VER > A_max || A_max > MAX_VER) {
        std::cerr << "Wrong input: max_ver must be in interval " <<
        MIN_VER << "-" << MAX_VER << std::endl;
        return ERROR_INPUT;
    }

    if (MIN_VER > B_max || B_max > MAX_VER) {
        std::cerr << "Wrong input: max_ver must be in interval " <<
                  MIN_VER << "-" << MAX_VER << std::endl;
        return ERROR_INPUT;
    }

    if (MIN_VER > C_max || C_max > MAX_VER) {
        std::cerr << "Wrong input: max_ver must be in interval " <<
                  MIN_VER << "-" << MAX_VER << std::endl;
        return ERROR_INPUT;
    }

    max_version_A = A_max;
    max_version_B = B_max;
    max_version_C = C_max;


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

void SystemVersion::get_res_count() {

}


int main() {
    SystemVersion ver;

    ver.get_res_count();

    return SUCCESS;
}
