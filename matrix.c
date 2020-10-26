#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

Matrix* create_matrix_from_file(const char* path_file) {
  FILE* fp;

  fp = fopen(path_file, "r+");

  if (fp == NULL) {
    return NULL;
  }

  Matrix* my_matrix = (Matrix*)malloc(sizeof(Matrix));
  if (my_matrix == NULL) {
    return NULL;
  }

  if (!fscanf(fp, "%zu", &my_matrix->num_rows)) {
    return NULL;
  }

  if (!fscanf(fp, "%zu", &my_matrix->num_cols)) {
    return NULL;
  }

  my_matrix->matrix = (double**)malloc(my_matrix->num_rows * sizeof(double*));
  if (my_matrix->matrix == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < my_matrix->num_rows; ++i) {
    my_matrix->matrix[i] = (double*)malloc(my_matrix->num_cols * sizeof(double));

    if (my_matrix->matrix[i] == NULL) {
      return NULL;
    }
  }

  for (size_t i = 0; i < my_matrix->num_rows; ++i) {
    for (size_t j = 0; j < my_matrix->num_cols; ++j) {
      if (!fscanf(fp, "%lf", &my_matrix->matrix[i][j])) {
        return NULL;
      }
    }
  }

  if (fclose(fp)) {
    return NULL;
  }
  return my_matrix;
}

Matrix* create_matrix(size_t rows, size_t cols) {
  if (rows == 0 || cols == 0) {
    return NULL;
  }

  Matrix* my_matrix = (Matrix*)malloc(sizeof(Matrix));
  if (my_matrix == NULL) {
    return NULL;
  }

  my_matrix->num_rows = rows;
  my_matrix->num_cols = cols;

  my_matrix->matrix = (double**)malloc(rows * sizeof(double*));
  if (my_matrix->matrix == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < rows; ++i) {
    my_matrix->matrix[i] = (double*)malloc(cols * sizeof(double));

    if (my_matrix->matrix[i] == NULL) {
      return NULL;
    }
  }

  return my_matrix;
}

int get_rows(const Matrix* matrix, size_t* rows) {
  if (matrix == NULL || rows == NULL) {
    return EXIT_FAILURE;
  }

  *rows = matrix->num_rows;
  return EXIT_SUCCESS;
}

int get_cols(const Matrix* matrix, size_t* cols) {
  if (matrix == NULL || cols == NULL) {
    return EXIT_FAILURE;
  }

  *cols = matrix->num_cols;
  return EXIT_SUCCESS;
}

int free_matrix(Matrix* matrix) {
  if (matrix == NULL) {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < matrix->num_rows; ++i) {
    free(matrix->matrix[i]);
  }
  free(matrix->matrix);
  free(matrix);
  return EXIT_SUCCESS;
}
