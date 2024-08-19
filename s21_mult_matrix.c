#include "s21_matrix.h"

double multiple(matrix_t *A, matrix_t *B, int x, int y);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int result_f = OK;

  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1 ||
      B == NULL || B->matrix == NULL || B->rows < 1 || B->columns < 1) {
    result_f = INCORRECT_MATRIX;
  } else if (A->columns != B->rows || A->rows != B->columns) {
    result_f = CALCULATION_ERROR;
  } else {
    result_f = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows && !result_f; ++i) {
      for (int j = 0; j < result->columns && !result_f; ++j) {
        result->matrix[i][j] = multiple(A, B, i, j);
        result_f =
            result->matrix[i][j] == INFINITY ? CALCULATION_ERROR : result_f;
      }
    }
  }

  return result_f;
}

double multiple(matrix_t *A, matrix_t *B, int x, int y) {
  double result = 0.0;
  for (int i = 0; i < A->columns && result != INFINITY; ++i) {
    if (A->matrix[x][i] == INFINITY || B->matrix[i][y] == INFINITY) {
      result = INFINITY;
    } else {
      result += (A->matrix[x][i] * B->matrix[i][y]);
    }
  }

  return result;
}