#include <stdio.h>
#include <check.h>
#include <stdarg.h>
#include "../matrix.h"
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
// #define SUCCESS 1
// #define FAILURE 0

START_TEST(eq_test_positive){
matrix_t m1,m2,m3,m4;
init_matrix_with_varables(3,3,&m1,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m2,1.000002,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0); // проблема, на крайнем случае при разнице 0.000001 не проходит тест исправь!!!
init_matrix_with_varables(3,3,&m3,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m4,1.0000011,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
ck_assert_int_eq(eq_matrix(&m1,&m2), 0);
ck_assert_int_eq(eq_matrix(&m1,&m3), 1);
ck_assert_int_eq(eq_matrix(&m1,&m4), 0);
ck_assert_int_eq(eq_matrix(&m2,&m4), 1);
}
END_TEST

START_TEST(eq_test_negative){
matrix_t m1,m2,m3,m4;
init_matrix_with_varables(3,3,&m1,-1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m2,-1.000002,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m3,-1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m4,-1.0000011,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
ck_assert_int_eq(eq_matrix(&m1,&m2), 0);
ck_assert_int_eq(eq_matrix(&m1,&m3), 1);
ck_assert_int_eq(eq_matrix(&m1,&m4), 0);
ck_assert_int_eq(eq_matrix(&m2,&m4), 1);
}
END_TEST

START_TEST(eq_test_negative_and_positive){
matrix_t m1,m2,m3,m4;
init_matrix_with_varables(3,3,&m1,-1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m2,-1.000002,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m3,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m4,1.0000011,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
ck_assert_int_eq(eq_matrix(&m1,&m2), 0);
ck_assert_int_eq(eq_matrix(&m1,&m3), 0);
ck_assert_int_eq(eq_matrix(&m1,&m4), 0);
ck_assert_int_eq(eq_matrix(&m2,&m4), 0);
}
END_TEST