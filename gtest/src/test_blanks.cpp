#include <gtest/gtest.h>

extern "C" {
    #include "list_parts.h"
    #include "list_blanks.h"
    #include "blank.h"
    #include "utils.h"
}

TEST(TEST_BLANKS, list_functional) {
    char stor[] = {"sto123r"};
    char res[] = {"re123s"};

    list_blanks_t *list = create_list(10, stor, res);
    EXPECT_TRUE(list != NULL);

    EXPECT_TRUE(list->first->number == 10);
    EXPECT_TRUE(list->last->number == 10);

    EXPECT_TRUE(strcmp(list->storage, stor) == 0);
    EXPECT_TRUE(strcmp(list->responsible, res) == 0);

    EXPECT_TRUE(insert(list, 4) != NULL);
    EXPECT_TRUE(list->first->number == 4);
    EXPECT_TRUE(list->last->number == 10);

    EXPECT_TRUE(insert(list, 16) != NULL);
    EXPECT_TRUE(list->first->number == 4);
    EXPECT_TRUE(list->last->number == 16);

    EXPECT_TRUE(free_list_blank(list) == SUCCESS);
}

TEST(TEST_PARTS, parts_functional) {
    char stor_1[] = {"stor"};
    char res_1[] = {"res"};

    node_list_parts_t *first = create_part(10, stor_1, res_1);
    EXPECT_TRUE(first != NULL);

    EXPECT_TRUE(strcmp(first->list_b->storage, stor_1) == 0);
    EXPECT_TRUE(strcmp(first->list_b->responsible, res_1) == 0);

    char stor_2[] = {"stor123"};
    char res_2[] = {"res"};

    EXPECT_TRUE(find_combination(first, stor_2, res_2) == NULL);

    EXPECT_TRUE(find_combination(first, stor_1, res_2) != NULL);

    EXPECT_TRUE(free_list_parts(first) == SUCCESS);
}

TEST(INPUT, input_data_file_file) {
    char path_input[] = {"gtest/data/ok/in.txt"};
    char path_output[] = {"build/tmp.txt"};

    size_t count_error = 0;

    node_list_parts_t* first;
    EXPECT_TRUE(input(path_input, &count_error, &first) == SUCCESS);

    EXPECT_TRUE(first != NULL);

    EXPECT_TRUE(output_parts(path_output, first, &count_error) == SUCCESS);;

    EXPECT_TRUE(free_list_parts(first) == SUCCESS);
}

TEST(INPUT, input_data_std_file) {
    char path_input[] = {"gtest/data/ok/in.txt"};

    size_t count_error = 0;

    node_list_parts_t* first;
    EXPECT_TRUE(input(path_input, &count_error, &first) == 1);

    EXPECT_TRUE(first != NULL);

    EXPECT_TRUE(output_parts(NULL, first, &count_error) == SUCCESS);

    EXPECT_TRUE(free_list_parts(first) == SUCCESS);
}

TEST(INPUT, input_data_incorrect) {
    char path_input[] = {"gtest/data/incorrect_input/in.txt"};
    char path_output[] = {"build/tmp.txt"};

    size_t count_error = 0;

    node_list_parts_t* first;

    EXPECT_TRUE(input(path_input, &count_error, &first) == 1);

    EXPECT_TRUE(first != NULL);

    EXPECT_TRUE(output_parts(path_output, first, &count_error) == SUCCESS);

    EXPECT_TRUE(free_list_parts(first) == SUCCESS);
}
