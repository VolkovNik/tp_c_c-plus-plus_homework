extern "C" {
#include "matrix.c"
#include "parallel_column_sum.c"
#include "sequential_column_sum.c"
}

#include <stdlib.h>
#include "gtest/gtest.h"

#define EMPTY_TEST "tests/empty_test.txt"  // пустой файл
#define WRONG_PATH "tests/null_test.txt"   // нет файла
#define TEST_WITHOUT_NMB_COLS \
  "tests/null_cols.txt"  // в файле нет кол-ва столбцов
#define TEST_WITHOUT_MTRX "tests/null_matrix.txt"  // в файле нет матрицы
#define TEST_MTRX_FULL_OF_ONE "tests/test1.txt"  // матрица из единиц 4x4

#define NMB_OF_COLS_FOR_STRESS_TEST1 5000
#define NMB_OF_ROWS_FOR_STRESS_TEST1 10000
#define NMB_OF_COLS_FOR_STRESS_TEST2 2500
#define NMB_OF_ROWS_FOR_STRESS_TEST2 5000
#define NMB_OF_COLS_FOR_STRESS_TEST3 1000
#define NMB_OF_ROWS_FOR_STRESS_TEST3 1000

class test_matrix : public ::testing::Test {
 protected:
  void SetUp() {
    matrix_full_of_one = create_matrix_from_file(TEST_MTRX_FULL_OF_ONE);
    null_matrix = NULL;

    zero_rows = 0;
    zero_cols = 0;

    rows_of_mtrx_4x4 = 4;
    cols_of_mtrx_4x4 = 4;
  }
  void TearDown() { free_matrix(matrix_full_of_one); }
  Matrix* null_matrix;
  Matrix* matrix_full_of_one;
  Matrix* matrix_for_tests;

  size_t zero_rows;
  size_t zero_cols;

  size_t rows_of_mtrx_4x4;
  size_t cols_of_mtrx_4x4;
};

TEST_F(test_matrix, t1) {
  ASSERT_TRUE(create_matrix_from_file(EMPTY_TEST) == NULL);
}

TEST_F(test_matrix, t2) {
  ASSERT_TRUE(create_matrix_from_file(WRONG_PATH) == NULL);
}

TEST_F(test_matrix, t3) {
  ASSERT_TRUE(create_matrix_from_file(TEST_WITHOUT_NMB_COLS) == NULL);
}

TEST_F(test_matrix, t4) {
  ASSERT_TRUE(create_matrix_from_file(TEST_WITHOUT_MTRX) == NULL);
}

TEST_F(test_matrix, t5) {
  ASSERT_TRUE(create_matrix(zero_rows, zero_cols) == NULL);
}

TEST_F(test_matrix, t6) {
  ASSERT_EQ(get_rows(null_matrix, &zero_rows), EXIT_FAILURE);
}

TEST_F(test_matrix, t7) {
  ASSERT_EQ(get_cols(null_matrix, &zero_cols), EXIT_FAILURE);
}

TEST_F(test_matrix, t8) { ASSERT_EQ(free_matrix(null_matrix), EXIT_FAILURE); }

TEST_F(test_matrix, t9) {
  matrix_for_tests = create_matrix_from_file(TEST_MTRX_FULL_OF_ONE);

  ASSERT_TRUE(matrix_for_tests != NULL);
  ASSERT_EQ(matrix_for_tests->num_cols, cols_of_mtrx_4x4);
  ASSERT_EQ(matrix_for_tests->num_rows, rows_of_mtrx_4x4);

  for (size_t i = 0; i < cols_of_mtrx_4x4; ++i) {
    for (size_t j = 0; j < rows_of_mtrx_4x4; ++j) {
      ASSERT_EQ(matrix_for_tests->matrix[i][j], 1);
    }
  }

  free_matrix(matrix_for_tests);
}

TEST_F(test_matrix, t10) {
  matrix_for_tests = create_matrix(4, 4);

  ASSERT_TRUE(matrix_for_tests != NULL);
  ASSERT_EQ(matrix_for_tests->num_cols, cols_of_mtrx_4x4);
  ASSERT_EQ(matrix_for_tests->num_rows, rows_of_mtrx_4x4);

  free_matrix(matrix_for_tests);
}

class test_parallel : public ::testing::Test {
 protected:
  void SetUp() {
    zero_left = 0;
    zero_right = 0;
    test1_left = 0;
    test1_right = 4;

    zero_nmb_of_rows = 0;
    nmb_of_rows_equal_four = 4;

    matrix_full_of_one = create_matrix_from_file(TEST_MTRX_FULL_OF_ONE);
    null_matrix = NULL;

    null_shared_memory = NULL;
    test1_shared_memory =
        (double*)malloc(sizeof(double) * nmb_of_rows_equal_four);
    for (size_t i = 0; i < nmb_of_rows_equal_four; ++i) {
      test1_shared_memory[i] = 0;
    }
  }

  void TearDown() {
    free_matrix(matrix_full_of_one);
    free(test1_shared_memory);
  }
  Matrix* null_matrix;
  Matrix* matrix_full_of_one;

  double* null_shared_memory;
  double* test1_shared_memory;

  long zero_left;
  long zero_right;
  long test1_left;
  long test1_right;

  size_t zero_nmb_of_rows;
  size_t nmb_of_rows_equal_four;

  double sum_of_mtrx_full_of_one[4] = {4, 4, 4, 4};
};

