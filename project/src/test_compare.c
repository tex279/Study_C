#include <w_r_files.h>
#include <test_compare.h>
#include <stdio.h>
#include <string.h>

#define TARGET_TEST    "record.dat"


void test_write_to_file() {
    const char *filename = TARGET_TEST;
    Some expected_data;
    expected_data.Number = 1;
    expected_data.Name[20] = *"name_1";
    expected_data.Surname[20] = *"surname_1";
    expected_data.address[30] = *"address_1";
    expected_data.TelNumber[15] = *"tel_1";
    expected_data.indebtedness = 80;
    expected_data.credit_limit = 150;
    expected_data.cash_payments = 20;
    write_to_file(filename, &expected_data);
    Some got_data;
    read_from_file(filename, &got_data);
    if ((expected_data.Number == got_data.Number &&
    strcmp(expected_data.Name, got_data.Name) &&
    strcmp(expected_data.Surname, got_data.Surname) &&
    strcmp(expected_data.address, got_data.address) &&
    strcmp(expected_data.TelNumber, got_data.TelNumber) &&
    expected_data.indebtedness == got_data.indebtedness &&
    expected_data.credit_limit == got_data.credit_limit &&
    expected_data.cash_payments == got_data.cash_payments) == 0) {
        printf("%s\n", "TEST COMPARE SUCCESS");
    } else {
        printf("%s\n", "TEST COMPARE FAILED");
    }
}
