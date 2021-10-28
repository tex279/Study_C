#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>

#define SUCCESS              1;
#define INCORRECT_INPUT     -1;
#define NO_INTERSECTION      0;

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
int check_index(const int rows , const int cols);
double mul_element(const Matrix* l, const Matrix* r, const size_t row, const size_t col);
Matrix* create_minor(const Matrix* matrix, const size_t row, const size_t col);

#endif  //  PROJECT_INCLUDE_MATRIX_H_
