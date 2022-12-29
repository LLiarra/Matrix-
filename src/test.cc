#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(constructor, customConstructor) {
  S21Matrix test_matrix(4, 6);
  EXPECT_EQ(4, test_matrix.GetRows());
  EXPECT_EQ(6, test_matrix.GetCols());
}

TEST(constructor, defaultConstructor) {
  S21Matrix test_matrix;
  EXPECT_EQ(9, test_matrix.GetRows());
  EXPECT_EQ(9, test_matrix.GetCols());
}

TEST(constructor, copyConstructor) {
  S21Matrix test_matrix(2, 2);
  test_matrix(0, 0) = 1;
  test_matrix(0, 1) = 2;
  test_matrix(1, 0) = 3;
  test_matrix(1, 1) = 4;
  S21Matrix other_matrix(test_matrix);
  EXPECT_EQ(2, other_matrix.GetRows());
  EXPECT_EQ(2, other_matrix.GetCols());
  double k = 1;
  for (int i = 0; i < other_matrix.GetRows(); i++) {
    for (int j = 0; j < other_matrix.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(other_matrix(i, j), k++);
    }
  }
}

TEST(constructor, moveConstructor) {
  S21Matrix test_matrix(2, 2);
  test_matrix(0, 0) = 1;
  test_matrix(0, 1) = 2;
  test_matrix(1, 0) = 3;
  test_matrix(1, 1) = 4;
  S21Matrix other_matrix(std::move(test_matrix));
  EXPECT_EQ(2, other_matrix.GetRows());
  EXPECT_EQ(2, other_matrix.GetCols());
  double k = 1;
  for (int i = 0; i < other_matrix.GetRows(); i++) {
    for (int j = 0; j < other_matrix.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(other_matrix(i, j), k++);
    }
  }
}

TEST(constructor, setGreaterRowDefault) {
  S21Matrix test_matrix;
  test_matrix.SetRows(15);
  EXPECT_EQ(15, test_matrix.GetRows());
  EXPECT_EQ(9, test_matrix.GetCols());
}

TEST(constructor, setLessRowDefault) {
  S21Matrix test_matrix;
  test_matrix.SetRows(3);
  EXPECT_EQ(3, test_matrix.GetRows());
  EXPECT_EQ(9, test_matrix.GetCols());
}

TEST(constructor, setLessRow) {
  S21Matrix test_matrix(10, 3);
  test_matrix.SetRows(3);
  EXPECT_EQ(3, test_matrix.GetRows());
  EXPECT_EQ(3, test_matrix.GetCols());
}

TEST(constructor, setGreaterRowD) {
  S21Matrix test_matrix(5, 10);
  test_matrix.SetRows(30);
  EXPECT_EQ(30, test_matrix.GetRows());
  EXPECT_EQ(10, test_matrix.GetCols());
}

TEST(constructor, setEqualRow) {
  S21Matrix test_matrix(5, 10);
  test_matrix.SetRows(5);
  EXPECT_EQ(5, test_matrix.GetRows());
  EXPECT_EQ(10, test_matrix.GetCols());
}

TEST(constructor, setGreaterColsDefault) {
  S21Matrix test_matrix(5, 10);
  test_matrix.SetCols(15);
  EXPECT_EQ(15, test_matrix.GetCols());
  EXPECT_EQ(5, test_matrix.GetRows());
}

TEST(constructor, setLessColsDefault) {
  S21Matrix test_matrix(5, 10);
  test_matrix.SetCols(3);
  EXPECT_EQ(3, test_matrix.GetCols());
  EXPECT_EQ(5, test_matrix.GetRows());
}

TEST(constructor, setLessEqualDefault) {
  S21Matrix test_matrix(1, 10);
  test_matrix.SetCols(10);
  EXPECT_EQ(10, test_matrix.GetCols());
  EXPECT_EQ(1, test_matrix.GetRows());
}

