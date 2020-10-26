#ifndef TP_C_CPP_HOMEWORK__PARALLEL_COLUMN_SUM_H_
#define TP_C_CPP_HOMEWORK__PARALLEL_COLUMN_SUM_H_

#include "matrix.h"

double* find_column_sum_parallel(const Matrix* matrix);
int sum_one_column(const Matrix *matrix,
                    int left_column,
                    int right_column,
                    int number_of_rows,
                    double *shared_memory);

#endif  // TP_C_CPP_HOMEWORK__PARALLEL_COLUMN_SUM_H_
