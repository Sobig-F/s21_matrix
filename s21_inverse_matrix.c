#include "s21_matrix.h"

void copy_vals(matrix_t *, matrix_t);
int find_inverse(matrix_t *, matrix_t *, matrix_t *, matrix_t *, double);

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int inversed = OK;

  if (A == NULL || A->matrix == NULL) {
    inversed = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    inversed = CALCULATION_ERROR;
  } else if (s21_create_matrix(A->rows, A->rows, result)) {
    inversed = INCORRECT_MATRIX;
  } else {
    if (A->rows == 1)
      **result->matrix = 1 / (**A->matrix);
    else {
      s21_remove_matrix(result);
      double determ = 0;
      matrix_t complems = {NULL, 0, 0}, transposed = {NULL, 0, 0},
               temp_a = {NULL, 0, 0};
      int temp_created = s21_create_matrix(A->rows, A->rows, &temp_a);

      if (!temp_created) {
        copy_vals(&temp_a, *A);
        s21_determinant(&temp_a, &determ);
        if (determ != 0.0) {
          double lambda = 1 / determ;
          if (find_inverse(A, &complems, &transposed, result, lambda)) {
            inversed = CALCULATION_ERROR;
          }
        } else {
          inversed = CALCULATION_ERROR;
        }
      }
      s21_remove_matrix(&temp_a);
      s21_remove_matrix(&complems);
      s21_remove_matrix(&transposed);
    }
  }

  return inversed;
}

int find_inverse(matrix_t *init_val, matrix_t *complems, matrix_t *transposed,
                 matrix_t *result, double lambda) {
  int res = 1;

  if (!s21_calc_complements(init_val, complems)) {
    if (!s21_transpose(complems, transposed)) {
      if (!s21_mult_number(transposed, lambda, result)) {
        res = 0;
      }
    }
  }

  return res;
}

void copy_vals(matrix_t *dst, matrix_t src) {
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.columns; j++) {
      dst->matrix[i][j] = src.matrix[i][j];
    }
  }
}