#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL) {
    return INCORRECT_MATRIX;
  }

  int result_f = OK;

  if (rows < 1 || columns < 1) {
    result_f = INCORRECT_MATRIX;
    result->matrix = NULL;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      result_f = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < rows; ++i) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
      }
    }
  }

  return result_f;
}