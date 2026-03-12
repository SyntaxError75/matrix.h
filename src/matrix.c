#include "matrix.h"
#include <stdarg.h>
#define EPS 1e-6
// 0 — OK;
// 1 — Ошибка, некорректная матрица;
// 2 — Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т. д.).

static int is_double_equal_to_zero(double a){
    return (a<=EPS && a>=-EPS); // если равен нулю, то 1, если не равен то 0
}
static double iter_of_cicle(matrix_t* a,int* sign_of_determinant){
for(int i =0;i<a->rows;i++){
    double *row_of_max_num=NULL;
    double max_num = 0.0;
    double *temp =  a->matrix[i];
    int num_of_row_to_remuve = 0;
        for (int j = 0;j<a->rows;j++){
            if(fabs(a->matrix[j][i])>fabs(max_num)){
                max_num = a->matrix[j][i];
                row_of_max_num =a->matrix[j];
                num_of_row_to_remuve = j;
            }
        }
        if (row_of_max_num !=NULL){
         *sign_of_determinant = -(*sign_of_determinant);
        a->matrix[i] = row_of_max_num;
        a->matrix[num_of_row_to_remuve] = temp;
        }
    }
}
static int copy_matrix(matrix_t *src, matrix_t *dest){
    for (int i = 0; i<src->rows;i++){
        for(int j = 0; j<src->columns;j++){
            dest->matrix[i][j] = src->matrix[i][j];
        }
    }
}
static int find_factorial(int a){
    if(a>0) return (a*(find_factorial((a-1))));
    return 1;
}

static int is_valid_matrix (matrix_t *a){
     return(a == NULL || a->rows<=0 || a->columns<=0 || a->matrix == NULL);
}

static void init_matrix_with_varables(int rows,int columns,matrix_t *result, ...){
    create_matrix(rows,columns,result);
    va_list args;
    va_start(args,result);
    for(int i = 0;i<result->rows;i++){
        for(int j = 0;j < result->columns;j++){
            result->matrix[i][j] = va_arg(args,double);
        }
    }
    va_end(args);
}

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

static int max_value(int n,int m){
    return n>m?n:m;
}
static void zero_matrix(matrix_t* a){
    for (int i = 0;i<a->rows;i++){
        for (int j = 0;j<a->columns;j++){
            a->matrix[i][j] = 0.0;
        }
    }
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
}
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
 
int mult_number(matrix_t *A, double number, matrix_t *result){ //умножение на число 
    if (A==NULL || number == INFINITY || number == NAN|| result == NULL)return 1;
    if(A->rows<=0 || A->columns<=0 || A->matrix == NULL || result->rows<=0 || result->columns<=0 || result->matrix == NULL)  return 1;
    if (A->columns!=result->columns ||A->rows!=result->rows)return 2;
    for(int i = 0;i<A->rows;i++){
        for(int j = 0;j <A->columns;j++){
            result->matrix[i][j] = A->matrix[i][j]*number;
        }
    }
    return 0;
}

int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result){ // умножение 2-х матриц

 if (A==NULL || B ==NULL || result == NULL)return 1;
 if(A->rows<=0 || A->columns<=0 || A->matrix == NULL || B->rows<=0 || B->columns<=0 || B->matrix == NULL || A->columns != B->rows)  return 1;
 if (A->columns != B->rows)  return 2;
 if (create_matrix(A->rows, B->columns, result)) return 1;
 else {
    for (int i = 0;i<A->rows;i++){
    for (int j = 0; j<B->columns;j++){
        for (int k = 0;k<A->columns;k++){
            result->matrix[i][j] += A->matrix[i][k]*B->matrix[k][j];
        }
    } 
 }
    return 0;
}
}

int transpose(matrix_t *A, matrix_t *result){//транспонирование
 if (A==NULL || result == NULL)return 1;
  if(A->rows<=0 || A->columns<=0 || A->matrix == NULL || result->rows<=0 || result->columns<=0 || result->matrix == NULL || A->columns != result->rows || A->rows != result->columns)  return 1;
  for (int i = 0;i<A->rows;i++){
    for (int j = 0; j<A->columns;j++){
        result->matrix[j][i] = A->matrix[i][j];
    }
}
  return 0;
} 
//int calc_complements(matrix_t *A, matrix_t *result){
// Минор матрицы и матрица алгебраических дополнений
int determinant(matrix_t *A, double *result){ // определитель
if (is_valid_matrix(A))return 1;
if (A->rows != A->columns) return 2;
matrix_t temp_matrix;
create_matrix(A->rows,A->columns,&temp_matrix);
copy_matrix(A,&temp_matrix);
//int f = 0;
//int num_of_iter = 0;
int sign_of_determinant = 1; // 0-положительный 1-отрицательный
//while(f<A->rows|| num_of_iter == (A->columns*A->rows)){
//num_of_iter++;
iter_of_cicle(&temp_matrix,&sign_of_determinant);
//}
for (int i = 0;i<temp_matrix.rows;i++){
    for(int k = i+1;k<temp_matrix.rows;k++){
        if (!is_double_equal_to_zero(temp_matrix.matrix[k][i])){
            double factor = temp_matrix.matrix[k][i]/temp_matrix.matrix[i][i];
            for (int j = 0;j<temp_matrix.rows;j++){
                temp_matrix.matrix[k][j] = temp_matrix.matrix[k][j]-factor*temp_matrix.matrix[i][j];
            }
        }

    }
}

copy_matrix(&temp_matrix,A);
remove_matrix(&temp_matrix);
    return 0;
} 
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




int main (){
matrix_t A, B, C;
init_matrix_with_varables(3, 3, &A, 1.0, 2.0, 3.0, 4.0,5.,6.,7.,8.,9.);
init_matrix_with_varables(2, 3, &B, 5.0, 6.0, 7.0, 8.0,9.,10.);
double b = 0.0;
print_matrix(A);
determinant(&A,&b);
print_matrix(A);
    return 0;
}
