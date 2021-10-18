#ifndef PROJECT_INCLUDE_STRUCT_AND_CONST_H_
#define PROJECT_INCLUDE_STRUCT_AND_CONST_H_

#include <stdio.h>

#define FILENAME_REC "record.dat"
#define FILENAME_TRAN "transaction.dat"
#define FILENAME_BLACK "blackrecord.dat"

struct masterRecord {
    int 		Number;
    char 		Name[20];
    char 		Surname[20];
    char 		address[30];
    char        TelNumber[15];
    double  	indebtedness;
    double    	credit_limit;
    double  	cash_payments; };

typedef  struct  masterRecord Data;

FILE *Ptr, *Ptr_2, *blackrecord;
Data client_data, transfer;

#endif  //  PROJECT_INCLUDE_STRUCT_AND_CONST_H_
