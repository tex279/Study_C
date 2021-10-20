#include <stdio.h>
#include <test_compare.h>
#include <input.h>
#include <utils.h>

#define INPUT_DATA           1
#define TRANSACTION_DATA     2
#define UPDATE_CREDIT_LIMIT  3
#define TEST_W_R             4

#define FILENAME_REC     "record.dat"
#define FILENAME_TRAN    "transaction.dat"
#define FILENAME_BLACK   "blackrecord.dat"

Data client_data, transfer;

	int main(void) {
        int choice = 0;
        printf("%s",
               "please enter action\n"
               "1 enter data client:\n"
               "2 enter data transaction:\n"
               "3 update base\n"
               "4 test compare\n");
        while (scanf("%d", &choice) != -1) {
            switch (choice) {
                case INPUT_DATA: {
                    master_write(FILENAME_REC , &client_data);
                    break;
                }
                case TRANSACTION_DATA: {
                    transaction_write(FILENAME_TRAN, &transfer);
                    break;
                }
                case UPDATE_CREDIT_LIMIT: {
                    black_record(FILENAME_REC, FILENAME_TRAN, FILENAME_BLACK , &client_data, &transfer);
                    break;
                }
                case TEST_W_R: {
                    test_write_to_file();
                    break;
                }
                default: {
                    puts("error");
                    break;
                }
            }
            return 0;
        }
    }
