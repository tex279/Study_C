#include <stdio.h>
#include <string.h>
#include <base_utils_file.h>
#include <test_compare.h>
#include <std_in_out.h>


#define TARGET_TEST    "record111.dat"


int foo_comparator(Data *expected_data, Data *got_data) {
    if (expected_data->Number == got_data->Number &&
        (strcmp(expected_data->Name, got_data->Name) == 0) &&
        (strcmp(expected_data->Surname, got_data->Surname) == 0) &&
        (strcmp(expected_data->Address, got_data->Address) == 0) &&
        (strcmp(expected_data->TelNumber, got_data->TelNumber) == 0) &&
         expected_data->Indebtedness == got_data->Indebtedness &&
         expected_data->Credit_limit == got_data->Credit_limit &&
         expected_data->Cash_payments == got_data->Cash_payments) {
        return 1;
    } else {
        return 0;
    }
}


void test_write_to_file() {
    const char *filename = TARGET_TEST;
    clear_file(TARGET_TEST);
    Data expected_data;
    input(&expected_data);
    write_to_file(filename, &expected_data);
    Data got_data;
    read_from_file(filename, &got_data);
    foo_comparator(&expected_data, &got_data) ?
    printf("%s\n", "TEST COMPARE SUCCESS") :
    printf("%s\n", "TEST COMPARE FAILED");
}