TEST(constructor, other_matrix) {
  S21Matrix test_matrix(1, 10);
  const S21Matrix& new_matrix(test_matrix);
  EXPECT_EQ(10, new_matrix.GetCols());
  EXPECT_EQ(1, new_matrix.GetRows());
}

TEST(constructor, other_matrixDefault) {
  S21Matrix test_matrix;
  const S21Matrix& new_matrix(test_matrix);
  EXPECT_EQ(9, new_matrix.GetCols());
  EXPECT_EQ(9, new_matrix.GetRows());
}

TEST(constructor, setMatrixCols) {
  S21Matrix test_matrix(2, 2);
  test_matrix.SetCols(3);
  EXPECT_DOUBLE_EQ(0.0, test_matrix(0, 2));
}

TEST(mulNmber, minMatrix) {
  S21Matrix test_matrix(1, 1);
  test_matrix(0, 0) = 3.3;
  double number = 3;
  test_matrix.MulNumber(number);
  EXPECT_DOUBLE_EQ(test_matrix(0, 0), 9.9);
}

TEST(mulNmber, bigMatrix) {
  S21Matrix test_matrix(20, 20);
  for (int i = 0; i < test_matrix.GetRows(); i++) {
    for (int j = 0; j < test_matrix.GetCols(); j++) {
      test_matrix(i, j) = 5;
    }
  }
  test_matrix.MulNumber(0.1);
  for (int i = 0; i < test_matrix.GetRows(); i++) {
    for (int j = 0; j < test_matrix.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(test_matrix(i, j), 0.5);
    }
  }
}

TEST(determinantMatrix, determinantNormal) {
  S21Matrix test_matrix(2, 2);
  test_matrix(0, 0) = 1.0;
  test_matrix(0, 1) = 2.0;
  test_matrix(1, 0) = 3.0;
  test_matrix(1, 1) = 5.0;
  double result = test_matrix.Determinant();
  EXPECT_DOUBLE_EQ(result, -1.0);
}

TEST(determinantMatrix, determinantNormal2) {
  S21Matrix test_matrix(2, 2);
  test_matrix(0, 0) = 11.0;
  test_matrix(0, 1) = -24.0;
  test_matrix(1, 0) = -101.0;
  test_matrix(1, 1) = 77.0;
  double result = test_matrix.Determinant();
  EXPECT_DOUBLE_EQ(result, -1577.0);
}

TEST(determinantMatrix, determinantNormal3) {
  S21Matrix test_matrix(4, 4);
  test_matrix(0, 0) = -8.0;
  test_matrix(0, 1) = 1.0;
  test_matrix(0, 2) = -1.0;
  test_matrix(0, 3) = 3.0;

  test_matrix(1, 0) = 3.0;
  test_matrix(1, 1) = -1.0;
  test_matrix(1, 2) = 4.0;
  test_matrix(1, 3) = -3.0;

  test_matrix(2, 0) = -14.0;
  test_matrix(2, 1) = 2.0;
  test_matrix(2, 2) = 5.0;
  test_matrix(2, 3) = 1.0;

  test_matrix(3, 0) = 5.0;
  test_matrix(3, 1) = 3.0;
  test_matrix(3, 2) = 1.0;
  test_matrix(3, 3) = -1.0;
  double result = test_matrix.Determinant();
  EXPECT_DOUBLE_EQ(result, 125.0);
}

