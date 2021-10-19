#include <stdio.h>
#include <test_compare.h>

#define INPUT_DATA           1
#define TRANSACTION_DATA     2
#define UPDATE_CREDIT_LIMIT  3
#define TEST_W_R             4

#define FILENAME_REC     "record.dat"
#define FILENAME_TRAN    "transaction.dat"
#define FILENAME_BLACK   "blackrecord.dat"

struct masterRecord {
    int 		Number;
    char 		Name[20];
    char 		Surname[20];
    char 		address[30];
    char        TelNumber[15];
    double  	indebtedness;
    double    	credit_limit;
    double  	cash_payments;
};

typedef  struct  masterRecord Data;

Data client_data, transfer;

void transaction_write(FILE *ofPtr, Data transfer);
void black_record(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);
void master_write(FILE *ofPTR, Data Client);


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
                        master_write(Ptr, client_data);
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
                        transaction_write(Ptr, transfer);
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
                        black_record(Ptr, Ptr_2, blackrecord, client_data, transfer);
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



// It should be in another module
void transaction_write(FILE *ofPtr, Data transfer) {
    printf("%s\n%s\n",
           "1 Number account: ",
           "2 Client cash payments: ");
    while (fscanf(ofPtr, "%i %lf",
                  &transfer.Number,
                  &transfer.cash_payments)!= -1) {
        fseek(ofPtr, 0, SEEK_END);
        fprintf(ofPtr, "%-3d%-6.2f\n",
                transfer.Number,
                transfer.cash_payments);
        printf("%s\n%s\n",
               "1 Number account:",
               "2 Client cash payments: ");
    }
}

void black_record(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer) {
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

void master_write(FILE *ofPTR, Data Client) {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
           "1 Number account: ",
           "2 Client name: ",
           "3 Surname: ",
           "4 Address client: ",
           "5 Client Telnum: ",
           "6 Client indebtedness: ",
           "7 Client credit limit: ",
           "8 Client cash payments: ");
    while (scanf ("%d%20s%20s%30s%15s%lf%lf%lf",
                  &Client.Number,
                  Client.Name,
                  Client.Surname,
                  Client.address,
                  Client.TelNumber,
                  &Client.indebtedness,
                  &Client.credit_limit ,
                  &Client.cash_payments)!= -1) {
        fprintf(ofPTR, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                Client.Number,
                Client.Name,
                Client.Surname,
                Client.address,
                Client.TelNumber,
                Client.indebtedness,
                Client.credit_limit,
                Client.cash_payments);
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
               "1 Number account: ",
               "2 Client name: ",
               "3 Surname: ",
               "4 Address client: ",
               "5 Client Telnum: ",
               "6 Client indebtedness: ",
               "7 Client credit limit: ",
               "9 Client cash payments:");
    }
}
