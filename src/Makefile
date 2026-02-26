
all: s21_matrix.a test 

s21_matrix.o: s21_matrix.c s21_matrix.h
	gcc -c s21_matrix.c -o s21_matrix.o

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o

test: s21_matrix.a
	gcc tests/main_test.c tests/tests.c s21_matrix.a -lcheck -lm -lsubunit -o run_tests 
	valgrind --tool=memcheck --leak-check=full  ./run_tests

gcov_report:

clean:
	rm -rf *.o *.a run_tests s21_matrix


