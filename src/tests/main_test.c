
#include "tests.c"
#include <stdio.h>
#include <math.h>
#include <check.h>
int main (){
        // Создаём набор тестов
        Suite *suite = suite_create("Math Tests");
        // Создаём группу тестов (можно называть как угодно)
        TCase *tc_math = tcase_create("Simple Math");
        // Добавляем все наши тесты в группу
        tcase_add_test(tc_math, eq_test_positive);
        tcase_add_test(tc_math, eq_test_negative);
        tcase_add_test (tc_math,eq_test_negative_and_positive);
        // Добавляем группу в набор
        suite_add_tcase(suite, tc_math);
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
