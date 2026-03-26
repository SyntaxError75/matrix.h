#include <check.h>
#include <stdarg.h>
#include <stdio.h>

#include "../matrix.h"
#include "../matrix_utils.h"

// #define SUCCESS 1
// #define FAILURE 0
//==================================================================================================================================
//================================================== CREATE MATRIX
//=================================================================
//==================================================================================================================================

START_TEST(create_matrix) {
  matrix_t m1;
  int result;

  // Тест 1: Нормальное создание
  result = create_matrix(2, 2, &m1);
  ck_assert_int_eq(result, 0);

  // Проверяем выделение памяти
  ck_assert_ptr_nonnull(m1.matrix);
  for (int i = 0; i < 2; i++) {
    ck_assert_ptr_nonnull(m1.matrix[i]);
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq(m1.matrix[i][j], 0.0);
    }
  }

  // Проверяем корректность размеров
  ck_assert_int_eq(m1.rows, 2);
  ck_assert_int_eq(m1.columns, 2);

  // Очищаем после успешного создания
  remove_matrix(&m1);
  ck_assert_ptr_null(m1.matrix);
  ck_assert_int_eq(m1.rows, 0);
  ck_assert_int_eq(m1.columns, 0);

  // Тест 2: Нулевые строки
  result = create_matrix(0, 1, &m1);
  ck_assert_int_eq(result, 1);
  // Матрица должна быть в валидном состоянии (или обнулена)
  ck_assert_int_eq(m1.rows, 0);
  ck_assert_int_eq(m1.columns, 0);
  ck_assert_ptr_null(m1.matrix);

  // Тест 3: Нулевые столбцы
  result = create_matrix(1, 0, &m1);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(m1.rows, 0);
  ck_assert_int_eq(m1.columns, 0);
  ck_assert_ptr_null(m1.matrix);

  // Тест 4: Отрицательные строки
  result = create_matrix(-1, 5, &m1);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(m1.rows, 0);
  ck_assert_int_eq(m1.columns, 0);
  ck_assert_ptr_null(m1.matrix);

  // Тест 5: Отрицательные столбцы
  result = create_matrix(5, -1, &m1);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(m1.rows, 0);
  ck_assert_int_eq(m1.columns, 0);
  ck_assert_ptr_null(m1.matrix);

  // Тест 6: NULL указатель
  result = create_matrix(5, 1, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(with_zero_rows) {
  matrix_t m;
  int ret = create_matrix(0, 1, &m);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(with_zero_columns) {
  matrix_t m;
  int ret = create_matrix(1, 0, &m);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(with_zero_pointer) {
  int ret = create_matrix(1, 1, NULL);
  ck_assert_int_eq(ret, 1);
}
END_TEST
//==================================================================================================================================
//================================================== IS EQUEL MATRIX
//===============================================================
//==================================================================================================================================

START_TEST(eq_test_positive) {
  matrix_t m1, m2, m3, m4;

  // Тест 1: разница ровно 1e-6 (должно быть равно)
  init_matrix_with_varables(3, 3, &m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                            9.0);
  init_matrix_with_varables(3, 3, &m2, 1.000001, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
                            8.0, 9.0);

  // Тест 2: разница 1e-7 (меньше EPS, должно быть равно)
  init_matrix_with_varables(3, 3, &m3, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                            9.0);
  init_matrix_with_varables(3, 3, &m4, 1.0000001, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
                            8.0, 9.0);

  // Ожидаем SUCCESS (1) для m1 и m2 (разница 1e-6)
  ck_assert_int_eq(eq_matrix(&m1, &m2), SUCCESS);
  // Ожидаем SUCCESS для m3 и m4 (разница 1e-7)
  ck_assert_int_eq(eq_matrix(&m3, &m4), SUCCESS);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
  remove_matrix(&m4);
}
END_TEST

START_TEST(eq_test_negative) {
  matrix_t m1, m2;

  // Тест: разница 1.1e-6 (больше EPS, должно быть НЕ равно)
  init_matrix_with_varables(3, 3, &m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                            9.0);
  init_matrix_with_varables(3, 3, &m2, 1.0000011, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
                            8.0, 9.0);

  // Ожидаем FAILURE (0)
  ck_assert_int_eq(eq_matrix(&m1, &m2), FAILURE);

  remove_matrix(&m1);
  remove_matrix(&m2);
}
END_TEST

START_TEST(eq_test_negative_and_positive) {
  matrix_t m1, m2, m3, m4;
  init_matrix_with_varables(3, 3, &m1, -1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                            9.0);
  init_matrix_with_varables(3, 3, &m2, -1.000002, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
                            8.0, 9.0);
  init_matrix_with_varables(3, 3, &m3, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                            9.0);
  init_matrix_with_varables(3, 3, &m4, 1.0000011, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,
                            8.0, 9.0);
  ck_assert_int_eq(eq_matrix(&m1, &m2), 0);
  ck_assert_int_eq(eq_matrix(&m1, &m3), 0);
  ck_assert_int_eq(eq_matrix(&m1, &m4), 0);
  ck_assert_int_eq(eq_matrix(&m2, &m4), 0);
  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
  remove_matrix(&m4);
}
END_TEST
//==================================================================================================================================
//================================================== SUM OF MATRIX
//=================================================================
//==================================================================================================================================

// Тест на некорректные размеры матриц (разные размеры)
START_TEST(sum_incorrect_sizes_1) {
  matrix_t m1, m2, m3;

  // Случай 1: разные столбцы
  create_matrix(2, 3, &m1);
  create_matrix(2, 5, &m2);
  create_matrix(2, 3, &m3);

  // Заполняем матрицы значениями
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = i + j + 1;
    }
  }
  for (int i = 0; i < m2.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m2.matrix[i][j] = (i + 1) * (j + 1);
    }
  }

  ck_assert_int_eq(sum_matrix(&m1, &m2, &m3), 2);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
}
END_TEST

