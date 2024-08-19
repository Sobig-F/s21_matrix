#include "s21_matrix.h"

void cut_matrix(matrix_t A, int row, int column, matrix_t *result);
matrix_t minor_matrix(matrix_t A);

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int result_f = OK;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    result_f = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    result_f = CALCULATION_ERROR;
  } else {
    if (A->rows == 1) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1.0;
    } else {
      s21_remove_matrix(result);
      *result = minor_matrix(*A);
      if (result->matrix == NULL) {
        result_f = CALCULATION_ERROR;
      }
    }
  }

  return result_f;
}

void cut_matrix(matrix_t A, int row, int column, matrix_t *result) {
  s21_create_matrix(A.rows - 1, A.columns - 1, result);
  int r = 0;
  int c = 0;
  for (int i = 0; i < A.rows; ++i) {
    c = 0;
    for (int j = 0; j < A.columns && i != row; ++j) {
      if (j != column) {
        result->matrix[r][c] = A.matrix[i][j];
        ++c;
      }
    }
    if (i != row) {
      ++r;
    }
  }
}

matrix_t minor_matrix(matrix_t A) {
  matrix_t result = {NULL, 0, 0};
  matrix_t *cut_mat = (matrix_t *)calloc(1, sizeof(matrix_t));
  double cash;
  if (!s21_create_matrix(A.rows, A.columns, &result)) {
    for (int i = 0; i < A.rows; ++i) {
      for (int j = 0; j < A.rows; ++j) {
        cut_matrix(A, i, j, cut_mat);
        s21_determinant(cut_mat, &cash);
        s21_remove_matrix(cut_mat);
        if ((i + j) % 2 != 0) {
          cash *= -1;
        }
        result.matrix[i][j] = cash;
      }
    }
  }

  free(cut_mat);
  cut_mat = NULL;

  return result;
}