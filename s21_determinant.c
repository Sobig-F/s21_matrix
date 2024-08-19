#include "s21_matrix.h"

matrix_t *s21_create_minor(int excluded_row, int excluded_column, matrix_t *A);

int s21_determinant(matrix_t *A, double *result) {
  int result_f = OK;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    result_f = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    result_f = CALCULATION_ERROR;
  }

  if (A->rows == 1 && !result_f) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2 && !result_f) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else if (A->rows > 2 && !result_f) {
    int sign = 1;
    *result = 0;
    for (int i = 0; i < A->columns && result_f == OK; i++) {
      matrix_t *minor = s21_create_minor(0, i, A);
      if (minor == NULL) {
        result_f = INCORRECT_MATRIX;
      } else {
        double minor_det = 0;
        result_f = s21_determinant(minor, &minor_det);
        if (!result_f) {
          *result += sign * A->matrix[0][i] * minor_det;
          sign = -sign;
        }
        s21_remove_matrix(minor);
        free(minor);
        minor = NULL;
      }
    }
  }

  return result_f;
}

matrix_t *s21_create_minor(int excluded_row, int excluded_column, matrix_t *A) {
  matrix_t *minor = NULL;
  if (A != NULL && A->matrix != NULL) {
    minor = calloc(1, sizeof(matrix_t));
  }

  if (minor != NULL) {
    if (s21_create_matrix(A->rows - 1, A->columns - 1, minor) == OK) {
      for (int i = 0, minor_row = 0; i < A->rows; i++) {
        if (i != excluded_row) {
          for (int j = 0, minor_column = 0; j < A->columns; j++) {
            if (j != excluded_column) {
              minor->matrix[minor_row][minor_column] = A->matrix[i][j];
              minor_column++;
            }
          }
          minor_row++;
        }
      }
    }
  }

  return minor;
}