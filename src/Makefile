CC=g++
FLAGS=-Wall -Wextra -Werror -g
GCOV=-coverage
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	TEST_FLAGS=-lgtest -lpthread
else
	TEST_FLAGS=--lgtest -pthread
endif

#SRC
SRC_FILES=s21_matrix_oop.cc

#OBJ
OBJ=$(notdir $(SRC_FILES:.cc=.o))

#DIRECTORY
OBJ_DIR=./objects

#INCLUDES
INCLUDE=s21_matrix_oop.h

vpath %.o $(OBJ_DIR)

.PHONY: all clean test gcov_report

all: s21_matrix_oop.a

%.o: %.cc $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $(addprefix $(OBJ_DIR)/, $@)

s21_matrix_oop.a: $(OBJ) $(INCLUDE)
	ar rcs $@ $(addprefix $(OBJ_DIR)/, $(OBJ))
	ranlib $@

test: s21_matrix_oop.a
	$(CC) $(FLAGS) test.cc $(TEST_FLAGS) s21_matrix_oop.a -o s21_test
	./s21_test

gcov_report:FLAGS += $(GCOV)
gcov_report: clean test
	./s21_test
	lcov -t "gcov_report" --no-external -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

clang:
	bash style.sh
	cppcheck --std=c++17 --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h

valgrind: test
ifeq ($(UNAME), Linux)
	valgrind --leak-check=full ./s21_test
else
	leaks --atExit -- ./s21_test
endif

clean:
	rm -rf objects s21_test report *.gcda *.gcno *.info s21_matrix_oop.a

rebuild: clean all