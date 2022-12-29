#ifndef CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H
#include <cmath>
#include <exception>
#include <iostream>
#define EPS 1e-6

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double& number);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double& number);
  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  double& operator()(int row, int col);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

 private:
  int rows_, cols_;
  double** matrix_;
  void CreateMatrix_();
  void RemoveMatrix_();
  void CreateMinorMatrix_(int rows, int cols, S21Matrix& other);
  void CopyMatrix_(S21Matrix& other, int rows, int cols);
  double GetDeterminant_(int size);
  void MatrixDimensionCompare(const S21Matrix& other);
};

#endif  // CPP1_S21_MATRIXPLUS_0_S21_MATRIX_OOP_H
