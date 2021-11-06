#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>
#include <stdbool.h>

#define SUCCESS              0
#define INCORRECT_INPUT     -1
#define ERR_ALLOCATION      -1

typedef double base_element;
typedef struct Matrix {
    base_element **m_data;   //  указатель на массив указателей;
    size_t m_rows;           //   - строки,
    size_t m_cols;           //   - столбцы;
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

// Support check
int check_index(const int rows , const int cols);
int check_ptr_matrix(const Matrix* matrix);

// Support
int step_viev(Matrix* matrix);
Matrix* create_minor(const Matrix* matrix, const size_t row, const size_t col);

//  Support step viev foo
int check_null_row(const Matrix* matrix, const size_t row);
int check_null_col(const Matrix* matrix, const size_t col);
int check_null_diag_el(Matrix* matrix, const size_t pos);
int plus_col(Matrix* matrix, const size_t target, const size_t sourse);

#endif  //  PROJECT_INCLUDE_MATRIX_H_