TEST(determinantMatrix, determinantNormal4) {
  S21Matrix test_matrix(5, 5);
  test_matrix(0, 0) = 4.0;
  test_matrix(0, 1) = 1.0;
  test_matrix(0, 2) = 1.0;
  test_matrix(0, 3) = 2.0;
  test_matrix(0, 4) = 1.0;

  test_matrix(1, 0) = 1.0;
  test_matrix(1, 1) = 2.0;
  test_matrix(1, 2) = -1.0;
  test_matrix(1, 3) = 1.0;
  test_matrix(1, 4) = 1.0;

  test_matrix(2, 0) = 3.0;
  test_matrix(2, 1) = 1.0;
  test_matrix(2, 2) = 1.0;
  test_matrix(2, 3) = 1.0;
  test_matrix(2, 4) = 1.0;

  test_matrix(3, 0) = 2.0;
  test_matrix(3, 1) = 1.0;
  test_matrix(3, 2) = 1.0;
  test_matrix(3, 3) = 4.0;
  test_matrix(3, 4) = 1.0;

  test_matrix(4, 0) = 2.0;
  test_matrix(4, 1) = -1.0;
  test_matrix(4, 2) = 1.0;
  test_matrix(4, 3) = 1.0;
  test_matrix(4, 4) = 5.0;
  double result = test_matrix.Determinant();
  EXPECT_DOUBLE_EQ(result, 64.0);
}

TEST(complements_matrix, complementsNormal1) {
  S21Matrix test_matrix(3, 3);
  test_matrix(0, 0) = 1.0;
  test_matrix(0, 1) = 2.0;
  test_matrix(0, 2) = 3.0;

  test_matrix(1, 0) = 0.0;
  test_matrix(1, 1) = 4.0;
  test_matrix(1, 2) = 2.0;

  test_matrix(2, 0) = 5.0;
  test_matrix(2, 1) = 2.0;
  test_matrix(2, 2) = 1.0;

  S21Matrix complements_matrix(3, 3);
  complements_matrix(0, 0) = 0.0;
  complements_matrix(0, 1) = 10.0;
  complements_matrix(0, 2) = -20.0;

  complements_matrix(1, 0) = 4.0;
  complements_matrix(1, 1) = -14.0;
  complements_matrix(1, 2) = 8.0;

  complements_matrix(2, 0) = -8.0;
  complements_matrix(2, 1) = -2.0;
  complements_matrix(2, 2) = 4.0;
  S21Matrix other_matrix = test_matrix.CalcComplements();
  EXPECT_EQ(other_matrix.EqMatrix(complements_matrix), true);
}

TEST(complements_matrix, complementsNormal2) {
  S21Matrix test_matrix(3, 3);
  test_matrix(0, 0) = 101.0;
  test_matrix(0, 1) = 2.0;
  test_matrix(0, 2) = -4.0;

  test_matrix(1, 0) = 6.0;
  test_matrix(1, 1) = -3.0;
  test_matrix(1, 2) = 12.0;

  test_matrix(2, 0) = 5.0;
  test_matrix(2, 1) = -2.0;
  test_matrix(2, 2) = 3.0;

  S21Matrix complements_matrix(3, 3);
  complements_matrix(0, 0) = 15.0;
  complements_matrix(0, 1) = 42.0;
  complements_matrix(0, 2) = 3.0;

  complements_matrix(1, 0) = 2.0;
  complements_matrix(1, 1) = 323.0;
  complements_matrix(1, 2) = 212.0;

  complements_matrix(2, 0) = 12.0;
  complements_matrix(2, 1) = -1236.0;
  complements_matrix(2, 2) = -315.0;
  S21Matrix other_matrix = test_matrix.CalcComplements();
  EXPECT_EQ(other_matrix.EqMatrix(complements_matrix), true);
}

