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
               "3 update base\n");
        while (scanf("%d", &choice) != -1) {
            switch (choice) {
                case INPUT_DATA: {
                    FILE *Ptr;
                    Ptr = fopen(FILENAME_REC, "r+");
                    if (Ptr == NULL) {
                        puts("Not access");
                    } else {
                        master_write(Ptr, &client_data);
                        fclose(Ptr);
                    }
                    break;
                }
                case TRANSACTION_DATA: {
                    FILE *Ptr;
                    Ptr = fopen(FILENAME_TRAN, "r+");
                    if (Ptr == NULL) {
                        puts("Not access");
                    } else {
                        transaction_write(Ptr, &transfer);
                        fclose(Ptr);
                    }
                    break;
                }
                case UPDATE_CREDIT_LIMIT: {
                    FILE *Ptr, *Ptr_2, *blackrecord;
                    Ptr = fopen(FILENAME_REC, "r");
                    Ptr_2 = fopen(FILENAME_TRAN, "r");
                    blackrecord = fopen(FILENAME_BLACK, "w");
                    if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL) {
                        puts("exit");
                        break;
                    } else {
                        black_record(Ptr, Ptr_2, blackrecord, &client_data, &transfer);
                        fclose(Ptr);
                        fclose(Ptr_2);
                        fclose(blackrecord);
                        break;
                    }
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
