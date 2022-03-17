#include <gtest/gtest.h>

extern "C" {
    #include "list_parts.h"
}

TEST(TEST_BLANKS, create_list) {
    node_blank_t *first = NULL;

    EXPECT_TRUE(first == NULL);
}
