#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result_f = SUCCESS;

  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1) {
    result_f = FAILURE;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    result_f = FAILURE;
  } else {
    for (int i = 0; i < A->rows && result_f; ++i) {
      for (int j = 0; j < A->columns && result_f; ++j) {
        if ((fabs(A->matrix[i][j] - B->matrix[i][j])) >= 1e-7) {
          result_f = FAILURE;
        }
      }
    }
  }

  return result_f;
}