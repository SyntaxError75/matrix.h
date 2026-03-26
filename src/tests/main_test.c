
#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Suite *suite(void);

int main() {
  SRunner *runner = srunner_create(suite());

  // Запускаем тесты
  srunner_run_all(runner, CK_NORMAL);

  // Смотрим, сколько тестов упало
  int failed_count = srunner_ntests_failed(runner);

  // Освобождаем память
  srunner_free(runner);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}