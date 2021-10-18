#include <stdio.h>
#include <struct_and_const.h>
#include <utils.h>
#include <input_data.h>

#define INPUT_DATA          1
#define TRANSACTION_DATA    2
#define CHECK_CREDIT_LIMIT  3


	int main(void) {
        int choice = 0;
        void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);

        printf("%s",
               "please enter action\n"
               "1 enter data client:\n"
               "2 enter data transaction:\n"
               "3 update base\n");
        while (scanf("%d", &choice) != -1) {
            switch (choice) {
                case INPUT_DATA: {
                    Ptr = fopen(FILENAME_REC, "r+");
                    if (Ptr == NULL) {
                        puts("Not access");
                    } else {
                        masterWrite(Ptr, client_data);
                        fclose(Ptr);
                    }
                    break;
                }
                case TRANSACTION_DATA: {
                    Ptr = fopen(FILENAME_TRAN, "r+");
                    if (Ptr == NULL) {
                        puts("Not access");
                    } else {
                        transaction_write(Ptr, transfer);
                        fclose(Ptr);
                    }
                    break;
                }
                case CHECK_CREDIT_LIMIT: {
                    Ptr = fopen(FILENAME_REC, "r");
                    Ptr_2 = fopen(FILENAME_TRAN, "r");
                    blackrecord = fopen(FILENAME_BLACK, "w");
                    if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL) {
                        puts("exit");
                    } else {
                        blackRecord(Ptr, Ptr_2, blackrecord, client_data, transfer);
                        fclose(Ptr);
                        fclose(Ptr_2);
                        fclose(blackrecord);
                        break;
                    }
                }
                default: {
                    puts("error");
                    break;
                }
            }
            return 0;
        }
    }

       void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer) {
       while (fscanf(ofPTR, "%d%20s%20s%30s%15s%lf%lf%lf",
                     &client_data.Number,
                     client_data.Name,
                     client_data.Surname,
                     client_data.address,
                     client_data.TelNumber,
                     &client_data.indebtedness,
                     &client_data.credit_limit,
                     &client_data.cash_payments) != -1) {
           while (fscanf(ofPTR_2, "%d%lf",
                         &transfer.Number,
                         &transfer.cash_payments) != -1) {
               if (client_data.Number == transfer.Number && transfer.cash_payments != 0) {
                   client_data.credit_limit += transfer.cash_payments;
               }
           }
                   fprintf(blackrecord, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                           client_data.Number,
                           client_data.Name,
                           client_data.Surname,
                           client_data.address,
                           client_data.TelNumber,
                           client_data.indebtedness,
                           client_data.credit_limit,
                           client_data.cash_payments);
                   rewind(ofPTR_2);
       }
    }
