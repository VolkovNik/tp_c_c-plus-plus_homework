#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "matrix.h"
#include "parallel_column_sum.h"
#include "sequential_column_sum.h"

int main(void) {
  Matrix *test = create_matrix_from_file("../tests/test1.txt");

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

  double *check_sum = find_column_sum_sequentially(test);
  if (check_sum == NULL) {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < test_cols; ++i) {
    printf("%lf ", check_sum[i]);
  }
  puts("\n");

  free(check_sum);

  long number_of_proc = 0;
  number_of_proc = sysconf(_SC_NPROCESSORS_ONLN);
  printf("number of proc: %ld", number_of_proc);
  puts("\n");

  check_sum = find_column_sum_parallel(test);
  for (size_t i = 0; i < test_cols; ++i) {
    printf("%lf ", check_sum[i]);
  }
  puts("\n");

  free_matrix(test);
  free(check_sum);
  return 0;
}
