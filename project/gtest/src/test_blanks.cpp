#include <gtest/gtest.h>

extern "C" {
    #include "../include/list_parts.h"
    #include "../include/list_blanks.h"
    #include "../include/blank.h"
    #include "../include/utils.h"
}

TEST(TEST_BLANKS, list_functional) {
    char storr[] = {"stor"};
    char ress[] = {"res"};


    char *stor = create_str(storr);
    char *res = create_str(ress);

    list_blanks_t *list = create_list(10, stor, res);
    EXPECT_TRUE(list != NULL);

    EXPECT_TRUE(list->first->number == 10);
    EXPECT_TRUE(list->last->number == 10);
    EXPECT_EQ(list->storage, stor);
    EXPECT_EQ(list->responsible, res);

    EXPECT_TRUE(insert(list, 4) != NULL);
    EXPECT_TRUE(list->first->number == 4);
    EXPECT_TRUE(list->last->number == 10);

    EXPECT_TRUE(insert(list, 16) != NULL);
    EXPECT_TRUE(list->first->number == 4);
    EXPECT_TRUE(list->last->number == 16);

    free_list_blank(list);
}

TEST(TEST_PARTS, parts_functional) {
    char stor_1[] = {"stor"};
    char res_1[] = {"res"};

    char *stor__1 = create_str(stor_1);
    char *res__1 = create_str(res_1);

    node_list_parts_t *first = create_part(10, stor__1, res__1);
    EXPECT_TRUE(first != NULL);

    EXPECT_EQ(first->list_b->storage, stor__1);
    EXPECT_EQ(first->list_b->responsible, res__1);

    char stor_2[] = {"stor123"};
    char res_2[] = {"res"};

    char *stor__2 = create_str(stor_2);
    char *res__2 = create_str(res_2);

    EXPECT_TRUE(find_combination(first, stor__2, res__2) == NULL);

    node_list_parts_t *tmp = find_combination(first, stor_1, res_2);
    EXPECT_TRUE(tmp != NULL);

    free(stor__2);
    free(res__2);

    free_list_parts(first);
}

TEST(INPUT, input_data) {
    char path[] = {"../project/gtest/data/ok/in.txt"};
    size_t count_error = 0;

    node_list_parts_t* first = input(path, &count_error);

    EXPECT_TRUE(first != NULL);

    free_list_parts(first);
}