TEST(complements_matrix, complementsBig) {
  S21Matrix test_matrix(4, 4);
  test_matrix(0, 0) = 0.023;
  test_matrix(0, 1) = 124.161;
  test_matrix(0, 2) = -4.445;
  test_matrix(0, 3) = 0.123;

  test_matrix(1, 0) = 6.122;
  test_matrix(1, 1) = -3.023;
  test_matrix(1, 2) = 12.011;
  test_matrix(1, 3) = 4.112;

  test_matrix(2, 0) = 5.032;
  test_matrix(2, 1) = -2.120;
  test_matrix(2, 2) = 3.530;
  test_matrix(2, 3) = 1.222;

  test_matrix(3, 0) = 1.032;
  test_matrix(3, 1) = -3.120;
  test_matrix(3, 2) = 0.530;
  test_matrix(3, 3) = 8.34;

  S21Matrix complements_matrix(4, 4);
  complements_matrix(0, 0) = 120.198301;
  complements_matrix(0, 1) = 316.662458;
  complements_matrix(0, 2) = -17.408659;
  complements_matrix(0, 3) = 104.696500;

  complements_matrix(1, 0) = -3514.483058;
  complements_matrix(1, 1) = 181.479355;
  complements_matrix(1, 2) = 5056.050798;
  complements_matrix(1, 3) = 181.469446;

  complements_matrix(2, 0) = 12116.204486;
  complements_matrix(2, 1) = -209.216057;
  complements_matrix(2, 2) = -5814.710587;
  complements_matrix(2, 3) = -1208.019247;

  complements_matrix(3, 0) = -44.272415;
  complements_matrix(3, 1) = -63.492874;
  complements_matrix(3, 2) = -1640.619098;
  complements_matrix(3, 3) = 4811.423335;
  S21Matrix other_matrix = test_matrix.CalcComplements();
  EXPECT_EQ(other_matrix.EqMatrix(complements_matrix), true);
}

TEST(inverseMatrix, inverseNormal) {
  S21Matrix test_matrix(3, 3);
  test_matrix(0, 0) = 2.0;
  test_matrix(0, 1) = 5.0;
  test_matrix(0, 2) = 7.0;

  test_matrix(1, 0) = 6.0;
  test_matrix(1, 1) = 3.0;
  test_matrix(1, 2) = 4.0;

  test_matrix(2, 0) = 5.0;
  test_matrix(2, 1) = -2.0;
  test_matrix(2, 2) = -3.0;

  S21Matrix complements_matrix(3, 3);
  complements_matrix(0, 0) = 1.0;
  complements_matrix(0, 1) = -1.0;
  complements_matrix(0, 2) = 1.0;

  complements_matrix(1, 0) = -38.0;
  complements_matrix(1, 1) = 41.0;
  complements_matrix(1, 2) = -34.0;

  complements_matrix(2, 0) = 27.0;
  complements_matrix(2, 1) = -29.0;
  complements_matrix(2, 2) = 24.0;
  S21Matrix other_matrix = test_matrix.InverseMatrix();
  EXPECT_EQ(other_matrix.EqMatrix(complements_matrix), true);
  EXPECT_EQ(test_matrix.EqMatrix(complements_matrix), false);
}

TEST(inverseMatrix, inverseOneByOne) {
  S21Matrix test_matrix(1, 1);
  test_matrix(0, 0) = 5.0;

  S21Matrix inverse_matrix(1, 1);
  inverse_matrix(0, 0) = 0.2;

  S21Matrix other_matrix = test_matrix.InverseMatrix();
  EXPECT_EQ(other_matrix.EqMatrix(inverse_matrix), true);
}