START_TEST(sum_incorrect_sizes_2) {
  matrix_t m1, m2, m3;

  // Случай 2: разные строки
  create_matrix(2, 3, &m1);
  create_matrix(1, 3, &m2);
  create_matrix(2, 3, &m3);

  // Заполняем матрицы значениями
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = i * 2 + j;
    }
  }
  for (int i = 0; i < m2.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m2.matrix[i][j] = j * 1.5;
    }
  }

  ck_assert_int_eq(sum_matrix(&m1, &m2, &m3), 2);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
}
END_TEST

START_TEST(sum_incorrect_sizes_3) {
  matrix_t m1, m2, m3;

  // Случай 3: разные строки и столбцы
  create_matrix(3, 4, &m1);
  create_matrix(2, 5, &m2);
  create_matrix(3, 4, &m3);

  // Заполняем матрицы значениями
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = i * 10 + j;
    }
  }
  for (int i = 0; i < m2.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m2.matrix[i][j] = (i + j) * 0.5;
    }
  }

  ck_assert_int_eq(sum_matrix(&m1, &m2, &m3), 2);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
}
END_TEST

// Тест на нулевые указатели
START_TEST(sum_null_pointers) {
  matrix_t m1, m2, m3;
  create_matrix(2, 2, &m1);
  create_matrix(2, 2, &m2);
  create_matrix(2, 2, &m3);

  // Заполняем тестовыми данными
  m1.matrix[0][0] = 1.0;
  m1.matrix[0][1] = 2.0;
  m1.matrix[1][0] = 3.0;
  m1.matrix[1][1] = 4.0;
  m2.matrix[0][0] = 5.0;
  m2.matrix[0][1] = 6.0;
  m2.matrix[1][0] = 7.0;
  m2.matrix[1][1] = 8.0;

  ck_assert_int_eq(sum_matrix(NULL, &m1, &m2), 1);
  ck_assert_int_eq(sum_matrix(&m1, NULL, &m2), 1);
  ck_assert_int_eq(sum_matrix(&m1, &m2, NULL), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
}
END_TEST

// Тест на некорректные матрицы (неинициализированные)
START_TEST(sum_invalid_matrices) {
  matrix_t m1 = {NULL, 0, 0};
  matrix_t m2 = {NULL, 0, 0};
  matrix_t m3;
  create_matrix(2, 2, &m3);

  ck_assert_int_eq(sum_matrix(&m1, &m2, &m3), 1);
  ck_assert_int_eq(sum_matrix(&m1, &m2, NULL), 1);

  remove_matrix(&m3);
}
END_TEST

// Тест на сумму матриц 1x1
START_TEST(sum_1x1) {
  matrix_t m1, m2, result;
  init_matrix_with_varables(1, 1, &m1, 1.0);
  init_matrix_with_varables(1, 1, &m2, 2.0);
  // result НЕ создаем - функция создаст

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 3.0);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);  // удаляем result, созданный функцией
}
END_TEST

// Тест на сумму матриц 1x1 с отрицательными числами
START_TEST(sum_1x1_negative) {
  matrix_t m1, m2, result;
  init_matrix_with_varables(1, 1, &m1, -5.5);
  init_matrix_with_varables(1, 1, &m2, 3.2);
  // result НЕ создаем

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], -2.3);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
}
END_TEST

