#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  this->rows_ = 9;
  this->cols_ = 9;
  CreateMatrix_();
}

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows_ = rows;
  this->cols_ = cols;
  CreateMatrix_();
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  CreateMatrix_();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { RemoveMatrix_(); }

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows != rows_) {
    S21Matrix new_matrix(rows, cols_);
    int min = rows_ < rows ? rows_ : rows;
    CopyMatrix_(new_matrix, min, cols_);
    if (matrix_) {
      this->RemoveMatrix_();
    }
    *this = new_matrix;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols != cols_) {
    S21Matrix new_matrix(rows_, cols);
    int min = cols_ < cols ? cols_ : cols;
    CopyMatrix_(new_matrix, rows_, min);
    if (matrix_) {
      this->RemoveMatrix_();
    }
    *this = new_matrix;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    result = false;
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > EPS) {
          result = false;
        }
        if (!result) {
          break;
        }
      }
      if (!result) {
        break;
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  MatrixDimensionCompare(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  MatrixDimensionCompare(other);
  if (this->matrix_ != nullptr && other.matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= num;
      }
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument(
        "the number of columns of the first matrix "
        "is not equal to the number of rows of the second matrix");
  }
  S21Matrix temp(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      temp.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = temp;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw std::invalid_argument("the matrix is not square");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < rows_; i++) {
      int negative = i % 2 ? -1 : 1;
      for (int j = 0; j < cols_; j++) {
        S21Matrix temp_matrix(rows_ - 1, cols_ - 1);
        CreateMinorMatrix_(i, j, temp_matrix);
        double temp = temp_matrix.GetDeterminant_(rows_ - 1);
        result.matrix_[i][j] = negative * temp;
        negative *= (-1);
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw std::invalid_argument("the matrix is not square");
  }
  return GetDeterminant_(rows_);
}

double S21Matrix::GetDeterminant_(int size) {
  double determinant = 0.0;
  int negative = 1;
  if (rows_ == 1) {
    determinant = this->matrix_[0][0];
  } else if (size == 2) {
    determinant = this->matrix_[0][0] * this->matrix_[1][1] -
                  (this->matrix_[0][1] * this->matrix_[1][0]);
  } else if (size > 2) {
    S21Matrix new_matrix(*this);
    for (int j = 0; j < size; j++) {
      CreateMinorMatrix_(0, j, new_matrix);
      determinant +=
          negative * (matrix_[0][j] * new_matrix.GetDeterminant_(size - 1));
      negative *= (-1);
    }
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (fabs(det) < EPS) {
    throw std::invalid_argument("matrix determinant is 0");
  }
  S21Matrix result = this->CalcComplements();
  result = result.Transpose();

  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = result.matrix_[i][j] / det;
    }
  }
  return result;
}

/*
 * utility
 */
void S21Matrix::CreateMatrix_() {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument(
        "the value cannot be less than or equal to zero");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < this->rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::RemoveMatrix_() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::CreateMinorMatrix_(int rows, int cols, S21Matrix& other) {
  int offset_row = 0;
  for (int i = 0; i < rows_ - 1; i++) {
    if (i == rows) {
      offset_row = 1;
    }
    int offset_column = 0;
    for (int j = 0; j < rows_ - 1; j++) {
      if (j == cols) {
        offset_column = 1;
      }
      other.matrix_[i][j] = matrix_[i + offset_row][j + offset_column];
    }
  }
}

void S21Matrix::CopyMatrix_(S21Matrix& other, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      other.matrix_[i][j] = this->matrix_[i][j];
    }
  }
}

void S21Matrix::MatrixDimensionCompare(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("different matrix dimensions");
  }
}

/*
 * overload
 */
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double& number) {
  S21Matrix result(*this);
  result.MulNumber(number);
  return result;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double& number) {
  this->MulNumber(number);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    if (matrix_) {
      this->RemoveMatrix_();
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix_();
    if (matrix_ != nullptr) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          this->matrix_[i][j] = other.matrix_[i][j];
        }
      }
    }
  }
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= this->rows_ || col >= this->cols_) {
    throw std::out_of_range("index is outside the matrix");
  }
  return this->matrix_[row][col];
}
