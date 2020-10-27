#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "matrix.h"
#include "parallel_column_sum.h"
#include "sequential_column_sum.h"

#define NMB_OF_COLS_FOR_STRESS_TEST 50
#define NMB_OF_ROWS_FOR_STRESS_TEST 100
#define NMB_OF_COLS_FOR_TIME_TEST 5000
#define NMB_OF_ROWS_FOR_TIME_TEST 10000
#define TEN_IN_THIRD_DEGREE 1000

void fill_random(Matrix *matrix, size_t nmb_of_rows, size_t nmb_of_cols) {
  for (size_t i = 0; i < nmb_of_rows; ++i) {
    for (size_t j = 0; j < nmb_of_cols; ++j) {
      matrix->matrix[i][j] = rand();
    }
  }
}

long get_time_of_work(struct timeval start_time, struct timeval end_time) {
  return (end_time.tv_sec - start_time.tv_sec) * TEN_IN_THIRD_DEGREE
    + (end_time.tv_usec - start_time.tv_usec) / TEN_IN_THIRD_DEGREE;
}

int main(void) {
  printf("Проверим работу алгоритмов, заполнив матрицу случайными числами\n");
  Matrix *matrix = create_matrix(NMB_OF_ROWS_FOR_STRESS_TEST, NMB_OF_COLS_FOR_STRESS_TEST);
  if (matrix == NULL) {
    return EXIT_FAILURE;
  }

  fill_random(matrix, NMB_OF_ROWS_FOR_STRESS_TEST, NMB_OF_COLS_FOR_STRESS_TEST);

  printf("Наша матрица, заполненная рандомными числами: \n");
  for (size_t i = 0; i < NMB_OF_COLS_FOR_STRESS_TEST; ++i) {
    for (size_t j = 0; j < NMB_OF_ROWS_FOR_STRESS_TEST; ++j) {
      printf("%f ", matrix->matrix[i][j]);
    }
    printf("\n");
  }

  double* sum_of_cols_get_from_parallel =
      find_column_sum_parallel(matrix);
  if (sum_of_cols_get_from_parallel == NULL) {
    return EXIT_FAILURE;
  }

  double* sum_of_cols_get_from_sequential =
      find_column_sum_sequentially(matrix);
  if (sum_of_cols_get_from_sequential == NULL) {
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < NMB_OF_COLS_FOR_STRESS_TEST; ++i) {
    if(sum_of_cols_get_from_parallel[i] != sum_of_cols_get_from_sequential[i]) {
      printf("Ошибка %f != %f\n", sum_of_cols_get_from_parallel[i], sum_of_cols_get_from_sequential[i]);
      return EXIT_FAILURE;
    }
  }

  printf("Алгортимы работают верно! Сумма каждого столбцы равны \n");

  for (size_t i = 0; i < NMB_OF_COLS_FOR_STRESS_TEST; ++i) {
      printf("%f ", sum_of_cols_get_from_parallel[i]);

  }

  printf("Измерим время работы последовательного и параллельного алгоритмов \n");

  Matrix *matrix_for_time = create_matrix(NMB_OF_ROWS_FOR_TIME_TEST, NMB_OF_COLS_FOR_TIME_TEST);
  if (matrix_for_time == NULL) {
    return EXIT_FAILURE;
  }

  fill_random(matrix_for_time, NMB_OF_ROWS_FOR_TIME_TEST, NMB_OF_COLS_FOR_TIME_TEST);

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

  double* sum_parallel_for_time = find_column_sum_parallel(matrix_for_time);
  if (sum_parallel_for_time == NULL) {
    return EXIT_FAILURE;
  }

  struct timeval end_time;
  gettimeofday(&end_time, NULL);
  // перевожу секунды и микросекунды в миллисекунды
  long time_of_work = get_time_of_work(start_time, end_time);
  printf("Время параллельного алгоритма %ld в мс\n", time_of_work);

  gettimeofday(&start_time, NULL);

  double* sum_sequential_for_time = find_column_sum_sequentially(matrix_for_time);
  if (sum_sequential_for_time == NULL) {
    return EXIT_FAILURE;
  }

  gettimeofday(&end_time, NULL);
  // перевожу секунды и микросекунды в миллисекунды
  time_of_work = get_time_of_work(start_time, end_time);
  printf("Время последовательного алгоритма %ld в мс\n", time_of_work);


  free_matrix(matrix_for_time);
  free_matrix(matrix);
  free(sum_sequential_for_time);
  free(sum_parallel_for_time);
  free(sum_of_cols_get_from_sequential);
  free(sum_of_cols_get_from_parallel);
  return 0;
}
