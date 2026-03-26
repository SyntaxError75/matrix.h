CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
CFLAGS_TEST = -Wall -Wextra -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lcheck -lm -lsubunit

SOURCES = matrix.c matrix_utils.c
OBJ = $(SOURCES:.c=.o)

all: matrix.a

matrix.a: $(OBJ)
	ar rcs $@ $^
	ranlib $@

matrix.o: matrix.c matrix.h matrix_utils.h
	$(CC) $(CFLAGS) -c matrix.c -o matrix.o

matrix_utils.o: matrix_utils.c matrix_utils.h matrix.h
	$(CC) $(CFLAGS) -c matrix_utils.c -o matrix_utils.o



test: matrix.a
	$(CC) $(CFLAGS_TEST) tests/main_test.c tests/tests.c matrix.a $(LIBS) -o run_tests
	./run_tests

test_valgrind: test
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./run_tests

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all ./run_tests 2>&1 | grep -E "definitely lost|indirectly lost|possibly lost|ERROR SUMMARY"

format:
	clang-format -n -style=Google *.c *.h tests/*.c
	clang-format -i -style=Google *.c *.h tests/*.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h tests/*.c

gcov_report: clean
	mkdir -p report
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SOURCES) tests/main_test.c tests/tests.c $(LIBS) -o run_tests
	./run_tests
	gcovr --root . --html --html-details -o report/coverage.html --exclude 'tests/'
	rm -f *.gcda *.gcno
	rm -f run_tests

clean:
	rm -rf *.o *.a run_tests report *.gcda *.gcno *.info

rebuild: clean all

.PHONY: all clean test test_valgrind gcov_report rebuild format cppcheck matrix.a
