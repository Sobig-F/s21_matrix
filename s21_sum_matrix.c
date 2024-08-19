#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_f = 0;

  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    result_f = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    result_f = CALCULATION_ERROR;
  } else {
    result_f = s21_create_matrix(A->rows, A->columns, result);
    if (!result_f) {
      for (int i = 0; i < result->rows && !result_f; ++i) {
        for (int j = 0; j < result->columns && !result_f; ++j) {
          result_f = A->matrix[i][j] == INFINITY || B->matrix[i][j] == INFINITY
                         ? CALCULATION_ERROR
                         : result_f;
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }

  return result_f;
}