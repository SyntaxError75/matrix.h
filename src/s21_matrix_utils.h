#ifndef MATRIX_HELPERS_H
#define MATRIX_HELPERS_H

#include "matrix.h"

int is_double_equal_to_zero(double a);
void init_matrix(matrix_t *matrix);
void meth_of_Gaus(matrix_t *a, int *sign_of_determinant);
void copy_matrix(matrix_t *src, matrix_t *dest);
void copy_matrix_for_minor(int row, int column, matrix_t *src, matrix_t *dest);
int is_not_valid_matrix(const matrix_t *a);
int is_not_square_matrix(const matrix_t *a);
void init_matrix_with_varables(int rows, int columns, matrix_t *result, ...);
int change_sign_of_values_matrix(matrix_t *a);
int get_sign_of_double(double a);

#endif
