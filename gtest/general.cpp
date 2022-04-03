#include <gtest/gtest.h>

extern "C" {
    #include "load_database.h"
}

TEST(TEST_FORMAT_RECORD, functional) {
    format_t *format = create_set_format();

    EXPECT_TRUE(format != NULL);

    EXPECT_TRUE(free_set_format(format) == SUCCESS);
}

TEST(TEST_RECORD, functional) {
    char record_1[] = {"Holly Mishystina female 81 337393 Teacher 44"};
    char record_2[] = {"Earl Zelenkov male 98 16293 Sailor 60"};

    char surname_1[] = {"Mishystina"};
    char surname_2[] = {"Zelenkov"};

    size_t exp_1 = 44;
    size_t exp_2 = 60;

    format_t *format = create_set_format();

    record_t *tmp_1 = (record_t*)calloc(1, sizeof(record_t));
    record_t *tmp_2 = (record_t*)calloc(1, sizeof(record_t));

    EXPECT_TRUE(get_record(record_1, tmp_1, format) > 0);
    EXPECT_TRUE(strcmp(surname_1, tmp_1->surname) == 0);
    EXPECT_TRUE(exp_1 == tmp_1->experience);

    EXPECT_TRUE(get_record(record_2, tmp_2, format) > 0);
    EXPECT_TRUE(strcmp(surname_2, tmp_2->surname) == 0);
    EXPECT_TRUE(exp_2 == tmp_2->experience);

    EXPECT_TRUE(free_record(tmp_1) == SUCCESS);
    EXPECT_TRUE(free_record(tmp_2) == SUCCESS);

    record_t **tmp_set = create_set_record(3);

    EXPECT_TRUE(tmp_set != NULL);

    EXPECT_TRUE(free_set_record(tmp_set, 3) == SUCCESS);

    free_set_format(format);
}

TEST(TEST_DATABASE, functional) {
    char path_to_database[] = {"generated_database.txt"};
    char path_output_sorted_db[] = {"sorted_database.txt"};

    database_t *db = create_database();
    EXPECT_TRUE(db != NULL);

    EXPECT_TRUE(load_database(path_to_database, db) > 0);

    sort_quick_recursive(db->set_records, db->number_records, position_rule_less);

    EXPECT_TRUE(print_set_record(path_output_sorted_db, db) == SUCCESS);

    EXPECT_TRUE(free_database(db) == SUCCESS);
}
