#include "matrix.h"
#define EPS 1e-6
// 0 — OK;
// 1 — Ошибка, некорректная матрица;
// 2 — Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т. д.).

static int change_sign_of_values_matrix(matrix_t* a){
int out = 0;
    for(int i = 0;i<a->rows;i++){
        for(int j = 0;j <a->columns;j++){
            a->matrix[i][j] *= -1;
        }
    }
    return out;
}

static int get_sign_of_double(double a){
uint64_t sign;
memcpy(&sign,&a,sizeof(double));
return (((sign>>63)&1) ==1);
}

int create_matrix(int rows, int columns, matrix_t *result){
int out = 0;
if(rows<=0 || columns<=0 || result == NULL)  return 1;
result->columns = columns;
result->rows = rows;
result->matrix = (double**)malloc(rows*sizeof(double*));    
if (result->matrix == NULL){
    out = 1;
    result->rows = 0;
    result->columns = 0;
    }
    if (out ==0 ){
        for (int i = 0;i<rows;i++){
            result->matrix[i] = (double*)malloc(columns*sizeof(double));
            if (result->matrix[i] == NULL){
                for(int j = 0;j<=i;j++){
                    free(result->matrix[j]);
                    result->matrix[j] = NULL;
                    }
                out = 1;
                free(result->matrix);
                result->matrix = NULL;
                result->rows = 0;
                result->columns = 0;
            }
            else{
                for (int j = 0;j<columns;j++){
                result->matrix[i][j] = 0.0;
                }
                }
        }
    }
    return out;
}

void remove_matrix(matrix_t *A){ // очистка матриц
    for (int i = 0;i<A->rows;i++){
        free(A->matrix[i]);
        A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
}

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
        if((sign_A != sign_B)||((fabs(A->matrix[i][j]-B->matrix[i][j])) + 1e-15 > EPS)) result =FAILURE;
        if (result == FAILURE) break;
    }
        if (result == FAILURE) break;
}
}
return result;
}//сравнение матриц
 int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result){//сумма
    if (A==NULL || B ==NULL || result == NULL)return 1;
    if(A->rows<=0 || A->columns<=0 || A->matrix == NULL || B->rows<=0 || B->columns<=0 || B->matrix == NULL || result->rows<=0 || result->columns<=0 || result->matrix == NULL)  return 1;
    if (A->columns!=B->columns || A->columns!=result->columns ||A->rows!=B->rows || A->rows!=result->rows)return 2;
    for(int i = 0;i<A->rows;i++){
        for(int j = 0;j <A->columns;j++){
            result->matrix[i][j] = A->matrix[i][j]+B->matrix[i][j];
        }
    }
    return 0;
 }
 int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    matrix_t neg_B = *B;
change_sign_of_values_matrix(&neg_B);
int out = sum_matrix(A,&neg_B,result);
return out;
 }//разность 
 
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
// matrix_t m1,m2;
// create_matrix(3,4,&m1);
// //remove_sign_of_values_matrix(&m1);
// //print_matrix(m1);
// for (int i = 0;i<12;i++){
//     printf("%f", m1.matrix[i]);
// }
//     return 0;
// }