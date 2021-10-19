#include <w_r_files.h>
#include <test_compare.h>
#include <stdio.h>
#include <string.h>

#define TEST    "testingfile.dat"

/*struct some {
    int 		id;
    char 		Name[20];
};

typedef  struct  some Some;*/

void test_write_to_file() {
    const char *filename = TEST;
    Some expected_data;
    expected_data.id       = 231;
    const char name[20] = "Andropov";
    expected_data.Name[20] = name[20];
    write_to_file(filename, &expected_data);
    Some got_data;
    read_from_file(filename, &got_data);
    if (expected_data.id == got_data.id && strcmp(expected_data.Name, got_data.Name) == 0) {
        printf("%s\n", "TEST COMPARE SUCCESS");
    } else {
        printf("%s\n", "TEST COMPARE FAILED");
    }
}
