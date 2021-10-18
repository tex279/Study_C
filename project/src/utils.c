#include <stdio.h>
#include <struct_and_const.h>


void transaction_write(FILE *ofPtr, Data transfer) {
    printf("%s\n%s\n",
           "1 Number account: ",
           "2 Client cash payments: ");
    while (fscanf(ofPtr, "%i %lf",
                  &transfer.Number,
                  &transfer.cash_payments)!= -1) {
        fseek(ofPtr,  0, 0);
        fprintf(ofPtr, "%-3d%-6.2f\n",
                transfer.Number,
                transfer.cash_payments);
        printf("%s\n%s\n",
               "1 Number account:",
               "2 Client cash payments: ");
    }
}
