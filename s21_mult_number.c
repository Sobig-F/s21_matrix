#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int result_f = OK;

  if (A == NULL || A->matrix == NULL || result == NULL) {
    result_f = INCORRECT_MATRIX;
  } else if (number == INFINITY) {
    result_f = CALCULATION_ERROR;
  } else {
    result_f = s21_create_matrix(A->rows, A->columns, result);
    if (!result_f) {
      for (int i = 0; i < result->rows && !result_f; ++i) {
        for (int j = 0; j < result->columns && !result_f; ++j) {
          result_f = A->matrix[i][j] == INFINITY ? CALCULATION_ERROR : result_f;
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }

  return result_f;
}