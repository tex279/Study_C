#ifndef  PROJECT_INCLUDE_BASE_STRUCT_H_
#define  PROJECT_INCLUDE_BASE_STRUCT_H_

#define LENGTH_NAME         20
#define LENGTH_SURNAME      20
#define LENGTH_ADDRESS      30
#define LENGTH_TELNUMBER    15

#define SUCCESS 1
#define ERROR_OPEN_FILE -1
#define INCORRECT_INPUT 0

struct master_record {
    int 		number;
    char 		name[LENGTH_NAME];
    char 		surname[LENGTH_SURNAME];
    char 		address[LENGTH_ADDRESS];
    char        tel_number[LENGTH_TELNUMBER];
    double  	indebtedness;
    double    	credit_limit;
    double  	cash_payments;
};

typedef  struct  master_record Data;

#endif  //   PROJECT_INCLUDE_BASE_STRUCT_H_