TEST(inverseMatrix, inverseMul) {
  S21Matrix test_matrix(3, 3);
  test_matrix(0, 0) = 2.0;
  test_matrix(0, 1) = 5.0;
  test_matrix(0, 2) = 7.0;

  test_matrix(1, 0) = 6.0;
  test_matrix(1, 1) = 3.0;
  test_matrix(1, 2) = 4.0;

  test_matrix(2, 0) = 5.0;
  test_matrix(2, 1) = -2.0;
  test_matrix(2, 2) = -3.0;

  S21Matrix inverse_matrix(3, 3);
  inverse_matrix(0, 0) = 1.0;
  inverse_matrix(0, 1) = -1.0;
  inverse_matrix(0, 2) = 1.0;

  inverse_matrix(1, 0) = -38.0;
  inverse_matrix(1, 1) = 41.0;
  inverse_matrix(1, 2) = -34.0;

  inverse_matrix(2, 0) = 27.0;
  inverse_matrix(2, 1) = -29.0;
  inverse_matrix(2, 2) = 24.0;
  S21Matrix other_matrix = test_matrix.InverseMatrix();
  EXPECT_EQ(other_matrix.EqMatrix(inverse_matrix), true);

  S21Matrix resultMulMatrix(3, 3);
  resultMulMatrix(0, 0) = 1.0;
  resultMulMatrix(0, 1) = 0.0;
  resultMulMatrix(0, 2) = 0.0;

  resultMulMatrix(1, 0) = 0.0;
  resultMulMatrix(1, 1) = 1.0;
  resultMulMatrix(1, 2) = 0.0;

  resultMulMatrix(2, 0) = 0.0;
  resultMulMatrix(2, 1) = 0.0;
  resultMulMatrix(2, 2) = 1.0;

  inverse_matrix.MulMatrix(test_matrix);
  EXPECT_EQ(inverse_matrix.EqMatrix(resultMulMatrix), true);
}

TEST(EqualMatrix, NotEqualMatrix) {
  S21Matrix test_matrix(2, 3);
  test_matrix(0, 0) = 1.0;
  test_matrix(0, 1) = -1.0;
  test_matrix(0, 2) = 1.0;

  test_matrix(1, 0) = -38.0;
  test_matrix(1, 1) = 41.0;
  test_matrix(1, 2) = -34.0;

  S21Matrix test_matrix2(1, 4);
  test_matrix2(0, 0) = 0.023;
  test_matrix2(0, 1) = 124.161;
  test_matrix2(0, 2) = -4.445;
  test_matrix2(0, 3) = 0.123;
  EXPECT_EQ(test_matrix.EqMatrix(test_matrix2), false);
}

TEST(SumMatrix, SumNormalAndOverload) {
  S21Matrix test_matrix(2, 2);
  test_matrix(0, 0) = 1;
  test_matrix(0, 1) = 1;
  test_matrix(1, 0) = 1;
  test_matrix(1, 1) = 1;
  S21Matrix other_matrix(2, 2);
  other_matrix(0, 0) = 1;
  other_matrix(0, 1) = 1;
  other_matrix(1, 0) = 1;
  other_matrix(1, 1) = 1;
  test_matrix.SumMatrix(other_matrix);
  for (int i = 0; i < test_matrix.GetRows(); i++) {
    for (int j = 0; j < test_matrix.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(test_matrix(i, j), 2.0);
    }
  }
  S21Matrix overload_result = test_matrix + other_matrix;
  for (int i = 0; i < overload_result.GetRows(); i++) {
    for (int j = 0; j < overload_result.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(overload_result(i, j), 3.0);
    }
  }
  overload_result += other_matrix;
  for (int i = 0; i < overload_result.GetRows(); i++) {
    for (int j = 0; j < overload_result.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(overload_result(i, j), 4.0);
    }
  }
}

TEST(SubMatrix, SubNormalAndOverload) {
  S21Matrix test_matrix(2, 2);
  test_matrix(0, 0) = 4;
  test_matrix(0, 1) = 4;
  test_matrix(1, 0) = 4;
  test_matrix(1, 1) = 4;
  S21Matrix other_matrix(2, 2);
  other_matrix(0, 0) = 1;
  other_matrix(0, 1) = 1;
  other_matrix(1, 0) = 1;
  other_matrix(1, 1) = 1;
  test_matrix.SubMatrix(other_matrix);
  for (int i = 0; i < test_matrix.GetRows(); i++) {
    for (int j = 0; j < test_matrix.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(test_matrix(i, j), 3.0);
    }
  }
  S21Matrix overload_result = test_matrix - other_matrix;
  for (int i = 0; i < overload_result.GetRows(); i++) {
    for (int j = 0; j < overload_result.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(overload_result(i, j), 2.0);
    }
  }
  overload_result -= other_matrix;
  for (int i = 0; i < overload_result.GetRows(); i++) {
    for (int j = 0; j < overload_result.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(overload_result(i, j), 1.0);
    }
  }
}

