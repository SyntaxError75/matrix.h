
all: matrix.a test

matrix.o: matrix.c matrix.h
	gcc -c matrix.c -o matrix.o

matrix.a: matrix.o
	ar rcs matrix.a matrix.o

test: matrix.a
	gcc tests/main_test.c tests/tests.c matrix.a -lcheck -lm -lsubunit -o run_tests
	./run_tests

gcov_report:

clean:
	rm -rf *.o *.a run_tests matrix


