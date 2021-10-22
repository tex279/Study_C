#include <stdio.h>
#include <std_in_out.h>


int scan_data(FILE *filename, Data *data) {
    if (fscanf(filename, "%d%20s%20s%30s%15s%lf%lf%lf",
               &data->Number,
               data->Name,
               data->Surname,
               data->Address,
               data->TelNumber,
               &data->Indebtedness,
               &data->Credit_limit,
               &data->Cash_payments) != -1) {
        return 1;
    } else {
        return 0;
    }
}


void print_data(FILE *filename, Data *data) {
    fprintf(filename, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
            data->Number,
            data->Name,
            data->Surname,
            data->Address,
            data->TelNumber,
            data->Indebtedness,
            data->Credit_limit,
            data->Cash_payments);
}


int input(Data *data) {
    fprintf(stdout, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
            "1 Number account: ",
            "2 Client name: ",
            "3 Surname: ",
            "4 Address client: ",
            "5 Client Telnum: ",
            "6 Client indebtedness: ",
            "7 Client credit limit: ",
            "8 Client cash payments: ");
    if (scan_data(stdin, data)) {
        return 1;
    } else {
        return 0;
    }
}

/* void output(Data *data) {
    fprintf(stdout, "%d %20s %20s %30s %15s %f %f %f\n",
           data->Number,
           data->Name,
           data->Surname,
           data->Address,
           data->TelNumber,
           data->Indebtedness,
           data->Credit_limit,
           data->Cash_payments);
} */

