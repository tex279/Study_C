#include <gtest/gtest.h>

extern "C" {
    #include "load_database.h"
    #include "database_functional.h"
}

TEST(TEST_IMPERATIVE_BUSNESS_LOGIC, functional) {
    char path_to_database[] = {"generated_database.txt"};
    char path_to_report[] = {"report.txt"};

    database_t *db = create_database();

    load_database(path_to_database, db);

    sort_set_record(db->set_records, db->number_records, position_rule_less);

    EXPECT_TRUE(get_average_salary_report(path_to_report, db) > 0);

    free_database(db);
}

