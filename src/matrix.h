#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
    double** matrix; 
    int rows;
    int columns;
} matrix_t; 

int s21_create_matrix(int rows, int columns, matrix_t *result);//создание матрицы
void s21_remove_matrix(matrix_t *A);// очистка матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);//сравнение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);//сумма
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);//разность 
int s21_mult_number(matrix_t *A, double number, matrix_t *result);//умножение на число 
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result); // умножение 2-х матриц
int s21_transpose(matrix_t *A, matrix_t *result); //транспонирование
int s21_calc_complements(matrix_t *A, matrix_t *result);// Минор матрицы и матрица алгебраических дополнений
int s21_determinant(matrix_t *A, double *result); // определитель
int s21_inverse_matrix(matrix_t *A, matrix_t *result);// обратная матрица