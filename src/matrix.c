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

int create_matrix(int rows, int columns, matrix_t *result){
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
void remove_matrix(matrix_t *A){ // очистка матриц
    for (int i = 0;i<A->rows;i++){
        for (int j = 0;j<A->columns;j++){
            A->matrix[i][j] = 0;
        }
    }
};
int eq_matrix(matrix_t *A, matrix_t *B){
int columns_A = A->columns;
int columns_B = B->columns;
int rows_A = A->rows;
int rows_B = B->rows;
int result = (columns_A != columns_B) || (rows_A !=rows_B)?FAILURE:SUCCESS;
if (result == SUCCESS){
for (int i = 0;i<rows_A;i++){
    for(int j = 0;j<columns_A;j++){
        int sign_A = get_sign_of_double(A->matrix[i][j]);
        int sign_B = get_sign_of_double(B->matrix[i][j]);
        if((sign_A != sign_B)||((fabs(A->matrix[i][j]-B->matrix[i][j]))>=0.000001)) result =FAILURE;
        if (result == FAILURE) break;
    }
        if (result == FAILURE) break;
}
}
return result;
}//сравнение матриц
// int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);//сумма
// int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);//разность 
// int mult_number(matrix_t *A, double number, matrix_t *result);//умножение на число 
// int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result); // умножение 2-х матриц
// int transpose(matrix_t *A, matrix_t *result); //транспонирование
// int calc_complements(matrix_t *A, matrix_t *result);// Минор матрицы и матрица алгебраических дополнений
// int determinant(matrix_t *A, double *result); // определитель
// int inverse_matrix(matrix_t *A, matrix_t *result);// обратная матрица


void print_matrix(matrix_t a){
   printf("====PRINTING_MATRIX...PLEASE_WAITING...====\n");
for (int i = 0;i<a.rows;i++){
    for(int j = 0;j<a.columns;j++){
        printf("%.7f ", a.matrix[i][j]);
    }
    printf("\n");
}
  printf("============================================\n\n");
}



// int main (){
// double a = 1.0;
// double b = 0.000001;
// printf("%d\n", isfinite(a));
// printf("%d\n", isfinite(b));
// printf("%d\n", isfinite(1.0/0.0));
// printf("%d\n", isfinite(0.0/0.0));
//     return 0;
// }