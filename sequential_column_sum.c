#include "sequential_column_sum.h"
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>


double* find_column_sum_sequentially(const Matrix* matrix) {
  size_t number_of_columns = 0;
  if (get_cols(matrix, &number_of_columns)) {
    return NULL;
  }
  double *sum_every_column = (double *) malloc(sizeof(double) * number_of_columns);
  if (sum_every_column == NULL) {
    return NULL;
  }

  size_t number_of_rows = 0;
  if (get_rows(matrix, &number_of_rows)) {
    return NULL;
  }
  for (size_t i = 0; i < number_of_rows; ++i) {
    for (size_t j = 0; j < number_of_columns; ++j) {
      sum_every_column[j] += matrix->matrix[i][j];
    }
  }

  return sum_every_column;
}