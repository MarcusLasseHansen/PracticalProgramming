#include "linalg.hpp"

namespace pracprog {

vector &vector::operator+=(const vector &other) {
  if (this->size() != other.size())
    throw std::invalid_argument(
        "Vector addition error: incompatible vector sizes (" +
        std::to_string(this->size()) + " vs " + std::to_string(other.size()) +
        ")");
  for (size_t i = 0; i < data.size(); i++)
    data[i] += other[i];
  return *this;
}

vector &vector::operator-=(const vector &other) {
  if (this->size() != other.size())
    throw std::invalid_argument(
        "Vector subtraction error: incompatible vector sizes (" +
        std::to_string(this->size()) + " vs " + std::to_string(other.size()) +
        ")");

  for (size_t i = 0; i < data.size(); i++)
    data[i] -= other[i];
  return *this;
}

vector &vector::operator*=(const double scalar) {
  for (auto &x : data)
    x *= scalar;
  return *this;
}

vector &vector::operator/=(const double scalar) {
  for (auto &x : data)
    x /= scalar;
  return *this;
}

double vector::dot(const vector &other) const {
  if (this->size() != other.size())
    throw std::invalid_argument(
        "Dot product error: incompatible vector sizes (" +
        std::to_string(this->size()) + " vs " + std::to_string(other.size()) +
        ")");
  double result = 0.0;
  for (size_t i = 0; i < data.size(); i++)
    result += data[i] * other[i];
  return result;
}

double vector::norm() const { return std::sqrt(dot(*this)); }

vector vector::normalized() const { return *this / norm(); }

std::ostream &operator<<(std::ostream &os, const vector &v) {
  os << "[";
  for (size_t i = 0; i < v.size(); i++) {
    os << " ";
    os << v[i];
  }
  os << " ]\n";
  return os;
}

vector operator-(const vector &v) {
  vector result(v.size());
  for (size_t i = 0; i < v.size(); i++)
    result[i] = -v[i];
  return result;
}

vector operator+(const vector &a, const vector &b) {
  vector result(a);
  result += b;
  return result;
}

vector operator-(const vector &a, const vector &b) {
  vector result(a);
  result -= b;
  return result;
}

vector operator*(const vector &v, double scalar) {
  vector result(v);
  result *= scalar;
  return result;
}

vector operator*(double scalar, const vector &v) { return v * scalar; }

vector operator/(const vector &v, double scalar) {
  vector result(v);
  result /= scalar;
  return result;
}

matrix matrix::identity(size_t n) {
  matrix I(n, n);
  for (size_t i = 0; i < n; i++)
    I(i, i) = 1.0;
  return I;
}

pracprog::vector matrix::row(size_t i) const {
  pracprog::vector r(cols());
  for (size_t j = 0; j < cols(); j++)
    r[j] = elements[j][i];
  return r;
}

matrix &matrix::operator+=(const matrix &B) {
  for (size_t j = 0; j < cols(); j++)
    elements[j] += B.elements[j];
  return *this;
}

matrix &matrix::operator-=(const matrix &B) {
  for (size_t j = 0; j < cols(); j++)
    elements[j] -= B.elements[j];
  return *this;
}

matrix &matrix::operator*=(double s) {
  for (size_t j = 0; j < cols(); j++)
    elements[j] *= s;
  return *this;
}

matrix matrix::transpose() const {
  matrix T(cols(), rows());
  for (size_t i = 0; i < rows(); i++)
    for (size_t j = 0; j < cols(); j++)
      T(j, i) = (*this)(i, j);
  return T;
}

void matrix::swap_cols(size_t j1, size_t j2) {
  std::swap(elements[j1], elements[j2]);
}

double matrix::det() const {
  if (!this->is_square())
    throw std::invalid_argument("Determinant called on a non-square matrix");
  size_t n = rows();
  if (n == 1)
    return (*this)(0, 0);

  if (n == 2)
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);

  double result = 0.0;
  for (size_t j = 0; j < n; j++) {
    matrix minor(n - 1, n - 1);
    for (size_t row = 1; row < n; row++) {
      size_t col_minor = 0;
      for (size_t col = 0; col < n; col++) {
        if (col == j)
          continue;
        minor(row - 1, col_minor++) = (*this)(row, col);
      }
    }

    double cofactor = ((j % 2 == 0) ? 1.0 : -1.0) * minor.det();
    result += (*this)(0, j) * cofactor;
  }

  return result;
}

matrix operator+(matrix A, const matrix &B) { return A += B; }
matrix operator-(matrix A, const matrix &B) { return A -= B; }
matrix operator*(matrix A, double s) { return A *= s; }
matrix operator*(double s, matrix A) { return A *= s; }

pracprog::vector operator*(const matrix &A, const pracprog::vector &x) {
  pracprog::vector result(A.rows());
  for (size_t j = 0; j < A.cols(); j++)
    result += A.col(j) * x[j];
  return result;
}

matrix operator*(const matrix &A, const matrix &B) {
  matrix C(A.rows(), B.cols());
  for (size_t j = 0; j < B.cols(); j++)
    C.col(j) = A * B.col(j);
  return C;
}

std::ostream &operator<<(std::ostream &os, const matrix &M) {
  for (size_t i = 0; i < M.rows(); i++) {
    os << "[ ";
    for (size_t j = 0; j < M.cols(); j++)
      os << M(i, j) << (j + 1 < M.cols() ? ", " : "");
    os << " ]\n";
  }
  return os;
}

bool approx_equal(const double &a, const double &b, double tol) {
  return std::abs(a - b) <= tol * std::max({std::abs(a), std::abs(b), 1.0});
}

bool approx_equal(const vector &a, const vector &b, double tol) {
  if (a.size() != b.size())
    return false;
  for (size_t i = 0; i < a.size(); i++)
    if (!approx_equal(a[i], b[i], tol))
      return false;
  return true;
}

bool approx_equal(const matrix &A, const matrix &B, double tol) {
  if (A.cols() != B.cols())
    return false;
  for (size_t j = 0; j < A.cols(); j++)
    if (!approx_equal(A.col(j), B.col(j), tol))
      return false;
  return true;
}

} /* namespace pracprog */
