#include <gtest/gtest.h>

extern "C" {
    #include "../include/list_parts.h"
}

TEST(TEST_BLANKS, create_list) {
    list_blanks *first = NULL;

    EXPECT_TRUE(first == NULL);

    node_blank_t *tmp = push_front(first, 10);

    EXPECT_TRUE(tmp != NULL);

    EXPECT_EQ(tmp->number, 10);

    free(tmp);
}
