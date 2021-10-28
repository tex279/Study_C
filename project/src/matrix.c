#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <matrix.h>

int check_index(const int rows , const int cols) {
    if (rows < 1 || cols < 1) {
        fprintf(stdout, "incorrect input, indices must be greater than zero\n");
        return SUCCESS;
    }
    return NO_INTERSECTION;
}

void print_matrix_my(const Matrix* matrix) {
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            fprintf(stdout, "%f ", matrix->m_data[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

Matrix* create_matrix(size_t rows, size_t cols) {
    if (check_index(rows , cols)) {return NULL;}
    Matrix *matrix = (Matrix*)calloc(1, sizeof(Matrix));
    if (!matrix) {return NULL;}
    matrix->m_data = calloc(rows, sizeof(base_element*));
    if (!matrix->m_data) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->m_data[i] = calloc(cols, sizeof(base_element));
        if (!matrix->m_data[i]) {
            free_matrix(matrix);
            return NULL;
        }
    }
    matrix->n = rows;
    matrix->m = cols;
    return matrix;
}

void free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->n; i++) {
        free(matrix->m_data[i]);
    }
    free(matrix->m_data);
    free(matrix);
}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE* source = fopen(path_file, "r");
    if (!source) {
        fprintf(stdout, "impossible open file in your path\n");
        return NULL;
    }
    size_t rows = 0;
    size_t cols = 0;
    if (fscanf(source, "%zu%zu", &rows, &cols) != 2) {
        fclose(source);
        fprintf(stdout, "incorrect input, there should be 2 values type - double\n");
        return NULL;
    }
    if (check_index(rows , cols)) {
        fclose(source);
        return NULL;
    }
    Matrix *matrix = create_matrix(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (fscanf(source, "%lf", &(matrix->m_data[i][j])) != 1) {
                fclose(source);
                free_matrix(matrix);
                fprintf(stdout, "incorrect input, there should be 1 values type - double\n");
                return NULL;
            }
        }
    }
    fclose(source);
    return matrix;
}

int get_rows(const Matrix* matrix, size_t* rows) {
    if (!matrix || !rows) {
        return INCORRECT_INPUT;
    }
    if (check_index(matrix->n, matrix->m)) {return INCORRECT_INPUT;}
    *rows = matrix->n;
    return SUCCESS;
}
int get_cols(const Matrix* matrix, size_t* cols) {
    if (check_index(matrix->n, matrix->m)) {return INCORRECT_INPUT;}
    *cols = matrix->m;
    return SUCCESS;
}
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (check_index(row, col)) {return INCORRECT_INPUT;}
    if (row > matrix->n || col > matrix->m) {return INCORRECT_INPUT;}
    *val = matrix->m_data[row][col];
    return SUCCESS;
}
int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (check_index(row , col)) {return INCORRECT_INPUT;}
    if (row > matrix->n || col > matrix->m) {return INCORRECT_INPUT;}
    matrix->m_data[row][col] = val;
    return SUCCESS;
}

Matrix* mul_scalar(const Matrix* matrix, double val) {
    Matrix *matrix_mul = create_matrix(matrix->n, matrix->m);
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            matrix_mul->m_data[i][j] = val*matrix->m_data[i][j];
        }
    }
    return matrix_mul;
}

Matrix* transp(const Matrix* matrix) {
    Matrix *matrix_tran = create_matrix(matrix->m, matrix->n);
    for (size_t i = 0; i < matrix->m; i++) {
        for (size_t j = 0; j < matrix->n; j++) {
            matrix_tran->m_data[i][j] = matrix->m_data[j][i];
        }
    }
    return matrix_tran;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (!(l->m == r->n)) {
        fprintf(stdout, "these matrices cannot be multiplied\n");
        return NULL;
    }
    Matrix *matrix = create_matrix(l->n, l->m);
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            matrix->m_data[i][j] = l->m_data[i][j] + r->m_data[i][j];
        }
    }
    return matrix;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    Matrix *matrix = create_matrix(l->n, l->m);
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            matrix->m_data[i][j] = l->m_data[i][j] - r->m_data[i][j];
        }
    }
    return matrix;
}

double mul_element(const Matrix* l, const Matrix* r, const size_t row, const size_t col) {
    double res = 0;
    size_t num_iter = l->m;
    for (size_t pos = 1; pos < num_iter; pos++) {
        res = res + r->m_data[row][pos] * r->m_data[pos][col];
    }
    return res;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    Matrix *matrix = create_matrix(l->n, r->m);
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            matrix->m_data[i][j] = mul_element(l, r, i, j);
        }
    }
    return matrix;
}

Matrix* create_minor(const Matrix* matrix, const size_t row, const size_t col) {
    Matrix *minor = create_matrix(matrix->n-1, matrix->m-1);
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            if (i != row || j != col) {
                minor->m_data[i][j] = matrix->m_data[i][j];
            }
        }
    }
    return minor;
}

int clear_col_down(Matrix* matrix, const size_t start) {
    if (start < 2) {
        fprintf(stdout, "incorrect input, first row is const\n");
        return INCORRECT_INPUT;
    }
    for (size_t i = start; i < matrix->n; i++) {
        int mull = matrix->m_data[i][1] / matrix->m_data[i-1][1];
        for (size_t j = start-1; j < matrix->m; j++) {
            matrix->m_data[i][j] = matrix->m_data[i][j] - mull * matrix->m_data[i-1][j];
            mull = 0;
        }
    }
    return SUCCESS;
}

int matrix_to_gaus(Matrix* matrix) {
    for (size_t i = 2; i < matrix->n; i++) {
        clear_col_down(matrix, i);
    }
    return SUCCESS;
}

int det(const Matrix* matrix, double* val) {
    *val = 1;
    Matrix *matrix_res = create_matrix(matrix->n, matrix->m);
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            matrix_res->m_data[i][j] = matrix->m_data[i][j];
        }
    }
    matrix_to_gaus(matrix_res);
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            *val = *val * matrix_res->m_data[i][j];
        }
    }
    free_matrix(matrix_res);
    return SUCCESS;
}

Matrix* adj(const Matrix* matrix) {
    Matrix *matrix_out = create_matrix(matrix->n, matrix->m);
    for (size_t i = 0; i < matrix->n; i++) {
        for (size_t j = 0; j < matrix->m; j++) {
            double val = 0;
            det(create_minor(matrix, i, j), &val);
            matrix_out->m_data[i][j] = pow(-1, (i+j)) * val;
        }
    }
    return matrix_out;
}

Matrix* inv(const Matrix* matrix) {
    double val = 0;
    det(matrix, &val);
    Matrix *adt_to_matrix = transp(adj(matrix));
    Matrix *matrix_inv = mul_scalar((adt_to_matrix), 1/val);
    free_matrix(adt_to_matrix);
    return matrix_inv;
}