TEST(MulNumber, MulNumberNormalAndOverload) {
  S21Matrix test_matrix(2, 2);
  test_matrix(0, 0) = 2;
  test_matrix(0, 1) = 2;
  test_matrix(1, 0) = 2;
  test_matrix(1, 1) = 2;
  double mul = 2;
  test_matrix.MulNumber(mul);
  for (int i = 0; i < test_matrix.GetRows(); i++) {
    for (int j = 0; j < test_matrix.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(test_matrix(i, j), 4.0);
    }
  }
  S21Matrix overload_result = test_matrix * mul;
  for (int i = 0; i < overload_result.GetRows(); i++) {
    for (int j = 0; j < overload_result.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(overload_result(i, j), 8.0);
    }
  }
  overload_result *= mul;
  for (int i = 0; i < overload_result.GetRows(); i++) {
    for (int j = 0; j < overload_result.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(overload_result(i, j), 16.0);
    }
  }
}

TEST(MulMatrix, MulNormalAndOverload) {
  S21Matrix test_matrix(2, 2);
  test_matrix(0, 0) = 3.0;
  test_matrix(0, 1) = -3.0;
  test_matrix(1, 0) = -1.0;
  test_matrix(1, 1) = 5.0;

  S21Matrix other_matrix(2, 2);
  other_matrix(0, 0) = 5.0;
  other_matrix(0, 1) = 3.0;
  other_matrix(1, 0) = 1.0;
  other_matrix(1, 1) = 3.0;

  S21Matrix mulResult(2, 2);
  mulResult(0, 0) = 12.0;
  mulResult(0, 1) = 0.0;
  mulResult(1, 0) = 0.0;
  mulResult(1, 1) = 12.0;
  test_matrix.MulMatrix(other_matrix);
  EXPECT_EQ(test_matrix == mulResult, true);

  S21Matrix test_matrix2(2, 2);
  test_matrix2(0, 0) = 3.0;
  test_matrix2(0, 1) = -3.0;
  test_matrix2(1, 0) = -1.0;
  test_matrix2(1, 1) = 5.0;
  S21Matrix mulResult2 = test_matrix2 * other_matrix;
  EXPECT_EQ(test_matrix == mulResult2, true);

  test_matrix2 *= other_matrix;
  EXPECT_EQ(test_matrix2 == test_matrix, true);
}

TEST(Exept, InvalidArgument) {
  EXPECT_THROW(S21Matrix test_matrix(-5, 0), std::invalid_argument);
}

TEST(Exept, InvalidIndex) {
  S21Matrix test_matrix(1, 1);
  EXPECT_ANY_THROW(test_matrix(2, 2));
}

TEST(Exept, DifferentDimensions) {
  S21Matrix test_matrix(1, 1);
  S21Matrix test_matrix2(5, 13);
  EXPECT_ANY_THROW(test_matrix2.SumMatrix(test_matrix));
  EXPECT_ANY_THROW(test_matrix2.SubMatrix(test_matrix));
  EXPECT_ANY_THROW(test_matrix2.MulMatrix(test_matrix));
}

TEST(Exept, IsnotSquare) {
  S21Matrix test_matrix(2, 3);
  S21Matrix test_matrix2(5, 13);
  EXPECT_ANY_THROW(test_matrix.Determinant());
  EXPECT_ANY_THROW(test_matrix2.CalcComplements());

  S21Matrix test_matrix3(2, 2);
  test_matrix(0, 0) = 2.0;
  test_matrix(0, 1) = 6.0;
  test_matrix(1, 0) = 6.0;
  test_matrix(1, 1) = 2.0;
  EXPECT_ANY_THROW(S21Matrix result = test_matrix3.InverseMatrix());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}