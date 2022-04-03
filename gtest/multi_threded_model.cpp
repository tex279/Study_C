#include <gtest/gtest.h>

extern "C" {
    #include "database_functional_multu_thread.h"
}

TEST(TEST_MULTI_BUSNESS_LOGIC, functional) {
    char path_to_database[] = {"sorted_database.txt"};

    database_t *db = create_database();

    load_database(path_to_database, db);

    EXPECT_TRUE(get_average_salary_report_ml(db) > 0);

    free_database(db);
}

