#include "matrix.h"

#include <stdio.h>  // Добавьте для printf

#include "matrix_utils.h"

int create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    res = 1;
  }
  if (!res) {
    init_matrix(result);
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL) {
      result->rows = 0;
      result->columns = 0;
      res = 1;
    }
  }
  if (!res) {
    result->rows = rows;
    result->columns = columns;
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        for (int j = 0; j < i; j++) {
          free(result->matrix[j]);
          result->matrix[j] = NULL;
        }
        free(result->matrix);
        result->matrix = NULL;
        result->rows = 0;
        result->columns = 0;
        res = 1;
        break;
      }
    }
  }

  return res;
}

void remove_matrix(matrix_t *A) {
  if (A == NULL) {
    return;
  }
  if (A->matrix == NULL) {
    A->rows = 0;
    A->columns = 0;
    return;
  }

  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] != NULL) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
  }
  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int eq_matrix(const matrix_t *A, const matrix_t *B) {
  int res = SUCCESS;
  if (A != NULL && B != NULL && A->matrix != NULL && B->matrix != NULL &&
      A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; (i < A->rows) && (res != FAILURE); i++) {
      for (int j = 0; (j < A->columns) && (res != FAILURE); j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
          res = FAILURE;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {  // сумма
  int res = 0;
  if (A == NULL || B == NULL || result == NULL) res = 1;
  if (!res) res = (is_not_valid_matrix(A) || is_not_valid_matrix(B)) ? 1 : 0;
  if (!res) res = (A->rows != B->rows || A->columns != B->columns) ? 2 : 0;
  if (!res) {
    init_matrix(result);
    res = create_matrix(A->rows, A->columns, result);
  }
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res;
}
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int out = (A == NULL || B == NULL || result == NULL) ? 1 : 0;
  if (!out) out = (is_not_valid_matrix(A) || is_not_valid_matrix(B)) ? 1 : 0;
  if (out == 0) {
    matrix_t neg_B;
    create_matrix(B->rows, B->columns, &neg_B);
    copy_matrix(B, &neg_B);
    change_sign_of_values_matrix(&neg_B);
    out = sum_matrix(A, &neg_B, result);
    remove_matrix(&neg_B);
  }
  return out;
}  // разность

int mult_number(matrix_t *A, double number,
                    matrix_t *result) {  // умножение на число
  int res = (A == NULL || isnan(number) || result == NULL) ? 1 : 0;
  if (!res) res = (is_not_valid_matrix(A)) ? 1 : 0;
  if (!res) {
    init_matrix(result);
    res = create_matrix(A->rows, A->columns, result);
  }
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result) {  // умножение 2-х матриц
  int res = (A == NULL || B == NULL || result == NULL) ? 1 : 0;
  if (!res) res = (is_not_valid_matrix(A) || is_not_valid_matrix(B)) ? 1 : 0;
  if (!res) res = (A->columns != B->rows) ? 2 : 0;
  if (!res) {
    init_matrix(result);
    res = create_matrix(A->rows, B->columns, result);
  }
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }

  return res;
}

int transpose(matrix_t *A, matrix_t *result) {  // транспонирование
  int res = (A == NULL || result == NULL) ? 1 : 0;
  if (!res) res = (is_not_valid_matrix(A)) ? 1 : 0;
  if (!res) {
    init_matrix(result);
    res = create_matrix(A->columns, A->rows, result);
  }
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}
int determinant(matrix_t *A, double *result) {  // определитель
  int res = (is_not_valid_matrix(A) || result == NULL) ? 1 : 0;
  if (!res) res = (is_not_square_matrix(A)) ? 2 : 0;
  if (!res) {
    matrix_t temp_matrix;
    create_matrix(A->rows, A->columns, &temp_matrix);
    copy_matrix(A, &temp_matrix);
    int sign_of_determinant = 1;
    switch (temp_matrix.rows) {
      case 1:
        *result = temp_matrix.matrix[0][0];
        break;
      case 2:
        *result = temp_matrix.matrix[0][0] * temp_matrix.matrix[1][1] -
                  temp_matrix.matrix[0][1] * temp_matrix.matrix[1][0];
        break;
      case 3:
        *result = (temp_matrix.matrix[0][0] * temp_matrix.matrix[1][1] *
                       temp_matrix.matrix[2][2] +
                   temp_matrix.matrix[0][1] * temp_matrix.matrix[1][2] *
                       temp_matrix.matrix[2][0] +
                   temp_matrix.matrix[1][0] * temp_matrix.matrix[2][1] *
                       temp_matrix.matrix[0][2]) -
                  ((temp_matrix.matrix[0][2] * temp_matrix.matrix[1][1] *
                        temp_matrix.matrix[2][0] +
                    temp_matrix.matrix[0][1] * temp_matrix.matrix[1][0] *
                        temp_matrix.matrix[2][2] +
                    temp_matrix.matrix[1][2] * temp_matrix.matrix[2][1] *
                        temp_matrix.matrix[0][0]));
        break;
      default:
        meth_of_Gaus(&temp_matrix, &sign_of_determinant);
        *result = 1.;
        for (int i = 0; i < temp_matrix.rows; i++) {
          *result *= temp_matrix.matrix[i][i];
        }
        *result *= sign_of_determinant;
    }
    remove_matrix(&temp_matrix);
  }
  return res;
}
int calc_complements(matrix_t *A, matrix_t *result) {
  int res = (is_not_valid_matrix(A) || result == NULL) ? 1 : 0;
  if (res == 0) res = (is_not_square_matrix(A)) ? 2 : 0;
  if (res == 0) {
    init_matrix(result);
    res = create_matrix(A->rows, A->columns, result);
  }
  if (res == 0) {
    if (A->columns == 1) {
      result->matrix[0][0] = 1.0;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t temp_matrix;
          create_matrix(A->rows - 1, A->columns - 1, &temp_matrix);
          copy_matrix_for_minor(i, j, A, &temp_matrix);
          double deter_of_minor = 0.;
          determinant(&temp_matrix, &deter_of_minor);
          int sign = ((i + j) % 2 == 0) ? 1 : -1;
          result->matrix[i][j] = deter_of_minor * sign;
          remove_matrix(&temp_matrix);
        }
      }
    }
  }
  return res;
}
int inverse_matrix(matrix_t *A, matrix_t *result) {  // обратная матрица
  int res = (is_not_valid_matrix(A) || result == NULL) ? 1 : 0;
  if (!res) res = (is_not_square_matrix(A)) ? 2 : 0;
  if (!res) {
    init_matrix(result);
    res = create_matrix(A->columns, A->rows, result);
  }
  if (!res) {
    double determinant_of_matrix = 0.;
    determinant(A, &determinant_of_matrix);
    if (determinant_of_matrix != 0) {
      matrix_t matrix_of_minors;
      create_matrix(A->rows, A->columns, &matrix_of_minors);
      calc_complements(A, &matrix_of_minors);
      transpose(&matrix_of_minors, result);
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = result->matrix[i][j] / determinant_of_matrix;
        }
      }
    } else
      res = 2;
  }
  return res;
}
