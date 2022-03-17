#include <gtest/gtest.h>

extern "C" {
#include "blank.h"
#include "list_blanks.h"
#include "list_parts.h"
#include "utils.h"
}

TEST(TEST_BLANKS, create_list) {
    node_t *first = NULL;

    EXPECT_TRUE(first == NULL);

    node_blank_t *expected = push_front(first, 10);

    EXPECT_FALSE(expected == NULL);

    EXPECT_EQ(expected->number, 10);
    EXPECT_EQ(expected->next, first);
    EXPECT_EQ(expected->prev, NULL);

    EXPECT_EQ(first->prev, expected);

    free(expected);
}
