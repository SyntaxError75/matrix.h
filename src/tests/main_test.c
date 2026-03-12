
#include "tests.c"
#include <stdio.h>
#include <math.h>
#include <check.h>
int main (){
        // Создаём набор тестов
        Suite *suite = suite_create("Math Tests");
        // Создаём группу тестов (можно называть как угодно)
        TCase *tc_math = tcase_create("Simple Math");
        TCase *tc_sum_matrix = tcase_create("Test sum of matrixs");
        TCase *tc_mutl_to_num = tcase_create("Testing multiplex matrix to number");
        TCase *tc_mult_matrix_to_matrix = tcase_create("Testing multiplex matrix to matrix");
        // Добавляем все наши тесты в группу
        tcase_add_test(tc_math, eq_test_positive);
        tcase_add_test(tc_math, eq_test_negative);
        tcase_add_test (tc_math,eq_test_negative_and_positive);
        tcase_add_test (tc_math,create_matrix);
        tcase_add_test(tc_sum_matrix, incorrect_matrix_1);
        tcase_add_test(tc_sum_matrix, incorrect_matrix_2);
        tcase_add_test(tc_sum_matrix, incorrect_matrix_3);
        tcase_add_test(tc_sum_matrix, null_pointers_for_sum);
        tcase_add_test(tc_sum_matrix,sums_1);
        tcase_add_test(tc_mutl_to_num,mult_to_number_1);
        tcase_add_test(tc_mutl_to_num,mult_to_number_2);
        tcase_add_test(tc_mutl_to_num,mult_to_number_INFINITY);
        tcase_add_test(tc_mult_matrix_to_matrix,mult_matrix_1_by_1);
        tcase_add_test(tc_mult_matrix_to_matrix,mult_matrix_3_by_2_and_2_by_3);
        tcase_add_test(tc_mult_matrix_to_matrix,mult_matrix_10_by_2_and_2_by_7);
        tcase_add_test(tc_mult_matrix_to_matrix,mult_matrix_from_task);

        // Добавляем группу в набор
        suite_add_tcase(suite, tc_math);
        suite_add_tcase(suite,tc_sum_matrix);
        suite_add_tcase(suite,tc_mutl_to_num);
        suite_add_tcase(suite,tc_mult_matrix_to_matrix);
        // Создаём раннер (бегунок) для запуска тестов
        SRunner *runner = srunner_create(suite);
        // Запускаем тесты
        // CK_NORMAL - выводить результаты в консоль
        srunner_run_all(runner, CK_NORMAL);
        // Смотрим, сколько тестов упало
        int failed_count = srunner_ntests_failed(runner);
        // Освобождаем память
        srunner_free(runner);
        // Возвращаем 0 если всё хорошо, или 1 если есть ошибки
        return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
