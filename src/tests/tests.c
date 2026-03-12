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
//==================================================================================================================================
//================================================== CREATE MATRIX =================================================================
//==================================================================================================================================

START_TEST(create_matrix){
matrix_t m1;
create_matrix(2,2,&m1);
for(int i = 0;i<2;i++){
    ck_assert_ptr_nonnull(m1.matrix[i]);
    for(int j = 0;j<2;j++){
        ck_assert_double_eq(m1.matrix[i][j],0.0);
}
}
int result = create_matrix(0,1,&m1);
ck_assert_int_eq(result,1);

result = create_matrix(1,0,&m1);
ck_assert_int_eq(result,1);

result = create_matrix(-1,5,&m1);
ck_assert_int_eq(result,1);

result = create_matrix(5,-1,&m1);
ck_assert_int_eq(result,1);

result = create_matrix(5,1,NULL);
ck_assert_int_eq(result,1);

remove_matrix(&m1);
ck_assert_ptr_null(m1.matrix);
ck_assert_int_eq(m1.columns,0);
ck_assert_int_eq(m1.rows,0);
}
END_TEST
//==================================================================================================================================
//================================================== IS EQUEL MATRIX ===============================================================
//==================================================================================================================================

START_TEST(eq_test_positive){
matrix_t m1,m2,m3,m4;
init_matrix_with_varables(3,3,&m1,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m2,1.000001,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0); 
init_matrix_with_varables(3,3,&m3,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
init_matrix_with_varables(3,3,&m4,1.0000011,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0);
ck_assert_int_eq(eq_matrix(&m1,&m2), 0);
ck_assert_int_eq(eq_matrix(&m1,&m3), 1);
ck_assert_int_eq(eq_matrix(&m1,&m4), 0);
ck_assert_int_eq(eq_matrix(&m2,&m4), 1);
remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&m3);
remove_matrix(&m4);
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
remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&m3);
remove_matrix(&m4);
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
remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&m3);
remove_matrix(&m4);
}
END_TEST
//==================================================================================================================================
//================================================== SUM OF MATRIX =================================================================
//==================================================================================================================================

START_TEST( incorrect_matrix_1){
matrix_t m1,m2,m3;
create_matrix(2,3,&m1);
create_matrix(2,5,&m2);
create_matrix(2,3,&m3);
ck_assert_int_eq(sum_matrix(&m1,&m2,&m3),2);

create_matrix(2,3,&m1);
create_matrix(1,3,&m2);
create_matrix(2,3,&m3);
ck_assert_int_eq(sum_matrix(&m1,&m2,&m3),2);

remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&m3);
}

END_TEST

START_TEST( incorrect_matrix_2){
matrix_t m1,m2,m3;
create_matrix(2,3,&m1);
create_matrix(2,5,&m2);
create_matrix(2,3,&m3);
ck_assert_int_eq(sum_matrix(&m2,&m1,&m3),2);

create_matrix(2,3,&m1);
create_matrix(1,3,&m2);
create_matrix(2,3,&m3);
ck_assert_int_eq(sum_matrix(&m2,&m1,&m3),2);

remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&m3);
}
END_TEST

START_TEST(incorrect_matrix_3){
matrix_t m1,m2,m3;
create_matrix(2,3,&m1);
create_matrix(2,5,&m2);
create_matrix(2,3,&m3);
ck_assert_int_eq(sum_matrix(&m3,&m1,&m2),2);

create_matrix(2,3,&m1);
create_matrix(1,3,&m2);
create_matrix(2,3,&m3);
ck_assert_int_eq(sum_matrix(&m3,&m1,&m2),2);

remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&m3);
}

END_TEST

START_TEST(null_pointers_for_sum){
matrix_t m1,m2,m3;
create_matrix(2,3,&m1);
create_matrix(2,5,&m2);
create_matrix(2,3,&m3);
ck_assert_int_eq(sum_matrix(NULL,&m1,&m2),1);
ck_assert_int_eq(sum_matrix(&m1,NULL,&m2),1);
ck_assert_int_eq(sum_matrix(&m1,&m2,NULL),1);
remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&m3);
}
END_TEST

START_TEST(sums_1){
    matrix_t m1,m2,m3;
init_matrix_with_varables(1,1,&m1,1.0);
init_matrix_with_varables(1,1,&m2,2.0);
init_matrix_with_varables(1,1,&m3,0.0);
ck_assert_int_eq(sum_matrix(&m1,&m2,&m3),0);
ck_assert_double_eq(m3.matrix[0][0],3.0);
}
END_TEST
//==================================================================================================================================
//================================================== MULTIPLEX TO NUMBER ===========================================================
//==================================================================================================================================
START_TEST(mult_to_number_1){
    matrix_t m1,m2;
    int n = 0;
    init_matrix_with_varables(1,1,&m1,0.);
    create_matrix(1,1,&m2);
    ck_assert_int_eq(mult_number(&m1,n,&m2),0);
    ck_assert_double_eq(m1.matrix[0][0],0.);
    remove_matrix(&m1);
    remove_matrix(&m2);
}
END_TEST

START_TEST(mult_to_number_2){
    matrix_t m1,m2;
    int n = 2;
    init_matrix_with_varables(1,1,&m1,1.);
    create_matrix(1,1,&m2);
    ck_assert_int_eq(mult_number(&m1,n,&m2),0);
    ck_assert_double_eq(m2.matrix[0][0],2.);
    remove_matrix(&m1);
    remove_matrix(&m2);
}
END_TEST

