#include <stdio.h>
#include <input.h>

void master_write(const char *filename, Data *Client) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
    puts("exit");
    } else {
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
               "1 Number account: ",
               "2 Client name: ",
               "3 Surname: ",
               "4 Address client: ",
               "5 Client Telnum: ",
               "6 Client indebtedness: ",
               "7 Client credit limit: ",
               "8 Client cash payments: ");
        while (scanf("%d%20s%20s%30s%15s%lf%lf%lf",
                     &Client->Number,
                     Client->Name,
                     Client->Surname,
                     Client->address,
                     Client->TelNumber,
                     &Client->indebtedness,
                     &Client->credit_limit,
                     &Client->cash_payments) != -1) {
            fprintf(fp, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                    Client->Number,
                    Client->Name,
                    Client->Surname,
                    Client->address,
                    Client->TelNumber,
                    Client->indebtedness,
                    Client->credit_limit,
                    Client->cash_payments);
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
        fclose(fp);
    }
}
