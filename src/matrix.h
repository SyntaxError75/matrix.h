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

int create_matrix(int rows, int columns, matrix_t *result);//создание матрицы
void remove_matrix(matrix_t *A);// очистка матриц
int eq_matrix(matrix_t *A, matrix_t *B);//сравнение матриц
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);//сумма
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);//разность 
int mult_number(matrix_t *A, double number, matrix_t *result);//умножение на число 
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result); // умножение 2-х матриц
int transpose(matrix_t *A, matrix_t *result); //транспонирование
int calc_complements(matrix_t *A, matrix_t *result);// Минор матрицы и матрица алгебраических дополнений
int determinant(matrix_t *A, double *result); // определитель
int inverse_matrix(matrix_t *A, matrix_t *result);// обратная матрица