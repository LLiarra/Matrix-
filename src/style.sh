#!/bin/bash

cp ../materials/linters/.clang-format .

clang-format -n s21_matrix_oop.h  s21_matrix_oop.cc test.cc

clang-format -i s21_matrix_oop.h s21_matrix_oop.cc test.cc

rm .clang-format


