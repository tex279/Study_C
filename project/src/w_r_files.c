#include <stdio.h>
#include <w_r_files.h>


void write_to_file(const char *filename, Some *data) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        puts("exit");
    } else {
        fprintf(fp, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                data->Number,
                data->Name,
                data->Surname,
                data->address,
                data->TelNumber,
                data->indebtedness,
                data->credit_limit,
                data->cash_payments);
        printf("%d %20s %20s %30s %15s %f %f %f\n",
               data->Number,
               data->Name,
               data->Surname,
               data->address,
               data->TelNumber,
               data->indebtedness,
               data->credit_limit,
               data->cash_payments);
        fclose(fp);
    }
}

void read_from_file(const char *filename, Some *data) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        puts("exit");
    } else {
        fscanf(fp, "%d%20s%20s%30s%15s%lf%lf%lf\n",
               &data->Number,
               data->Name,
               data->Surname,
               data->address,
               data->TelNumber,
               &data->indebtedness,
               &data->credit_limit,
               &data->cash_payments);
        printf("%d %20s %20s %30s %15s %f %f %f\n",
               data->Number,
               data->Name,
               data->Surname,
               data->address,
               data->TelNumber,
               data->indebtedness,
               data->credit_limit,
               data->cash_payments);
        fclose(fp);
    }
}
