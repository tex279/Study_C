#include <gtest/gtest.h>

extern "C" {
    #include "../include/list_parts.h"
    #include "../include/list_blanks.h"
    #include "../include/blank.h"
}

TEST(TEST_BLANKS, create_list) {
    char stor[] = {"stor"};
    char res[] = {"ZINA"};

    list_blanks_t *list = create_list(10, stor, res);

    EXPECT_TRUE(list != NULL);

    EXPECT_TRUE(list->first->number == 10);
    EXPECT_TRUE(list->last->number == 10);

    EXPECT_EQ(list->storage, stor);
    EXPECT_EQ(list->responsible, res);
}
