CC				=	gcc
CFLAGS			=	-std=c11 -Wall -Werror -Wextra -g
SOURCES			=	s21_*.c
HEADER			= 	s21_matrix.h
OS 				= 	$(shell uname)
TEST_FILE_NAME 	= 	tests/unit_tests.c

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm
endif

all: gcov_report

s21_matrix.a: objects
	ar rcs s21_matrix.a *.o
	ranlib s21_matrix.a
	rm -rf *.o

objects:
	$(CC) $(CFLAGS) -c $(SOURCES)

test: clean
	clear
	$(CC) $(CFLAGS) -c $(SOURCES) -fprofile-arcs -ftest-coverage -lgcov
	ar rcs s21_matrix.a *.o
	ranlib s21_matrix.a
	rm -rf *.o
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage -lgcov $(TEST_FILE_NAME) s21_matrix.a -o test $(TEST_LIBS)
	valgrind --track-origins=yes --tool=memcheck --leak-check=yes --show-leak-kinds=all ./test
	# ./test

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info

valgrind_check: test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all test

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt test.info test.dSYM

clang:
	clang-format -n -style=Google *.c *.h
	clang-format -n -style=Google tests/*.c tests/*.h