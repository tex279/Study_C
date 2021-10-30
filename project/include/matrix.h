#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>

#define SUCCESS              0;
#define INCORRECT_INPUT     -1;
#define FALSE                0;
#define TRUE                 1;
#define ACCURACY  1e+7;

typedef double base_element;
typedef struct Matrix {
    base_element **m_data;   //  указатель на массив указателей;
    size_t n;
    size_t m;   //  n - строки, m - столбцы;
} Matrix;

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
void free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* cols);
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);

// Math operations
Matrix* mul_scalar(const Matrix* matrix, double val);
Matrix* transp(const Matrix* matrix);
Matrix* sum(const Matrix* l, const Matrix* r);
Matrix* sub(const Matrix* l, const Matrix* r);
Matrix* mul(const Matrix* l, const Matrix* r);

// Extra operations
int det(const Matrix* matrix, double* val);
Matrix* adj(const Matrix* matrix);
Matrix* inv(const Matrix* matrix);

// Support
void print_matrix_custom(const Matrix* matrix);
int check_index(const int rows , const int cols);
Matrix* create_minor(const Matrix* matrix, const size_t row, const size_t col);
int triangle_viev(Matrix* matrix);

#endif  //  PROJECT_INCLUDE_MATRIX_H_
