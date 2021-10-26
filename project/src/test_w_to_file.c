#include <stdio.h>
#include <string.h>

#include <w_r_file.h>
#include <test_w_to_file.h>
#include <std_in_out_data.h>

int foo_comparator(Data *expected_data, Data *got_data) {
    if (!(expected_data->number == got_data->number &&
        (strcmp(expected_data->name, got_data->name) == 0) &&
        (strcmp(expected_data->surname, got_data->surname) == 0) &&
        (strcmp(expected_data->address, got_data->address) == 0) &&
        (strcmp(expected_data->tel_number, got_data->tel_number) == 0) &&
        expected_data->indebtedness == got_data->indebtedness &&
        expected_data->credit_limit == got_data->credit_limit &&
        expected_data->cash_payments == got_data->cash_payments)) {
        return INCORRECT_INPUT;
    }
    return SUCCESS;
}

void test_write_to_file(const char *filename) {
    Data expected_data;
    write_to_file(filename, &expected_data);
    Data got_data;
    read_from_file(filename, &got_data);
    output(&got_data);
    foo_comparator(&expected_data, &got_data) ?
    printf("%s\n", "TEST COMPARE STRUCT SUCCESS") :
    printf("%s\n", "TEST COMPARE STRUCT FAILED");
}
