#ifndef TP_C_CPP_HOMEWORK_MATRIX_H_
#define TP_C_CPP_HOMEWORK_MATRIX_H_

#include <stddef.h>


typedef struct Matrix {
  size_t num_rows;
  size_t num_cols;
  double** matrix;
} Matrix;

// Init/release operations
Matrix* create_matrix_from_file(const char* path_file);
Matrix* create_matrix(size_t rows, size_t cols);
int free_matrix(Matrix* matrix);

// Basic operations
int get_rows(const Matrix* matrix, size_t* rows);
int get_cols(const Matrix* matrix, size_t* cols);
int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);


#endif  // TP_C_CPP_HOMEWORK__MATRIX_H_
