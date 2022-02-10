#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>

#define LOW_COUNT 1
#define HIGH_COUNT 2 * 10000

#define LOW_WIDTH 1
#define HIGH_WIDTH 10e18


#define ERROR_INPUT -1
#define SUCCESS 0

class Tower {
    size_t count_plates;
    size_t count_volunteers;

    std::vector <unsigned long int> plates;
    std::vector <unsigned long int> volunteers;
public:
    int input_count();
    int input_parameters();

    void get_res_count();

    Tower();
    ~Tower() = default;
};

int Tower::input_count() {
    std::cin >> count_plates >> count_volunteers;

    if ((LOW_COUNT > count_plates) || (count_plates > HIGH_COUNT)) {
        std::cerr << "Wrong input: count must be in interval " <<
                  LOW_COUNT << "-" << HIGH_COUNT << std::endl;
        return ERROR_INPUT;
    }

    if ((LOW_COUNT > count_volunteers) || (count_volunteers > HIGH_COUNT)) {
        std::cerr << "Wrong input: count must be in interval " <<
                  LOW_COUNT << "-" << HIGH_COUNT << std::endl;
        return ERROR_INPUT;
    }

    return SUCCESS;
}

int Tower::input_parameters() {
    unsigned long int buf;
    for (size_t i = 0; i < count_plates; ++i) {
        std::cin >> buf;
        if ((LOW_WIDTH > buf) || (buf > HIGH_WIDTH)) {
            std::cerr << "Wrong input: width must be in interval " <<
                      LOW_WIDTH << "-" << HIGH_WIDTH << std::endl;
            return ERROR_INPUT;
        }
        plates.push_back(buf);
    }

    for (size_t j = 0; j < count_volunteers; ++j) {
        std::cin >> buf;
        if ((LOW_WIDTH > buf) || (buf > HIGH_WIDTH)) {
            std::cerr << "Wrong input: width must be in interval " <<
                      LOW_WIDTH << "-" << HIGH_WIDTH << std::endl;
            return ERROR_INPUT;
        }
        volunteers.push_back(buf);
    }

    std::sort(volunteers.begin(), volunteers.end());

    std::reverse(plates.begin(), plates.end());

    return SUCCESS;
}

Tower::Tower() {
   input_count();
   input_parameters();
}

void Tower::get_res_count() {
    std::vector <unsigned long int> free_width;

    free_width.push_back(plates[0]);

    unsigned long int max = plates[0];
    unsigned long int buf;
    for (size_t i = 1; i < count_plates; ++i) {
        if (plates[i] > max) {
            buf = max;
            max = plates[i];
            free_width.push_back(max - buf);
        }
    }

    std::sort(free_width.begin(), free_width.end());

    size_t count = 0;

    size_t i = 0;
    size_t j = 0;
    while (true) {
        if (volunteers[j] <= free_width[i]) {
            count++;

            ++i;
            ++j;
        } else {
            ++i;
        }

        if (j == volunteers.size() || i == free_width.size()) {
            break;
        }
    }

    std::cout << count << std::endl;
}

int main() {
    Tower tower;

    tower.get_res_count();

    return SUCCESS;
}
