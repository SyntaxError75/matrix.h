#include "matrix.h"
#define PRINT_INT(x) printf("%s\n", #x)
// 0 — OK;
// 1 — Ошибка, некорректная матрица;
// 2 — Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т. д.).

static int get_sign_of_double(double a){
uint64_t sign;
memcpy(&sign,&a,sizeof(double));
return (((sign>>63)&1) ==1);
}

int s21_create_matrix(int rows, int columns, matrix_t *result){
    int out;
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double**)malloc(rows*sizeof(double*)); 
    out = result->matrix == NULL? FAILURE:SUCCESS;
    for (int i = 0;i<rows;i++){
        result->matrix[i] = (double*)malloc(columns*sizeof(double));
        out = result->matrix == NULL?FAILURE:SUCCESS;
        }
    
    return SUCCESS;
};
void s21_remove_matrix(matrix_t *A){ // очистка матриц
    for (int i = 0;i<A->rows;i++){
        for (int j = 0;j<A->columns;j++){
            A->matrix[i][j] = 0;
        }
    }
};
int s21_eq_matrix(matrix_t *A, matrix_t *B){
int columns_A = A->columns;
int columns_B = B->columns;
int rows_A = A->rows;
int rows_B = B->rows;
int result = (columns_A != columns_B) && (rows_A !=rows_B)?FAILURE:SUCCESS;
if (result == SUCCESS){
for (int i = 0;i<rows_A;i++){
    for(int j = 0;j<columns_A;j++){
        int sign_A = get_sign_of_double(A->matrix[i][j]);
        int sign_B = get_sign_of_double(B->matrix[i][j]);
        if((sign_A == sign_B)&&(fabs(A->matrix[i][j]-B->matrix[i][j])<0.000001)) result =SUCCESS;
        else result = FAILURE;
        if (result == FAILURE) break;
    }
  if (result == FAILURE) break;
}
}
return result;
};//сравнение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);//сумма
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);//разность 
int s21_mult_number(matrix_t *A, double number, matrix_t *result);//умножение на число 
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result); // умножение 2-х матриц
int s21_transpose(matrix_t *A, matrix_t *result); //транспонирование
int s21_calc_complements(matrix_t *A, matrix_t *result);// Минор матрицы и матрица алгебраических дополнений
int s21_determinant(matrix_t *A, double *result); // определитель
int s21_inverse_matrix(matrix_t *A, matrix_t *result);// обратная матрица


static void print_matrix(matrix_t a){
   printf("====PRINTING_MATRIX...PLEASE_WAITING...====\n");
for (int i = 0;i<a.rows;i++){
    for(int j = 0;j<a.columns;j++){
        printf("%4.0f", a.matrix[i][j]);
    }
    printf("\n");
}
  printf("============================================\n\n");
}



int main (){
    matrix_t m1;
    matrix_t m2;
    double x = 1.23456789;
    double x2 = ldexp(x,6);
    printf("%f\n",x2);
    s21_create_matrix(4,3,&m1);
    s21_create_matrix(4,3,&m2);
    int num = 0;
    for (int i = 0;i<m1.rows;i++){
        for (int j = 0; j < m1.columns;j++){
             m1.matrix[i][j] = num;
             m2.matrix[i][j] = num;
            num++;
        }
    }
    print_matrix(m1);
    print_matrix(m2);
    if (s21_eq_matrix(&m1,&m2))printf("\033[0;32mEQUAL\033[0m\n");
    else printf("\033[31mNOT_EQUAL\033[0m\n");

    return 0;
}