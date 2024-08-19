#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *a) {
  if (a != NULL && a->matrix != NULL) {
    for (int i = 0; i < a->rows; i++)
      if (a->matrix[i] != NULL) {
        free(a->matrix[i]);
        a->matrix[i] = NULL;
      }

    if (a->matrix != NULL) {
      free(a->matrix);
      a->matrix = NULL;
    }

    a->rows = 0, a->columns = 0;
  }
}
