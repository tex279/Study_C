#include <utils.h>
#include <stdio.h>


void transaction_write(const char *filename, Data *transfer) {
    FILE *ofPtr;
    ofPtr = fopen(filename, "w+r");
    if (ofPtr == NULL) {
        puts("exit");
    } else {
        printf("%s\n%s\n",
               "1 Number account: ",
               "2 Client cash payments: ");
        while (scanf( "%d%lf",
                      &transfer->Number,
                      &transfer->cash_payments) != -1) {
            //  debug code
            /*printf("%-3d%4.2lf\n",
                    transfer->Number,
                    transfer->cash_payments); */
            fprintf(ofPtr, "%-3d%4.2f\n",
                    transfer->Number,
                    transfer->cash_payments);
            printf("%s\n%s\n",
                   "1 Number account:",
                   "2 Client cash payments: ");
        }
        fclose(ofPtr);
    }
}

void black_record(const char *filename_out_general,
                  const char *filename_out,
                  const char *filename_update,
                  Data *client_data,
                  Data *transfer) {
    FILE *Ptr, *Ptr_2, *blackrecord;
    Ptr = fopen(filename_out_general, "r");
    Ptr_2 = fopen(filename_out, "r");
    blackrecord = fopen(filename_update, "w");
    if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL) {
        puts("exit");
    } else {
        while (fscanf(Ptr, "%d%20s%20s%30s%15s%lf%lf%lf\n",
                      &client_data->Number,
                      client_data->Name,
                      client_data->Surname,
                      client_data->address,
                      client_data->TelNumber,
                      &client_data->indebtedness,
                      &client_data->credit_limit,
                      &client_data->cash_payments) != -1) {
            while (fscanf(Ptr_2, "%d%lf\n",
                          &transfer->Number,
                          &transfer->cash_payments) != -1) {
                if ((client_data->Number == transfer->Number) != 0) {
                    client_data->credit_limit += transfer->cash_payments;
                    fprintf(blackrecord, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                            client_data->Number,
                            client_data->Name,
                            client_data->Surname,
                            client_data->address,
                            client_data->TelNumber,
                            client_data->indebtedness,
                            client_data->credit_limit,
                            client_data->cash_payments);
                }
            }
            rewind(Ptr_2);
        }
        fclose(Ptr);
        fclose(Ptr_2);
        fclose(blackrecord);
    }
}


