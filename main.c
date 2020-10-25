#include <stdio.h>

#include "matrix.h"

int main(void) {
  Matrix *test = create_matrix_from_file("test.txt");

  size_t test_rows = 0;
  get_rows(test, &test_rows);
  printf("Our number of rows: %zu\n", test_rows);

  size_t test_cols = 0;
  get_cols(test, &test_cols);
  printf("Our number of cols: %zu\n", test_cols);

  puts("Our matrix:");
  for (size_t i = 0; i < test_rows; ++i) {
    for (size_t j = 0; j < test_cols; ++j) {
      printf("%lf ", test->matrix[i][j]);
    }
    printf("\n");
  }

  double val = -1;
  get_elem(test, 1, 1, &val);
  printf("Our value at 1,1: %lf\n", val);

  free_matrix(test);
  return 0;
}
