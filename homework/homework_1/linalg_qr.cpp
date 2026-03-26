#include "linalg_qr.hpp"

namespace pracprog {
void qr::decompose() {
  for (size_t i = 0; i < Q.cols(); ++i) {
    R(i, i) = Q.col(i).norm();
    Q.col(i) /= R(i, i);
    for (size_t j = i + 1; j < Q.cols(); ++j) {
      R(i, j) = Q.col(i).dot(Q.col(j));
      Q.col(j) -= Q.col(i) * R(i, j);
    }
  }
}

// solves Ax=b <=> QRx=b <=> Rx=Q(^T)b=y
vector qr::solve(const vector &b) const {
  vector y = this->Q.transpose() * b;
  for (int i = y.size() - 1; i >= 0; i--) {
    double sum = 0;
    for (unsigned int k = i + 1; k < y.size(); k++) {
      sum += this->R(i, k) * y[k];
    }
    y[i] = (y[i] - sum) / this->R(i, i);
  }
  return y;
}

double qr::det() const {
  double determinant = R(0, 0);
  for (unsigned int i = 1; i < this->R.cols(); ++i) {
    determinant *= R(i, i);
  }
  return determinant;
}

matrix qr::inverse() const {
  if (!this->Q.is_square())
     throw std::invalid_argument("Inverse called on a non-square matrix");
  const size_t size = this->Q.cols();
  matrix inverse_matrix(size,size);
  matrix identity_matrix = matrix::identity(size);
  for (unsigned int i = 0; i < size; i++) {
    inverse_matrix.col(i) = this->solve(identity_matrix.col(i));
  }
  return inverse_matrix;
}
} /* namespace pracprog */