START_TEST(mult_to_number_INFINITY){
    matrix_t m1,m2;
    double n = INFINITY;
    init_matrix_with_varables(1,1,&m1,1.);
    create_matrix(1,1,&m2);
    ck_assert_int_eq(mult_number(&m1,n,&m2),1);
    ck_assert_double_eq(m2.matrix[0][0],0.);
    remove_matrix(&m1);
    remove_matrix(&m2);
}
END_TEST
//==================================================================================================================================
//================================================== MULTIPLEX MATRIXES ============================================================
//==================================================================================================================================

START_TEST(mult_matrix_1_by_1){
matrix_t m1,m2,result,matrix_to_compare;
create_matrix(1,1,&result);
init_matrix_with_varables(1,1,&m1,0.000001);
init_matrix_with_varables(1,1,&m2,453454.);
init_matrix_with_varables(1,1,&matrix_to_compare,0.453454);
ck_assert_int_eq(mult_matrix(&m1,&m2,&result),0);
ck_assert_int_eq(eq_matrix(&result,&matrix_to_compare),1);
remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&result);
remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(mult_matrix_3_by_2_and_2_by_3){
matrix_t m1,m2,result,matrix_to_compare;
create_matrix(3,3,&result);
init_matrix_with_varables(3,2,&m1,1.,2.,3.,4.,5.,6.);
init_matrix_with_varables(2,3,&m2,1.,2.,3.,4.,5.,6.);
init_matrix_with_varables(3,3,&matrix_to_compare,9.0, 12.0, 15.0, 19.0, 26.0, 33.0, 29.0, 40.0, 51.0);
ck_assert_int_eq(mult_matrix(&m1,&m2,&result),0);
ck_assert_int_eq(eq_matrix(&result,&matrix_to_compare),1);
remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&result);
remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(mult_matrix_10_by_2_and_2_by_7){
matrix_t m1,m2,result,matrix_to_compare;
create_matrix(10,7,&result);
init_matrix_with_varables(10,2,&m1,1.5, 2.3, 3.7, 4.1, 5.2, 6.8, 7.9, 8.4, 9.2, 1.7, 2.5, 3.9, 4.6, 5.3, 6.1, 7.2, 8.3, 9.5, 0.8, 1.2);
init_matrix_with_varables(2,7,&m2,2.1, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.1, 1.3, 2.4, 3.5, 4.6, 5.7, 6.8);
init_matrix_with_varables(10,7,&matrix_to_compare,
24.08, 8.09, 12.27, 16.45, 20.63, 24.81, 28.99,
45.08, 17.91, 26.49, 35.07, 43.65, 52.23, 60.81,
72.80, 26.52, 39.72, 52.92, 66.12, 79.32, 92.52,
93.03, 37.78, 55.71, 73.64, 91.57, 109.50, 127.43,
34.79, 33.49, 45.48, 57.47, 69.46, 81.45, 93.44,
40.74, 13.57, 20.61, 27.65, 34.69, 41.73, 48.77,
57.89, 22.53, 33.42, 44.31, 55.20, 66.09, 76.98,
78.33, 30.10, 44.73, 59.36, 73.99, 88.62, 103.25,
103.88, 40.57, 60.15, 79.73, 99.31, 118.89, 138.47,
12.60, 4.28, 6.48, 8.68, 10.88, 13.08, 15.28);
ck_assert_int_eq(mult_matrix(&m1,&m2,&result),0);
ck_assert_int_eq(eq_matrix(&result,&matrix_to_compare),1);
remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&result);
remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(mult_matrix_from_task){
matrix_t m1,m2,result,matrix_to_compare;
create_matrix(3,3,&result);
init_matrix_with_varables(3,2,&m1,1.,4.,2.,5.,3.,6.);
init_matrix_with_varables(2,3,&m2,1.,-1.,1.,2.,3.,4.);
init_matrix_with_varables(3,3,&matrix_to_compare,9.,11.,17.,12.,13.,22.,15.,15.,27.);
ck_assert_int_eq(mult_matrix(&m1,&m2,&result),0);
ck_assert_int_eq(eq_matrix(&result,&matrix_to_compare),1);
remove_matrix(&m1);
remove_matrix(&m2);
remove_matrix(&result);
remove_matrix(&matrix_to_compare);
}
END_TEST

//==================================================================================================================================
//================================================== TRANSPOSE MATRIXES ============================================================
//==================================================================================================================================

START_TEST(transpose_matrix_from_task){
    matrix_t m1,result, matrix_to_compare;
    init_matrix_with_varables(3, 2, &m1, 1.0, 4.0, 2.0, 5.0,3.,6.);
    init_matrix_with_varables(2, 3, &result, 5.0, 6.0, 7.0, 8.0,9.,10.);
    init_matrix_with_varables(2, 3, &matrix_to_compare, 1.0, 2.0, 3.0, 4.0,5.,6.);
    ck_assert_int_eq(transpose(&m1,&result),0);
    ck_assert_int_eq(eq_matrix(&result,&matrix_to_compare),1);
    remove_matrix(&m1);
    remove_matrix(&result);
    remove_matrix(&matrix_to_compare);
}

START_TEST(transpose_matrix_error_1){
    matrix_t m1,result, matrix_to_compare;
    init_matrix_with_varables(3, 2, &m1, 1.0, 4.0, 2.0, 5.0,3.,6.);
    init_matrix_with_varables(1, 3, &result, 5.0, 6.0, 7.0, 8.0,9.,10.);
    init_matrix_with_varables(2, 3, &matrix_to_compare, 1.0, 2.0, 3.0, 4.0,5.,6.);
    ck_assert_int_eq(transpose(&m1,&result),1);
    ck_assert_int_eq(eq_matrix(&result,&matrix_to_compare),0);
    remove_matrix(&m1);
    remove_matrix(&result);
    remove_matrix(&matrix_to_compare);
}
END_TEST