#include "parallel_column_sum.h"

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include "matrix.h"

// делю кол-во рядов на кол-во процессов, таким образом нахожу границы left и right,
// чтобы каждый процессор искал сумму столбцов в нужных ему границах
int sum_one_column(const Matrix *matrix, long left_column, long right_column,
                   size_t number_of_rows, double *shared_memory) {
  if (matrix == NULL || !shared_memory) {
    return EXIT_FAILURE;
  }

  for (long j = left_column; j < right_column; ++j) {
    for (size_t i = 0; i < number_of_rows; ++i) {
      shared_memory[j] += matrix->matrix[i][j];
    }
  }

  return EXIT_SUCCESS;
}

double *find_column_sum_parallel(const Matrix *matrix) {
  size_t number_of_columns = 0;
  if (get_cols(matrix, &number_of_columns)) {
    return NULL;
  }

  double *sum_every_column =
      (double *)malloc(sizeof(double) * number_of_columns);
  if (sum_every_column == NULL) {
    return NULL;
  }

  double *shared_memory = (double *)mmap(
      NULL, sizeof(double) * number_of_columns, PROT_READ | PROT_WRITE,
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);  // анонимус - значит нет файла
  if (!shared_memory) {
    free(sum_every_column);
    return NULL;
  }

  for (size_t i = 0; i < number_of_columns; ++i) {
    sum_every_column[i] = 0;
    shared_memory[i] = 0;
  }

  size_t number_of_rows = 0;
  if (get_rows(matrix, &number_of_rows)) {
    munmap(shared_memory, sizeof(double) * number_of_columns);
    free(sum_every_column);
    return NULL;
  }

  long number_of_proc = sysconf(_SC_NPROCESSORS_ONLN);

  for (long i = 0; i < number_of_proc; ++i) {
    pid_t pid = fork();

    if (pid == -1) {
      munmap(shared_memory, sizeof(double) * number_of_columns);
      free(sum_every_column);
      return NULL;
    }

    if (pid == 0) {
      long left = i * (number_of_columns / number_of_proc);
      long right = 0;
      if (i == number_of_proc - 1) {
        right = number_of_columns;
      } else {
        right = left + (number_of_columns / number_of_proc);
      }

      if (sum_one_column(matrix, left, right, number_of_rows, shared_memory)) {
        munmap(shared_memory, sizeof(double) * number_of_columns);
        free(sum_every_column);
        return NULL;
      }

      exit(EXIT_SUCCESS);
    }
  }

  int status = 0;
  for (long i = 0; i < number_of_proc; ++i) {
    wait(&status);

    if (!WIFEXITED(status)) {
      munmap(shared_memory, sizeof(double) * number_of_columns);
      free(sum_every_column);
      return NULL;
    }
  }

  for (size_t i = 0; i < number_of_columns; ++i) {
    sum_every_column[i] = shared_memory[i];
  }

  if (munmap(shared_memory, sizeof(double) * number_of_columns)) {
    free(sum_every_column);
    return NULL;
  }

  return sum_every_column;
}
