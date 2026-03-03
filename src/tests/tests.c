#include <stdio.h>
#include <check.h>
#include <stdarg.h>
#include "../s21_matrix.h"
static void init_matrix_with_varables(int rows,int columns,matrix_t *result, ...){
    s21_create_matrix(rows,columns,result);
    va_list args;
    va_start(args,result);
    for(int i = 0;i<result->rows;i++){
        for(int j = 0;j < result->columns;j++){
            result->matrix[i][j] = va_arg(args,double);
        }
    }
    va_end(args);
}
// #define SUCCESS 1
// #define FAILURE 0
START_TEST(create_matrix){
matrix_t m1;
s21_create_matrix(2,2,&m1);
for(int i = 0;i<2;i++){
    ck_assert_ptr_nonnull(m1.matrix[i]);
    for(int j = 0;j<2;j++){
        ck_assert_double_eq(m1.matrix[i][j],0.0);
}
}
int result = s21_create_matrix(0,1,&m1);
ck_assert_int_eq(result,1);

result = s21_create_matrix(1,0,&m1);
ck_assert_int_eq(result,1);

result = s21_create_matrix(-1,5,&m1);
ck_assert_int_eq(result,1);

result = s21_create_matrix(5,-1,&m1);
ck_assert_int_eq(result,1);

result = s21_create_matrix(5,1,NULL);
ck_assert_int_eq(result,1);

s21_remove_matrix(&m1);
ck_assert_ptr_null(m1.matrix);
ck_assert_int_eq(m1.columns,0);
ck_assert_int_eq(m1.rows,0);
}
END_TEST

START_TEST(eq_test_positive){
matrix_t m1,m2,m3,m4;
init_matrix_with_varables(3,3,&m1,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m2,1.000001,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0); // проблема, на крайнем случае при разнице 0.000001 не проходит тест исправь!!!
init_matrix_with_varables(3,3,&m3,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m4,1.0000011,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
ck_assert_int_eq(s21_eq_matrix(&m1,&m2), 0);
ck_assert_int_eq(s21_eq_matrix(&m1,&m3), 1);
ck_assert_int_eq(s21_eq_matrix(&m1,&m4), 0);
ck_assert_int_eq(s21_eq_matrix(&m2,&m4), 1);
s21_remove_matrix(&m1);
s21_remove_matrix(&m2);
s21_remove_matrix(&m3);
s21_remove_matrix(&m4);
}
END_TEST

START_TEST(eq_test_negative){
matrix_t m1,m2,m3,m4;
init_matrix_with_varables(3,3,&m1,-1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m2,-1.000002,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m3,-1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m4,-1.0000011,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
ck_assert_int_eq(s21_eq_matrix(&m1,&m2), 0);
ck_assert_int_eq(s21_eq_matrix(&m1,&m3), 1);
ck_assert_int_eq(s21_eq_matrix(&m1,&m4), 0);
ck_assert_int_eq(s21_eq_matrix(&m2,&m4), 1);
s21_remove_matrix(&m1);
s21_remove_matrix(&m2);
s21_remove_matrix(&m3);
s21_remove_matrix(&m4);
}
END_TEST

START_TEST(eq_test_negative_and_positive){
matrix_t m1,m2,m3,m4;
init_matrix_with_varables(3,3,&m1,-1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m2,-1.000002,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m3,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m4,1.0000011,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
ck_assert_int_eq(s21_eq_matrix(&m1,&m2), 0);
ck_assert_int_eq(s21_eq_matrix(&m1,&m3), 0);
ck_assert_int_eq(s21_eq_matrix(&m1,&m4), 0);
ck_assert_int_eq(s21_eq_matrix(&m2,&m4), 0);
s21_remove_matrix(&m1);
s21_remove_matrix(&m2);
s21_remove_matrix(&m3);
s21_remove_matrix(&m4);
}
END_TEST

START_TEST( incorrect_matrix_1){
matrix_t m1,m2,m3;
s21_create_matrix(2,3,&m1);
s21_create_matrix(2,5,&m2);
s21_create_matrix(2,3,&m3);
ck_assert_int_eq(s21_sum_matrix(&m1,&m2,&m3),2);

s21_create_matrix(2,3,&m1);
s21_create_matrix(1,3,&m2);
s21_create_matrix(2,3,&m3);
ck_assert_int_eq(s21_sum_matrix(&m1,&m2,&m3),2);

s21_remove_matrix(&m1);
s21_remove_matrix(&m2);
s21_remove_matrix(&m3);
}

END_TEST

START_TEST( incorrect_matrix_2){
matrix_t m1,m2,m3;
s21_create_matrix(2,3,&m1);
s21_create_matrix(2,5,&m2);
s21_create_matrix(2,3,&m3);
ck_assert_int_eq(s21_sum_matrix(&m2,&m1,&m3),2);

s21_create_matrix(2,3,&m1);
s21_create_matrix(1,3,&m2);
s21_create_matrix(2,3,&m3);
ck_assert_int_eq(s21_sum_matrix(&m2,&m1,&m3),2);

s21_remove_matrix(&m1);
s21_remove_matrix(&m2);
s21_remove_matrix(&m3);
}
END_TEST

START_TEST(incorrect_matrix_3){
matrix_t m1,m2,m3;
s21_create_matrix(2,3,&m1);
s21_create_matrix(2,5,&m2);
s21_create_matrix(2,3,&m3);
ck_assert_int_eq(s21_sum_matrix(&m3,&m1,&m2),2);

s21_create_matrix(2,3,&m1);
s21_create_matrix(1,3,&m2);
s21_create_matrix(2,3,&m3);
ck_assert_int_eq(s21_sum_matrix(&m3,&m1,&m2),2);

s21_remove_matrix(&m1);
s21_remove_matrix(&m2);
s21_remove_matrix(&m3);
}

END_TEST

START_TEST(null_pointers_for_sum){
matrix_t m1,m2,m3;
s21_create_matrix(2,3,&m1);
s21_create_matrix(2,5,&m2);
s21_create_matrix(2,3,&m3);
ck_assert_int_eq(s21_sum_matrix(NULL,&m1,&m2),1);
ck_assert_int_eq(s21_sum_matrix(&m1,NULL,&m2),1);
ck_assert_int_eq(s21_sum_matrix(&m1,&m2,NULL),1);
s21_remove_matrix(&m1);
s21_remove_matrix(&m2);
s21_remove_matrix(&m3);
}
END_TEST

START_TEST(sums_1){
    matrix_t m1,m2,m3;
init_matrix_with_varables(1,1,&m1,1.0);
init_matrix_with_varables(1,1,&m2,2.0);
init_matrix_with_varables(1,1,&m3,0.0);
ck_assert_int_eq(s21_sum_matrix(&m1,&m2,&m3),0);
ck_assert_double_eq(m3.matrix[1][1],3.0);
}