TEST_F(test_parallel, t1) {
  ASSERT_EQ(sum_one_column(null_matrix, zero_left, zero_right, zero_nmb_of_rows,
                           null_shared_memory),
            EXIT_FAILURE);
}

TEST_F(test_parallel, t2) {
  ASSERT_EQ(sum_one_column(matrix_full_of_one, test1_left, test1_right,
                           nmb_of_rows_equal_four, test1_shared_memory),
            EXIT_SUCCESS);
  ASSERT_EQ(test1_shared_memory[0], sum_of_mtrx_full_of_one[0]);
  ASSERT_EQ(test1_shared_memory[1], sum_of_mtrx_full_of_one[1]);
  ASSERT_EQ(test1_shared_memory[2], sum_of_mtrx_full_of_one[2]);
  ASSERT_EQ(test1_shared_memory[3], sum_of_mtrx_full_of_one[3]);
}

TEST_F(test_parallel, t3) {
  ASSERT_TRUE(find_column_sum_parallel(null_matrix) == NULL);
}

TEST_F(test_parallel, t4) {
  double* answer = find_column_sum_parallel(matrix_full_of_one);
  ASSERT_TRUE(answer != NULL);
  ASSERT_EQ(answer[0], sum_of_mtrx_full_of_one[0]);
  ASSERT_EQ(answer[1], sum_of_mtrx_full_of_one[1]);
  ASSERT_EQ(answer[2], sum_of_mtrx_full_of_one[2]);
  ASSERT_EQ(answer[3], sum_of_mtrx_full_of_one[3]);
  free(answer);
}

class test_sequential : public ::testing::Test {
 protected:
  void SetUp() {
    matrix_full_of_one = create_matrix_from_file(TEST_MTRX_FULL_OF_ONE);
    null_matrix = NULL;
  }
  void TearDown() { free_matrix(matrix_full_of_one); }
  Matrix* null_matrix;
  Matrix* matrix_full_of_one;

  double sum_of_mtrx_full_of_one[4] = {4, 4, 4, 4};
};

TEST_F(test_sequential, t1) {
  ASSERT_TRUE(find_column_sum_sequentially(null_matrix) == NULL);
}

TEST_F(test_sequential, t2) {
  double* answer = find_column_sum_sequentially(matrix_full_of_one);
  ASSERT_TRUE(answer != NULL);
  ASSERT_EQ(answer[0], sum_of_mtrx_full_of_one[0]);
  ASSERT_EQ(answer[1], sum_of_mtrx_full_of_one[1]);
  ASSERT_EQ(answer[2], sum_of_mtrx_full_of_one[2]);
  ASSERT_EQ(answer[3], sum_of_mtrx_full_of_one[3]);
  free(answer);
}

TEST(stress_test, t1) {
  Matrix* random_matrix =
      create_matrix(NMB_OF_ROWS_FOR_STRESS_TEST1, NMB_OF_COLS_FOR_STRESS_TEST1);

  for (size_t i = 0; i < NMB_OF_ROWS_FOR_STRESS_TEST1; ++i) {
    for (size_t j = 0; j < NMB_OF_COLS_FOR_STRESS_TEST1; ++j) {
      random_matrix->matrix[i][j] = rand();
    }
  }

  double* sum_of_rows_get_from_parallel =
      find_column_sum_parallel(random_matrix);
  double* sum_of_rows_ger_from_sequential =
      find_column_sum_sequentially(random_matrix);

  for (size_t i = 0; i < NMB_OF_COLS_FOR_STRESS_TEST1; ++i) {
    ASSERT_EQ(sum_of_rows_get_from_parallel[i],
              sum_of_rows_ger_from_sequential[i]);
  }
}

TEST(stress_test, t2) {
  Matrix* random_matrix =
      create_matrix(NMB_OF_ROWS_FOR_STRESS_TEST2, NMB_OF_COLS_FOR_STRESS_TEST2);

  for (size_t i = 0; i < NMB_OF_ROWS_FOR_STRESS_TEST2; ++i) {
    for (size_t j = 0; j < NMB_OF_COLS_FOR_STRESS_TEST2; ++j) {
      random_matrix->matrix[i][j] = rand();
    }
  }

  double* sum_of_rows_get_from_parallel =
      find_column_sum_parallel(random_matrix);
  double* sum_of_rows_ger_from_sequential =
      find_column_sum_sequentially(random_matrix);

  for (size_t i = 0; i < NMB_OF_COLS_FOR_STRESS_TEST2; ++i) {
    ASSERT_EQ(sum_of_rows_get_from_parallel[i],
              sum_of_rows_ger_from_sequential[i]);
  }
}

TEST(stress_test, t3) {
  Matrix* random_matrix =
      create_matrix(NMB_OF_ROWS_FOR_STRESS_TEST3, NMB_OF_COLS_FOR_STRESS_TEST3);

  for (size_t i = 0; i < NMB_OF_ROWS_FOR_STRESS_TEST3; ++i) {
    for (size_t j = 0; j < NMB_OF_COLS_FOR_STRESS_TEST3; ++j) {
      random_matrix->matrix[i][j] = rand();
    }
  }

  double* sum_of_rows_get_from_parallel =
      find_column_sum_parallel(random_matrix);
  double* sum_of_rows_ger_from_sequential =
      find_column_sum_sequentially(random_matrix);

  for (size_t i = 0; i < NMB_OF_COLS_FOR_STRESS_TEST3; ++i) {
    ASSERT_EQ(sum_of_rows_get_from_parallel[i],
              sum_of_rows_ger_from_sequential[i]);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}