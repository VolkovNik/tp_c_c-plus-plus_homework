#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

Matrix* create_matrix_from_file(const char* path_file) {
  FILE* fp;

  fp = fopen(path_file, "r+");

  if (fp == NULL) {
    printf("%s\n", "Can't open file");
    return NULL;
  }

  Matrix* my_matrix = (Matrix*)malloc(sizeof(Matrix));

  fscanf(fp, "%zu", &my_matrix->num_rows);
  fscanf(fp, "%zu", &my_matrix->num_cols);

  my_matrix->matrix = (double**)malloc(my_matrix->num_rows * sizeof(double*));
  for (size_t i = 0; i < my_matrix->num_rows; ++i) {
    my_matrix->matrix[i] = (double*)malloc(my_matrix->num_cols * sizeof(double));
  }

  for (size_t i = 0; i < my_matrix->num_rows; ++i) {
    for (size_t j = 0; j < my_matrix->num_cols; ++j) {
      fscanf(fp, "%lf", &my_matrix->matrix[i][j]);
    }
  }

  fclose(fp);
  return my_matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    puts("Wrong number of rows or cols");
    return NULL;
  }

  Matrix* my_matrix = (Matrix*)malloc(sizeof(Matrix));

  my_matrix->num_rows = rows;
  my_matrix->num_cols = cols;

  my_matrix->matrix = (double**)malloc(rows * sizeof(double*));
  for (size_t i = 0; i < rows; ++i) {
    my_matrix->matrix[i] = (double*)malloc(cols * sizeof(double));
  }

  return my_matrix;
}

int get_rows(const Matrix* matrix, size_t* rows) {
  if (matrix == NULL || rows == NULL) {
    puts("Error");
    return EXIT_FAILURE;
  }

  *rows = matrix->num_rows;
  return EXIT_SUCCESS;
}

int get_cols(const Matrix* matrix, size_t* cols) {
  if (matrix == NULL || cols == NULL) {
    puts("Error");
    return EXIT_FAILURE;
  }

  *cols = matrix->num_cols;
  return EXIT_SUCCESS;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
  if (matrix == NULL || val == NULL) {
    puts("Error");
    return EXIT_FAILURE;
  }
  if (row >= matrix->num_rows || col >= matrix->num_cols) {
    puts("Wrong number of row or col");
    return EXIT_FAILURE;
  }

  *val = matrix->matrix[row][col];
  return EXIT_SUCCESS;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
  if (matrix == NULL) {
    puts("Error");
    return EXIT_FAILURE;
  }

  if (row >= matrix->num_rows || col >= matrix->num_cols) {
    puts("Wrong number of row or col");
    return EXIT_FAILURE;
  }

  matrix->matrix[row][col] = val;
  return EXIT_SUCCESS;
}

int free_matrix(Matrix* matrix) {
  if (matrix == NULL) {
    puts("Error");
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < matrix->num_rows; ++i) {
    free(matrix->matrix[i]);
  }
  free(matrix->matrix);
  free(matrix);
  return EXIT_SUCCESS;
}