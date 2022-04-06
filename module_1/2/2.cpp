#include <cstddef>
#include <vector>
#include <iostream>
#include <algorithm>

#define LOW_LEVEL_HEIGHT 2
#define HIGH_LEVEL_HEIGHT 100

#define LOW_LEVEL_WIDTH 3
#define HIGH_LEVEL_WIDTH 100

#define HIGH_LEVEL_INGREDIENT 89

#define LOW_LEVEL_SYMBOL 32
#define HIGH_LEVEL_SYMBOL 127

#define ERROR_INPUT -1
#define SUCCESS 0

class Cup {
    size_t height_n;
    size_t width_m;

    std::vector<std::string> form_cup;

    size_t count_ingredients;

    std::vector<std::string> names;
    std::vector<size_t> count_layers;
    std::vector<char> symbols;
public:
    int limits();

    void get_form_cup();

    int get_count_ingredients();

    int ingredient();

    void filling();

    Cup() = default;
    ~Cup() = default;

    void print();
};

int Cup::limits() {
    size_t n;
    size_t m;
    std::cin >> n >> m;

    if ((LOW_LEVEL_HEIGHT > n) || (n > HIGH_LEVEL_HEIGHT)) {
        std::cerr << "Wrong input: height_n must be in interval " <<
                  LOW_LEVEL_HEIGHT << "-" << HIGH_LEVEL_HEIGHT << std::endl;
        return ERROR_INPUT;
    }

    if ((LOW_LEVEL_WIDTH > m) || (m > HIGH_LEVEL_WIDTH)) {
        std::cerr << "Wrong input: width_m must be in interval " <<
                  LOW_LEVEL_WIDTH << "-" << HIGH_LEVEL_WIDTH << std::endl;
        return ERROR_INPUT;
    }

    height_n = n;
    width_m = m;

    return SUCCESS;
}

void Cup::get_form_cup() {
    std::cin.width(width_m);
    std::string buf;
    for (size_t i = 0; i <= height_n; i++) {
        std::getline(std::cin, buf);

        form_cup.push_back(buf);
    }

    std::string buf_01;
    for (auto line_bar: form_cup) {
        buf_01 += line_bar.data();
    }
}

int Cup::get_count_ingredients() {
    size_t k;
    std::cin >> k;

    size_t min = std::min(height_n - 1, (size_t)HIGH_LEVEL_WIDTH);
    if (k > min) {
        std::cerr << "Wrong input: count ingredients must be in interval " <<
                  (height_n - 1) << "-" << HIGH_LEVEL_INGREDIENT << std::endl;
        return ERROR_INPUT;
    }

    count_ingredients = k;

    return SUCCESS;
}

int Cup::ingredient() {
    std::string name;
    size_t count;
    char symbol;
    for (size_t i = 1; i <= count_ingredients; i++) {
        std::cin >> name >> count >> symbol;

        if (!((int) symbol > LOW_LEVEL_SYMBOL) || !((int) symbol < HIGH_LEVEL_SYMBOL)) {
            std::cerr << "Wrong input: code your symbol must be in interval " <<
                      LOW_LEVEL_SYMBOL << "-" << HIGH_LEVEL_SYMBOL << std::endl;
            return ERROR_INPUT;
        }

        names.push_back(name);
        count_layers.push_back(count);
        symbols.push_back(symbol);
    }

    return SUCCESS;
}

void Cup::filling() {
    std::vector<size_t>::iterator it_c = count_layers.begin();
    std::vector<char>::const_iterator it_s = symbols.begin();

    size_t right_pos;
    size_t left_pos;
    size_t length_filling;
    for (size_t i = (height_n - 1); i != 0; i--) {
        size_t l_check_f_s = form_cup[i].find("/");
        if (l_check_f_s == 0) {
            left_pos = l_check_f_s + 1;
        }

        l_check_f_s = form_cup[i].find("./");
        if (l_check_f_s != std::string::npos)
            left_pos = l_check_f_s + 2;




        size_t l_check_v_b = form_cup[i].find("|");
        if (l_check_v_b == 0) {
            left_pos = l_check_v_b + 1;
        }

        l_check_v_b = form_cup[i].find(".|");
        if (l_check_v_b != std::string::npos)
            left_pos = l_check_v_b + 2;




        size_t l_check_b_s = form_cup[i].find("\\");
        if (l_check_b_s == 0) {
            left_pos = l_check_b_s + 1;
        }

        l_check_b_s = form_cup[i].find(".\\");
        if (l_check_b_s != std::string::npos)
            left_pos = l_check_b_s + 2;





        size_t r_check_f_s = form_cup[i].rfind("/");
        if (r_check_f_s == form_cup[i].length() - 1) {
            right_pos = r_check_f_s;
        }

        r_check_f_s = form_cup[i].rfind("/.");
        if (r_check_f_s != std::string::npos)
            right_pos = r_check_f_s;



        size_t r_check_v_b = form_cup[i].rfind("|");
        if (r_check_v_b == form_cup[i].length() - 1) {
            right_pos = r_check_v_b;
        }

        r_check_v_b = form_cup[i].rfind("|.");
        if (r_check_v_b != std::string::npos)
            right_pos = r_check_v_b;



        size_t r_check_b_s = form_cup[i].rfind("\\");
        if (r_check_b_s == form_cup[i].length() - 1) {
            right_pos = r_check_b_s;
        }

        r_check_b_s = form_cup[i].rfind("\\.");
        if (r_check_b_s != std::string::npos)
            right_pos = r_check_b_s;

        length_filling = right_pos - left_pos;

        form_cup[i].replace(left_pos, length_filling, length_filling, *it_s);
        (*it_c)--;
        if (*it_c == 0) {
            it_s++;
            it_c++;
            count_ingredients--;
        }

        if (count_ingredients == 0) {
            break;
        }
    }
}

void Cup::print() {
    for (size_t i = 1; i <= form_cup.capacity(); i++) {
        std::cout << form_cup[i].data() << "\n";
    }
}

int main() {
    Cup cup;

    cup.limits();
    cup.get_form_cup();

    cup.get_count_ingredients();
    cup.ingredient();

    cup.filling();

    cup.print();
    return SUCCESS;
}