// Тест на сумму матриц 2x2
START_TEST(sum_2x2) {
  matrix_t m1, m2, result, expected;

  init_matrix_with_varables(2, 2, &m1, 1.0, 2.0, 3.0, 4.0);
  init_matrix_with_varables(2, 2, &m2, 5.0, 6.0, 7.0, 8.0);
  // result НЕ создаем
  init_matrix_with_varables(2, 2, &expected, 6.0, 8.0, 10.0, 12.0);

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

// Тест на сумму матриц 3x3
START_TEST(sum_3x3) {
  matrix_t m1, m2, result, expected;

  init_matrix_with_varables(3, 3, &m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                            9.0);

  init_matrix_with_varables(3, 3, &m2, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0,
                            1.0);

  // result НЕ создаем

  init_matrix_with_varables(3, 3, &expected, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0,
                            10.0, 10.0, 10.0);

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

// Тест на сумму матриц 3x4
START_TEST(sum_3x4) {
  matrix_t m1, m2, result, expected;

  create_matrix(3, 4, &m1);
  create_matrix(3, 4, &m2);
  // result НЕ создаем
  create_matrix(3, 4, &expected);

  const double values1[12] = {1.1, 2.2, 3.3, 4.4,  5.5,  6.6,
                              7.7, 8.8, 9.9, 10.1, 11.2, 12.3};
  const double values2[12] = {0.9, 1.8, 2.7, 3.6, 4.5, 5.4,
                              6.3, 7.2, 8.1, 9.0, 9.9, 10.8};
  const double expected_values[12] = {2.0,  4.0,  6.0,  8.0,  10.0, 12.0,
                                      14.0, 16.0, 18.0, 19.1, 21.1, 23.1};

  int idx = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      m1.matrix[i][j] = values1[idx];
      m2.matrix[i][j] = values2[idx];
      expected.matrix[i][j] = expected_values[idx];
      idx++;
    }
  }

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

// Тест на сумму с нулевой матрицей
START_TEST(sum_with_zero_matrix) {
  matrix_t m1, zero, result, expected;

  init_matrix_with_varables(2, 2, &m1, 1.0, 2.0, 3.0, 4.0);
  create_matrix(2, 2, &zero);
  // result НЕ создаем
  init_matrix_with_varables(2, 2, &expected, 1.0, 2.0, 3.0, 4.0);

  for (int i = 0; i < zero.rows; i++) {
    for (int j = 0; j < zero.columns; j++) {
      zero.matrix[i][j] = 0.0;
    }
  }

  ck_assert_int_eq(sum_matrix(&m1, &zero, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&zero);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST
// Тест на сумму матриц с дробными числами, проверка точности до 6 знаков
START_TEST(sum_precision_test) {
  matrix_t m1, m2, result, expected;

  init_matrix_with_varables(2, 2, &m1, 0.1234567, 0.2345678, 0.3456789,
                            0.4567890);
  init_matrix_with_varables(2, 2, &m2, 0.8765433, 0.7654322, 0.6543211,
                            0.5432110);
  create_matrix(2, 2, &result);
  init_matrix_with_varables(2, 2, &expected, 1.000000, 1.000000, 1.000000,
                            1.000000);

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

// Тест на сумму матриц с очень большими числами
START_TEST(sum_large_numbers) {
  matrix_t m1, m2, result, expected;

  init_matrix_with_varables(2, 2, &m1, 1e10, 2e10, 3e10, 4e10);
  init_matrix_with_varables(2, 2, &m2, 5e10, 6e10, 7e10, 8e10);
  create_matrix(2, 2, &result);
  init_matrix_with_varables(2, 2, &expected, 6e10, 8e10, 1e11, 1.2e11);

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

// Тест на сумму матриц с очень маленькими числами
START_TEST(sum_small_numbers) {
  matrix_t m1, m2, result, expected;

  init_matrix_with_varables(2, 2, &m1, 1e-10, 2e-10, 3e-10, 4e-10);
  init_matrix_with_varables(2, 2, &m2, 5e-10, 6e-10, 7e-10, 8e-10);
  create_matrix(2, 2, &result);
  init_matrix_with_varables(2, 2, &expected, 6e-10, 8e-10, 1e-9, 1.2e-9);

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

// Тест на сумму с отрицательными числами
START_TEST(sum_negative_numbers) {
  matrix_t m1, m2, result, expected;

  init_matrix_with_varables(3, 3, &m1, -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0,
                            -8.0, -9.0);

  init_matrix_with_varables(3, 3, &m2, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0,
                            -2.0, -1.0);

  create_matrix(3, 3, &result);
  init_matrix_with_varables(3, 3, &expected, -10.0, -10.0, -10.0, -10.0, -10.0,
                            -10.0, -10.0, -10.0, -10.0);

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

// Тест на сумму матриц с нулевыми указателями внутри структуры
START_TEST(sum_null_matrix_pointers) {
  matrix_t m1, m2, result;

  create_matrix(2, 2, &m1);
  create_matrix(2, 2, &m2);
  create_matrix(2, 2, &result);

  // Искусственно портим матрицы
  free(m1.matrix);
  m1.matrix = NULL;

  ck_assert_int_eq(sum_matrix(&m1, &m2, &result), 1);

  // Восстанавливаем для корректного удаления
  create_matrix(2, 2, &m1);
  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
}
END_TEST
//==================================================================================================================================
//================================================== MULTIPLEX TO NUMBER
//===========================================================
//==================================================================================================================================
START_TEST(mult_to_number_1) {
  matrix_t m1, result;
  int n = 0;
  init_matrix_with_varables(1, 1, &m1, 0.);
  // result НЕ создаем

  ck_assert_int_eq(mult_number(&m1, n, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 0.);

  remove_matrix(&m1);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_to_number_2) {
  matrix_t m1, result;
  int n = 2;
  init_matrix_with_varables(1, 1, &m1, 1.);
  // result НЕ создаем

  ck_assert_int_eq(mult_number(&m1, n, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 2.);

  remove_matrix(&m1);
  remove_matrix(&result);
}
END_TEST

START_TEST(mult_to_number_INFINITY) {
  matrix_t m1, result;
  double n = INFINITY;
  init_matrix_with_varables(1, 1, &m1, 1.0);
  // result НЕ создаем

  int res = mult_number(&m1, n, &result);
  ck_assert_int_eq(res, 0);

  remove_matrix(&m1);
  remove_matrix(&result);
}
END_TEST
//==================================================================================================================================
//================================================== MULTIPLEX MATRIXES
//============================================================
//==================================================================================================================================

START_TEST(mult_matrix_1_by_1) {
  matrix_t m1, m2, result, matrix_to_compare;
  // result НЕ создаем
  init_matrix_with_varables(1, 1, &m1, 0.000001);
  init_matrix_with_varables(1, 1, &m2, 453454.);
  init_matrix_with_varables(1, 1, &matrix_to_compare, 0.453454);

  ck_assert_int_eq(mult_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &matrix_to_compare), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(mult_matrix_3_by_2_and_2_by_3) {
  matrix_t m1, m2, result, matrix_to_compare;
  create_matrix(3, 3, &result);
  init_matrix_with_varables(3, 2, &m1, 1., 2., 3., 4., 5., 6.);
  init_matrix_with_varables(2, 3, &m2, 1., 2., 3., 4., 5., 6.);
  init_matrix_with_varables(3, 3, &matrix_to_compare, 9.0, 12.0, 15.0, 19.0,
                            26.0, 33.0, 29.0, 40.0, 51.0);
  ck_assert_int_eq(mult_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &matrix_to_compare), 1);
  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(mult_matrix_10_by_2_and_2_by_7) {
  matrix_t m1, m2, result, matrix_to_compare;
  create_matrix(10, 7, &result);
  init_matrix_with_varables(10, 2, &m1, 1.5, 2.3, 3.7, 4.1, 5.2, 6.8, 7.9, 8.4,
                            9.2, 1.7, 2.5, 3.9, 4.6, 5.3, 6.1, 7.2, 8.3, 9.5,
                            0.8, 1.2);
  init_matrix_with_varables(2, 7, &m2, 2.1, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.1,
                            1.3, 2.4, 3.5, 4.6, 5.7, 6.8);
  init_matrix_with_varables(
      10, 7, &matrix_to_compare, 24.08, 8.09, 12.27, 16.45, 20.63, 24.81, 28.99,
      45.08, 17.91, 26.49, 35.07, 43.65, 52.23, 60.81, 72.80, 26.52, 39.72,
      52.92, 66.12, 79.32, 92.52, 93.03, 37.78, 55.71, 73.64, 91.57, 109.50,
      127.43, 34.79, 33.49, 45.48, 57.47, 69.46, 81.45, 93.44, 40.74, 13.57,
      20.61, 27.65, 34.69, 41.73, 48.77, 57.89, 22.53, 33.42, 44.31, 55.20,
      66.09, 76.98, 78.33, 30.10, 44.73, 59.36, 73.99, 88.62, 103.25, 103.88,
      40.57, 60.15, 79.73, 99.31, 118.89, 138.47, 12.60, 4.28, 6.48, 8.68,
      10.88, 13.08, 15.28);
  ck_assert_int_eq(mult_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &matrix_to_compare), 1);
  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(mult_matrix_from_task) {
  matrix_t m1, m2, result, matrix_to_compare;
  create_matrix(3, 3, &result);
  init_matrix_with_varables(3, 2, &m1, 1., 4., 2., 5., 3., 6.);
  init_matrix_with_varables(2, 3, &m2, 1., -1., 1., 2., 3., 4.);
  init_matrix_with_varables(3, 3, &matrix_to_compare, 9., 11., 17., 12., 13.,
                            22., 15., 15., 27.);
  ck_assert_int_eq(mult_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &matrix_to_compare), 1);
  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
  remove_matrix(&matrix_to_compare);
}
END_TEST

//==================================================================================================================================
//================================================== TRANSPOSE MATRIXES
//============================================================
//==================================================================================================================================

START_TEST(transpose_matrix_from_task) {
  matrix_t m1, result, matrix_to_compare;
  init_matrix_with_varables(3, 2, &m1, 1.0, 4.0, 2.0, 5.0, 3.0, 6.0);
  // result НЕ создаем
  init_matrix_with_varables(2, 3, &matrix_to_compare, 1.0, 2.0, 3.0, 4.0, 5.0,
                            6.0);

  ck_assert_int_eq(transpose(&m1, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &matrix_to_compare), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
  remove_matrix(&matrix_to_compare);
}
END_TEST

START_TEST(transpose_matrix_error_1) {
  matrix_t m1, result, matrix_to_compare;
  init_matrix_with_varables(3, 2, &m1, 1.0, 4.0, 2.0, 5.0, 3., 6.);
  init_matrix_with_varables(1, 3, &result, 5.0, 6.0, 7.0, 8.0, 9., 10.);
  init_matrix_with_varables(2, 3, &matrix_to_compare, 1.0, 2.0, 3.0, 4.0, 5.,
                            6.);
  ck_assert_int_eq(transpose(&m1, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &matrix_to_compare), 1);
  remove_matrix(&m1);
  remove_matrix(&result);
  remove_matrix(&matrix_to_compare);
}
END_TEST

//==================================================================================================================================
//================================================== DETERMINANT OF MATRIX 1/1
//===========================================
//==================================================================================================================================

START_TEST(determinant_of_matrix_1_1_simple) {
  matrix_t m1;
  double result;
  init_matrix_with_varables(1, 1, &m1, 1.2345);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1.2345);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_1_1_zero) {
  matrix_t m1;
  double result;
  init_matrix_with_varables(1, 1, &m1, 0.);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 0.000);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_1_1_wery_big) {
  matrix_t m1;
  double result;
  init_matrix_with_varables(1, 1, &m1, 1234567890.564);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1234567890.564);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_1_1_wery_small) {
  matrix_t m1;
  double result;
  init_matrix_with_varables(1, 1, &m1, 0.000001234567890564);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 0.000001234567890564);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_1_1_null_pointer_instead_matrix) {
  double result;
  int answer = determinant(NULL, &result);
  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(determinant_of_matrix_1_1_null_pointer_instead_result) {
  matrix_t m1;
  init_matrix_with_varables(1, 1, &m1, 0.000001234567890564);
  int answer = determinant(&m1, NULL);
  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(determinant_of_matrix_1_2_not_square_matrix) {
  matrix_t m1;
  double result;
  init_matrix_with_varables(1, 2, &m1, 1.234567890564, 2.34);
  int answer = determinant(&m1, &result);
  ck_assert_double_eq(answer, 2);
  remove_matrix(&m1);
}
END_TEST

//==================================================================================================================================
//================================================== SUBTRACTION OF MATRIX
//=========================================================
//==================================================================================================================================

START_TEST(sub_incorrect_matrix_1) {
  matrix_t m1, m2, m3;
  create_matrix(2, 3, &m1);
  create_matrix(2, 5, &m2);
  create_matrix(2, 3, &m3);
  ck_assert_int_eq(sub_matrix(&m1, &m2, &m3), 2);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
}
END_TEST

START_TEST(sub_incorrect_matrix_2) {
  matrix_t m1, m2, m3;
  create_matrix(2, 3, &m1);
  create_matrix(1, 3, &m2);
  create_matrix(2, 3, &m3);
  ck_assert_int_eq(sub_matrix(&m1, &m2, &m3), 2);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
}
END_TEST

START_TEST(sub_null_pointers) {
  matrix_t m1, m2, m3;
  create_matrix(2, 2, &m1);
  create_matrix(2, 2, &m2);
  create_matrix(2, 2, &m3);

  ck_assert_int_eq(sub_matrix(NULL, &m2, &m3), 1);
  ck_assert_int_eq(sub_matrix(&m1, NULL, &m3), 1);
  ck_assert_int_eq(sub_matrix(&m1, &m2, NULL), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
}
END_TEST

START_TEST(sub_1) {
  matrix_t m1, m2, result;
  init_matrix_with_varables(1, 1, &m1, 5.0);
  init_matrix_with_varables(1, 1, &m2, 3.0);
  // result НЕ создаем

  ck_assert_int_eq(sub_matrix(&m1, &m2, &result), 0);
  ck_assert_double_eq(result.matrix[0][0], 2.0);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&result);
}
END_TEST

START_TEST(sub_2) {
  matrix_t m1, m2, m3, result;
  init_matrix_with_varables(2, 2, &m1, 1.0, 2.0, 3.0, 4.0);
  init_matrix_with_varables(2, 2, &m2, 4.0, 3.0, 2.0, 1.0);
  init_matrix_with_varables(2, 2, &m3, -3.0, -1.0, 1.0, 3.0);
  // result НЕ создаем

  ck_assert_int_eq(sub_matrix(&m1, &m2, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &m3), 1);

  remove_matrix(&m1);
  remove_matrix(&m2);
  remove_matrix(&m3);
  remove_matrix(&result);
}
END_TEST

//==================================================================================================================================
//================================================== DETERMINANT (CONTINUED)
//=======================================================
//==================================================================================================================================

START_TEST(determinant_of_matrix_2_2) {
  matrix_t m1;
  double result;
  init_matrix_with_varables(2, 2, &m1, 1.0, 2.0, 3.0,
                            4.0);  // det = 1*4 - 2*3 = -2
  determinant(&m1, &result);
  ck_assert_double_eq(result, -2.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_3_3) {
  matrix_t m1;
  double result;
  // Матрица из примера в задании (определитель = 0)
  init_matrix_with_varables(3, 3, &m1, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                            9.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 0.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_3_3_non_zero) {
  matrix_t m1;
  double result;
  // Матрица из примера для обратной (определитель = -1)
  init_matrix_with_varables(3, 3, &m1, 2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0,
                            -3.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, -1.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_3_3_another) {
  matrix_t m1;
  double result;
  init_matrix_with_varables(
      3, 3, &m1, 1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0,
      1.0);  // det = 1*4*1 + 2*2*5 + 3*0*2 - 3*4*5 - 2*0*1 - 1*2*2 = 4 + 20 + 0
             // - 60 - 0 - 4 = -40
  determinant(&m1, &result);
  ck_assert_double_eq(result, -40.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_5x5) {
  matrix_t m1;
  double result;
  // Матрица 5x5 с известным определителем
  // Используем диагональную матрицу (определитель = произведение диагональных
  // элементов)
  init_matrix_with_varables(5, 5, &m1, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 3.0, 0.0,
                            0.0, 0.0, 0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                            5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 2.0 * 3.0 * 4.0 * 5.0 * 6.0);  // 720
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_5x5_upper_triangular) {
  matrix_t m1;
  double result;
  // Верхнетреугольная матрица (определитель = произведение диагональных
  // элементов)
  init_matrix_with_varables(5, 5, &m1, 1.0, 2.0, 3.0, 4.0, 5.0, 0.0, 2.0, 3.0,
                            4.0, 5.0, 0.0, 0.0, 3.0, 4.0, 5.0, 0.0, 0.0, 0.0,
                            4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 5.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1.0 * 2.0 * 3.0 * 4.0 * 5.0);  // 120
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_5x5_lower_triangular) {
  matrix_t m1;
  double result;
  // Нижнетреугольная матрица (определитель = произведение диагональных
  // элементов)
  init_matrix_with_varables(5, 5, &m1, 1.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0, 0.0,
                            0.0, 0.0, 3.0, 3.0, 3.0, 0.0, 0.0, 4.0, 4.0, 4.0,
                            4.0, 0.0, 5.0, 5.0, 5.0, 5.0, 5.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1.0 * 2.0 * 3.0 * 4.0 * 5.0);  // 120
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_5x5_identity) {
  matrix_t m1;
  double result;
  // Единичная матрица (определитель = 1)
  init_matrix_with_varables(5, 5, &m1, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                            1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_5x5_with_zeros) {
  matrix_t m1;
  double result;
  // Матрица с нулевым определителем (две строки пропорциональны)
  init_matrix_with_varables(5, 5, &m1, 1.0, 2.0, 3.0, 4.0, 5.0, 2.0, 4.0, 6.0,
                            8.0, 10.0,  // в два раза больше первой строки
                            1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
                            3.0, 4.0, 5.0, 6.0, 7.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 0.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_6x6) {
  matrix_t m1;
  double result;
  // Диагональная матрица 6x6
  init_matrix_with_varables(6, 6, &m1, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0,
                            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0,
                            0.0, 0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                            5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0);  // 720
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_6x6_upper_triangular) {
  matrix_t m1;
  double result;
  // Верхнетреугольная матрица 6x6
  init_matrix_with_varables(6, 6, &m1, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 2.0,
                            2.0, 2.0, 2.0, 2.0, 0.0, 0.0, 3.0, 3.0, 3.0, 3.0,
                            0.0, 0.0, 0.0, 4.0, 4.0, 4.0, 0.0, 0.0, 0.0, 0.0,
                            5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 6.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0);  // 720
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_6x6_lower_triangular) {
  matrix_t m1;
  double result;
  // Нижнетреугольная матрица 6x6
  init_matrix_with_varables(6, 6, &m1, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 2.0,
                            0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 0.0, 0.0, 0.0,
                            1.0, 2.0, 3.0, 4.0, 0.0, 0.0, 1.0, 2.0, 3.0, 4.0,
                            5.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0);  // 720
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_6x6_identity) {
  matrix_t m1;
  double result;
  // Единичная матрица 6x6
  init_matrix_with_varables(6, 6, &m1, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
                            0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                            1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 1.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_6x6_with_zeros) {
  matrix_t m1;
  double result;
  // Матрица с нулевым определителем (два столбца одинаковы)
  init_matrix_with_varables(6, 6, &m1, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0,
                            4.0, 5.0, 6.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 3.0,
                            4.0, 5.0, 6.0, 7.0, 8.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                            9.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 6.0);
  determinant(&m1, &result);
  ck_assert_double_eq(result, 0.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_5x5_random) {
  matrix_t m1;
  double result;
  // Случайная матрица 5x5 с известным определителем (вычисленным)
  init_matrix_with_varables(5, 5, &m1, 1.0, 2.0, 0.0, 0.0, 0.0, 3.0, 4.0, 0.0,
                            0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 0.0, 0.0, 0.0, 3.0,
                            4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 5.0);
  // Определитель блочно-диагональной матрицы = (1*4-2*3) * (1*4-2*3) * 5 = (-2)
  // * (-2) * 5 = 20
  determinant(&m1, &result);
  ck_assert_double_eq(result, 20.0);
  remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_of_matrix_6x6_random) {
  matrix_t m1;
  double result;
  // Случайная матрица 6x6 с известным определителем
  init_matrix_with_varables(6, 6, &m1, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 3.0,
                            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 0.0, 0.0,
                            0.0, 0.0, 3.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                            1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 3.0, 4.0);
  // Определитель = 2 * 3 * (1*4-2*3) * (1*4-2*3) = 6 * (-2) * (-2) = 24
  determinant(&m1, &result);
  ck_assert_double_eq_tol(result, 24.0, 1e-6);  // Используем tolerance
  remove_matrix(&m1);
}
END_TEST
//==================================================================================================================================
//================================================== CALC COMPLEMENTS
//==============================================================
//==================================================================================================================================

START_TEST(calc_complements_incorrect) {
  matrix_t m1, result;
  create_matrix(2, 3, &m1);  // Не квадратная
  create_matrix(2, 2, &result);

  ck_assert_int_eq(calc_complements(&m1, &result), 2);
  ck_assert_int_eq(calc_complements(NULL, &result), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_1_1) {
  matrix_t m1, result, expected;
  init_matrix_with_varables(1, 1, &m1, 5.0);
  // result НЕ создаем
  init_matrix_with_varables(1, 1, &expected, 1.0);

  ck_assert_int_eq(calc_complements(&m1, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_3_3_from_task) {
  matrix_t m1, result, expected;
  // Матрица из задания (для миноров)
  init_matrix_with_varables(3, 3, &m1, 1.0, 2.0, 3.0, 0.0, 4.0, 2.0, 5.0, 2.0,
                            1.0);
  create_matrix(3, 3, &result);
  // Матрица алгебраических дополнений из задания
  init_matrix_with_varables(3, 3, &expected, 0.0, 10.0, -20.0, 4.0, -14.0, 8.0,
                            -8.0, -2.0, 4.0);

  ck_assert_int_eq(calc_complements(&m1, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_3_3_identity) {
  matrix_t m1, result, expected;
  init_matrix_with_varables(3, 3, &m1, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
                            1.0);
  create_matrix(3, 3, &result);
  // Для единичной матрицы алг. дополнения на главной диагонали = 1, остальные =
  // 0
  init_matrix_with_varables(3, 3, &expected, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                            0.0, 1.0);

  ck_assert_int_eq(calc_complements(&m1, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

//==================================================================================================================================
//================================================== INVERSE MATRIX
//================================================================
//==================================================================================================================================

START_TEST(inverse_matrix_incorrect) {
  matrix_t m1, result;
  create_matrix(2, 3, &m1);  // Не квадратная
  create_matrix(2, 2, &result);

  ck_assert_int_eq(inverse_matrix(&m1, &result), 2);
  ck_assert_int_eq(inverse_matrix(NULL, &result), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_det_zero) {
  matrix_t m1, result;
  init_matrix_with_varables(2, 2, &m1, 1.0, 2.0, 1.0, 2.0);  // det = 0
  create_matrix(2, 2, &result);

  ck_assert_int_eq(inverse_matrix(&m1, &result), 2);

  remove_matrix(&m1);
  remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_1_1) {
  matrix_t m1, result, expected;
  init_matrix_with_varables(1, 1, &m1, 5.0);
  // result НЕ создаем
  init_matrix_with_varables(1, 1, &expected, 0.2);

  ck_assert_int_eq(inverse_matrix(&m1, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_matrix_2_2) {
  matrix_t m1, result, expected;
  // A = [4, 7; 2, 6]
  init_matrix_with_varables(2, 2, &m1, 4.0, 7.0, 2.0, 6.0);
  create_matrix(2, 2, &result);
  // Ожидаемая обратная: (1/det=10) * [6, -7; -2, 4] = [0.6, -0.7; -0.2, 0.4]
  init_matrix_with_varables(2, 2, &expected, 0.6, -0.7, -0.2, 0.4);

  ck_assert_int_eq(inverse_matrix(&m1, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_matrix_3_3_from_task) {
  matrix_t m1, result, expected;
  // Матрица из задания
  init_matrix_with_varables(3, 3, &m1, 2.0, 5.0, 7.0, 6.0, 3.0, 4.0, 5.0, -2.0,
                            -3.0);
  create_matrix(3, 3, &result);
  // Обратная матрица из задания (с обратными знаками, т.к. в задании опечатка?
  // Проверим по формуле) По расчетам: (1/|A| = -1) * транспонированная матрица
  // алг. дополнений. Матрица алг. доп. из задания: [-1, 38, -27; 1, -41, 29;
  // -1, 34, -24] Транспонированная: [-1, 1, -1; 38, -41, 34; -27, 29, -24]
  // Умножаем на -1: [1, -1, 1; -38, 41, -34; 27, -29, 24]
  init_matrix_with_varables(3, 3, &expected, 1.0, -1.0, 1.0, -38.0, 41.0, -34.0,
                            27.0, -29.0, 24.0);

  ck_assert_int_eq(inverse_matrix(&m1, &result), 0);
  ck_assert_int_eq(eq_matrix(&result, &expected), 1);

  remove_matrix(&m1);
  remove_matrix(&result);
  remove_matrix(&expected);
}
END_TEST

Suite *suite(void) {
  Suite *s = suite_create("Math Tests");

  // Создаём группы тестов
  TCase *tc_eq_matrix = tcase_create("Eq Matrix Tests");
  TCase *tc_create_matrix = tcase_create("Create Matrix Tests");
  TCase *tc_sum_matrix = tcase_create("Sum Matrix Tests");
  TCase *tc_sub_matrix = tcase_create("Sub Matrix Tests");
  TCase *tc_mult_number = tcase_create("Mult Number Tests");
  TCase *tc_mult_matrix = tcase_create("Mult Matrix Tests");
  TCase *tc_transpose = tcase_create("Transpose Tests");
  TCase *tc_determinant = tcase_create("Determinant Tests");
  TCase *tc_calc_complements = tcase_create("Calc Complements Tests");
  TCase *tc_inverse = tcase_create("Inverse Matrix Tests");

  // ========== EQ MATRIX TESTS ==========
  tcase_add_test(tc_eq_matrix, eq_test_positive);
  tcase_add_test(tc_eq_matrix, eq_test_negative);
  tcase_add_test(tc_eq_matrix, eq_test_negative_and_positive);

  // ========== CREATE MATRIX TESTS ==========
  tcase_add_test(tc_create_matrix, create_matrix);
  tcase_add_test(tc_create_matrix, with_zero_rows);
  tcase_add_test(tc_create_matrix, with_zero_columns);
  tcase_add_test(tc_create_matrix, with_zero_pointer);

  // ========== SUM MATRIX TESTS ==========
  tcase_add_test(tc_sum_matrix, sum_incorrect_sizes_1);
  tcase_add_test(tc_sum_matrix, sum_incorrect_sizes_2);
  tcase_add_test(tc_sum_matrix, sum_incorrect_sizes_3);
  tcase_add_test(tc_sum_matrix, sum_null_pointers);
  tcase_add_test(tc_sum_matrix, sum_invalid_matrices);
  tcase_add_test(tc_sum_matrix, sum_1x1);
  tcase_add_test(tc_sum_matrix, sum_1x1_negative);
  tcase_add_test(tc_sum_matrix, sum_2x2);
  tcase_add_test(tc_sum_matrix, sum_3x3);
  tcase_add_test(tc_sum_matrix, sum_3x4);
  tcase_add_test(tc_sum_matrix, sum_with_zero_matrix);
  tcase_add_test(tc_sum_matrix, sum_precision_test);
  tcase_add_test(tc_sum_matrix, sum_large_numbers);
  tcase_add_test(tc_sum_matrix, sum_small_numbers);
  tcase_add_test(tc_sum_matrix, sum_negative_numbers);
  tcase_add_test(tc_sum_matrix, sum_null_matrix_pointers);

  // ========== SUB MATRIX TESTS ==========
  tcase_add_test(tc_sub_matrix, sub_incorrect_matrix_1);
  tcase_add_test(tc_sub_matrix, sub_incorrect_matrix_2);
  tcase_add_test(tc_sub_matrix, sub_null_pointers);
  tcase_add_test(tc_sub_matrix, sub_1);
  tcase_add_test(tc_sub_matrix, sub_2);

  // ========== MULT NUMBER TESTS ==========
  tcase_add_test(tc_mult_number, mult_to_number_1);
  tcase_add_test(tc_mult_number, mult_to_number_2);
  tcase_add_test(tc_mult_number, mult_to_number_INFINITY);

  // ========== MULT MATRIX TESTS ==========
  tcase_add_test(tc_mult_matrix, mult_matrix_1_by_1);
  tcase_add_test(tc_mult_matrix, mult_matrix_3_by_2_and_2_by_3);
  tcase_add_test(tc_mult_matrix, mult_matrix_10_by_2_and_2_by_7);
  tcase_add_test(tc_mult_matrix, mult_matrix_from_task);

  // ========== TRANSPOSE TESTS ==========
  tcase_add_test(tc_transpose, transpose_matrix_from_task);
  tcase_add_test(tc_transpose, transpose_matrix_error_1);

  // ========== DETERMINANT TESTS ==========
  tcase_add_test(tc_determinant, determinant_of_matrix_1_1_simple);
  tcase_add_test(tc_determinant, determinant_of_matrix_1_1_zero);
  tcase_add_test(tc_determinant, determinant_of_matrix_1_1_wery_big);
  tcase_add_test(tc_determinant, determinant_of_matrix_1_1_wery_small);
  tcase_add_test(tc_determinant,
                 determinant_of_matrix_1_1_null_pointer_instead_matrix);
  tcase_add_test(tc_determinant,
                 determinant_of_matrix_1_1_null_pointer_instead_result);
  tcase_add_test(tc_determinant, determinant_of_matrix_1_2_not_square_matrix);
  tcase_add_test(tc_determinant, determinant_of_matrix_2_2);
  tcase_add_test(tc_determinant, determinant_of_matrix_3_3);
  tcase_add_test(tc_determinant, determinant_of_matrix_3_3_non_zero);
  tcase_add_test(tc_determinant, determinant_of_matrix_3_3_another);
  tcase_add_test(tc_determinant, determinant_of_matrix_5x5);
  tcase_add_test(tc_determinant, determinant_of_matrix_5x5_upper_triangular);
  tcase_add_test(tc_determinant, determinant_of_matrix_5x5_lower_triangular);
  tcase_add_test(tc_determinant, determinant_of_matrix_5x5_identity);
  tcase_add_test(tc_determinant, determinant_of_matrix_5x5_with_zeros);
  tcase_add_test(tc_determinant, determinant_of_matrix_5x5_random);
  tcase_add_test(tc_determinant, determinant_of_matrix_6x6);
  tcase_add_test(tc_determinant, determinant_of_matrix_6x6_upper_triangular);
  tcase_add_test(tc_determinant, determinant_of_matrix_6x6_lower_triangular);
  tcase_add_test(tc_determinant, determinant_of_matrix_6x6_identity);
  tcase_add_test(tc_determinant, determinant_of_matrix_6x6_with_zeros);
  tcase_add_test(tc_determinant, determinant_of_matrix_6x6_random);

  // ========== CALC COMPLEMENTS TESTS ==========
  tcase_add_test(tc_calc_complements, calc_complements_incorrect);
  tcase_add_test(tc_calc_complements, calc_complements_1_1);
  tcase_add_test(tc_calc_complements, calc_complements_3_3_from_task);
  tcase_add_test(tc_calc_complements, calc_complements_3_3_identity);

  // ========== INVERSE MATRIX TESTS ==========
  tcase_add_test(tc_inverse, inverse_matrix_incorrect);
  tcase_add_test(tc_inverse, inverse_matrix_det_zero);
  tcase_add_test(tc_inverse, inverse_matrix_1_1);
  tcase_add_test(tc_inverse, inverse_matrix_2_2);
  tcase_add_test(tc_inverse, inverse_matrix_3_3_from_task);

  // Добавляем все группы в набор
  suite_add_tcase(s, tc_eq_matrix);
  suite_add_tcase(s, tc_create_matrix);
  suite_add_tcase(s, tc_sum_matrix);
  suite_add_tcase(s, tc_sub_matrix);
  suite_add_tcase(s, tc_mult_number);
  suite_add_tcase(s, tc_mult_matrix);
  suite_add_tcase(s, tc_transpose);
  suite_add_tcase(s, tc_determinant);
  suite_add_tcase(s, tc_calc_complements);
  suite_add_tcase(s, tc_inverse);
  return s;
}
