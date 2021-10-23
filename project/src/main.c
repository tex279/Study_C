#include <stdio.h>
#include <test_w_to_file.h>
#include <utils_for_file.h>
#include <w_r_file.h>


#define INPUT_DATA           1
#define TRANSACTION_DATA     2
#define UPDATE_CREDIT_LIMIT  3
#define TEST_W_R             4

#define FILENAME_REC     "record.dat"
#define FILENAME_TRAN    "transaction.dat"
#define FILENAME_BLACK   "blackrecord.dat"
#define TARGET_TEST      "TEST.dat"

	int main(void) {
        int choice = 0;
        fprintf(stdout, "%s\n%s\n%s\n%s\n%s\n\n",
                "please enter action",
                "1 enter data client:",
                "2 enter data transaction:",
                "3 update base",
                "4 test compare");
        while (fscanf(stdin, "%d", &choice) != -1) {
            switch (choice) {
                case INPUT_DATA: {
                    Data client_data;
                    write_to_file(FILENAME_REC, &client_data);
                    break;
                }
                case TRANSACTION_DATA: {
                    Data transfer;
                    transaction_write(FILENAME_TRAN, &transfer);
                    break;
                }
                case UPDATE_CREDIT_LIMIT: {
                    Data client_data, transfer;
                    black_record(FILENAME_REC, FILENAME_TRAN, FILENAME_BLACK , &client_data, &transfer);
                    break;
                }
                case TEST_W_R: {
                    test_write_to_file(TARGET_TEST);
                    break;
                }
                default: {
                    fprintf(stdout, "%s\n", "error");
                    break;
                }
            }
            return 0;
        }
    }
