#include "matrix_utils.h"

#include <math.h>
#include <stdlib.h>

void init_matrix_with_varables(int rows, int columns, matrix_t *result, ...) {
  create_matrix(rows, columns, result);
  va_list args;
  va_start(args, result);
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = va_arg(args, double);
    }
  }
  va_end(args);
}

int is_double_equal_to_zero(double a) {
  return (a <= EPS && a >= -EPS);  // если равен нулю, то 1, если не равен то 0
}

void init_matrix(matrix_t *matrix) {
  matrix->rows = 0;
  matrix->columns = 0;
  matrix->matrix = NULL;
}
void meth_of_Gaus(matrix_t *a, int *sign_of_determinant) {
  for (int i = 0; i < a->rows; i++) {
    int if_i_can_rearrange = 1;
    for (int j = 0; j < a->columns; j++) {
      if (is_double_equal_to_zero(a->matrix[i][j])) {
        if_i_can_rearrange = 0;
      }
    }
    if (if_i_can_rearrange) {
      double *row_of_max_num = NULL;
      double max_num = a->matrix[i][i];
      double *temp = a->matrix[i];
      int num_of_row_to_remuve = 0;
      for (int j = i; j < a->rows; j++) {
        if (fabs(a->matrix[j][i]) > fabs(max_num)) {
          *sign_of_determinant = -(*sign_of_determinant);
          max_num = a->matrix[j][i];
          row_of_max_num = a->matrix[j];
          num_of_row_to_remuve = j;
        }
      }
      if (row_of_max_num != NULL) {
        *sign_of_determinant = -(*sign_of_determinant);
        a->matrix[i] = row_of_max_num;
        a->matrix[num_of_row_to_remuve] = temp;
      }
    }
  }
  for (int i = 0; i < a->rows; i++) {
    for (int k = i + 1; k < a->rows; k++) {
      if (!is_double_equal_to_zero(a->matrix[k][i])) {
        double factor = a->matrix[k][i] / a->matrix[i][i];
        for (int j = 0; j < a->rows; j++) {
          a->matrix[k][j] = a->matrix[k][j] - factor * a->matrix[i][j];
        }
      }
    }
  }
}

void copy_matrix(matrix_t *src, matrix_t *dest) {
  for (int i = 0; i < src->rows; i++) {
    for (int j = 0; j < src->columns; j++) {
      dest->matrix[i][j] = src->matrix[i][j];
    }
  }
}
void copy_matrix_for_minor(int row, int column, matrix_t *src, matrix_t *dest) {
  int dest_i = 0;
  for (int i = 0; i < src->rows; i++) {
    if (i != row) {
      int dest_j = 0;
      for (int j = 0; j < src->columns; j++) {
        if (j != column) {
          dest->matrix[dest_i][dest_j] = src->matrix[i][j];
          dest_j++;
        }
      }
      dest_i++;
    }
  }
}

int is_not_valid_matrix(const matrix_t *a) {
  return (a == NULL || a->rows <= 0 || a->columns <= 0 || a->matrix == NULL);
}
int is_not_square_matrix(const matrix_t *a) { return (a->rows != a->columns); }

int change_sign_of_values_matrix(matrix_t *a) {
  int out = 0;
  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < a->columns; j++) {
      a->matrix[i][j] *= -1;
    }
  }
  return out;
}
