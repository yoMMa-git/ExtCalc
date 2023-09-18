CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
OS = $(shell uname)
TEST_FILE_NAME = s21_tests.c
POLISH_FILE_NAMES = back/polish/*.c

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm	
endif

all: gcov_report

install:
	cd back; make install 
	cd back; mv s21_SmartCalc ../

uninstall:
	cd back; make uninstall
	rm -rf s21_SmartCalc 

dist: 
	tar --totals -cvf s21_SmartCalc.tar back front
	
dvi:
	doxygen Doxyfile 2> /dev/null && open doxygen/html/index.html 2> /dev/null
		
test: $(TEST_FILE_NAME)
	$(CC) $(CFLAGS) $(TEST_FILE_NAME) $(POLISH_FILE_NAMES) -o test --coverage $(TEST_LIBS)
	./test

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html 2> /dev/null

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt test.info test.dSYM
	cd back; make clean

clang_n:
	clang-format -n --style=Google *.[ch] 
	clang-format -n --style=Google ./back/*.[ch] ./back/*.cpp 
	clang-format -n --style=Google ./back/calc/*.[ch] ./back/calc/*.cpp 
	clang-format -n --style=Google ./back/credit/*.[ch] ./back/credit/*.cpp 
	clang-format -n --style=Google ./back/deposit/*.[ch] ./back/deposit/*.cpp 
	clang-format -n --style=Google ./back/graphics/*.[ch] ./back/graphics/*.cpp 
	clang-format -n --style=Google ./back/polish/*.[ch] 

clang_i:
	clang-format -i --style=Google *.[ch]
	clang-format -i --style=Google ./back/*.[h]
	clang-format -i --style=Google ./back/calc/*.[h] ./back/calc/*.cpp 
	clang-format -i --style=Google ./back/credit/*.[h] ./back/credit/*.cpp 
	clang-format -i --style=Google ./back/deposit/*.[h] ./back/deposit/*.cpp 
	clang-format -i --style=Google ./back/graphics/*.[h] ./back/graphics/*.cpp 
	clang-format -i --style=Google ./back/polish/*.[ch]
