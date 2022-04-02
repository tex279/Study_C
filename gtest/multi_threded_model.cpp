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

