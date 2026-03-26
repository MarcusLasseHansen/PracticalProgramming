#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

// This course will only work with linear algebra using doubles, therefore
// templating is foregone.
namespace pracprog {
class vector {
private:
  std::vector<double> data;

public:
  vector(const size_t n) : data(n, 0.0) {}
  vector(const size_t n, const double val) : data(n, val) {}
  vector(const vector &other) : data(other.data) {}
  size_t size() const { return data.size(); }
  double &operator[](size_t i) { return data[i]; }
  double operator[](size_t i) const { return data[i]; }
  auto begin() { return data.begin(); }
  auto end() { return data.end(); }
  auto begin() const { return data.begin(); }
  auto end() const { return data.end(); }

  vector &operator+=(const vector &);
  vector &operator-=(const vector &);
  vector &operator*=(const double);
  vector &operator/=(const double);
  vector &operator=(const vector &) = default;

  double dot(const vector &) const;
  double norm() const;
  vector normalized() const;

  friend std::ostream &operator<<(std::ostream &, const vector &);
};

vector operator-(const vector &);
vector operator-(const vector &, const vector &);
vector operator+(const vector &, const vector &);
vector operator*(const vector &, double);
vector operator*(double, const vector &);
vector operator/(const vector &, double);

/*
 * Note: This implementation breaks memory locality since our vectors may not
 *       be in the same place in memory. This is okay because our algorithms
 *       in this course will never work with rows, only with columns.
 */
class matrix {
private:
  std::vector<pracprog::vector> elements; // column-major - elements[col][row]
public:
  matrix(size_t rows, size_t cols) : elements(cols, pracprog::vector(rows)) {}
  matrix(size_t rows, size_t cols, double val)
      : elements(cols, pracprog::vector(rows, val)) {}
  matrix(const matrix &other) : elements(other.elements) {}

  static matrix identity(size_t n);

  size_t rows() const { return elements.empty() ? 0 : elements[0].size(); }
  size_t cols() const { return elements.size(); }
  bool is_square() const { return rows() == cols(); }

  double &operator()(size_t i, size_t j) { return elements[j][i]; }
  double operator()(size_t i, size_t j) const { return elements[j][i]; }

  pracprog::vector &col(size_t j) { return elements[j]; }
  const pracprog::vector &col(size_t j) const { return elements[j]; }

  pracprog::vector row(size_t i) const;

  matrix &operator+=(const matrix &B);

  matrix &operator-=(const matrix &B);

  matrix &operator*=(double s);

  matrix transpose() const;

  void swap_cols(size_t j1, size_t j2);

  double det() const;

  friend std::ostream &operator<<(std::ostream &os, const matrix &M);
};

matrix operator+(matrix, const matrix &);
matrix operator-(matrix, const matrix &);
matrix operator*(matrix, double);
matrix operator*(double, matrix);

pracprog::vector operator*(const matrix &, const pracprog::vector &);

matrix operator*(const matrix &, const matrix &);

bool approx_equal(const double &a, const double &b, double tol = 1e-10);

bool approx_equal(const vector &a, const vector &b, double tol = 1e-10);

bool approx_equal(const matrix &A, const matrix &B, double tol = 1e-10);
} /* namespace pracprog */
