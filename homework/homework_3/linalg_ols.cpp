#include "linalg_ols.hpp"

namespace pracprog {
std::pair<pracprog::vector, pracprog::matrix>
lsfit(const std::vector<std::function<double(double)>> &fs,
      const pracprog::vector &x, const pracprog::vector &y,
      const pracprog::vector &dy) {
  const size_t row_num = y.size();
  const size_t col_num = fs.size();
  pracprog::matrix A(row_num, col_num);
  pracprog::vector b(row_num);
  for (size_t col = 0; col < col_num; col++) {
    for (size_t row = 0; row < row_num; row++) {
      A(row, col) = fs[col](x[row]) / dy[row];
    }
  }
  for (size_t row = 0; row < row_num; row++) {
    b[row] = y[row] / dy[row];
  }

  pracprog::qr QR(A);
  const auto& R = QR.R;
  // Covariance matrix calculated as R_inv * R_inv^T
  // R_inv is gotten from back substitution since
  // R is triangular. Should be the fastest way we can do it
  matrix R_inv(col_num, col_num);
  for (int i = col_num - 1; i >= 0; i--) {
    R_inv(i, i) = 1.0 / R(i, i);
    for (size_t j = i + 1; j < col_num; j++) {
      double sum = 0.0;
      for (size_t k = i + 1; k <= j; k++) {
        sum += R(i, k) * R_inv(k, j);
      }
      R_inv(i, j) = -sum / R(i, i);
    }
  }
  
  return std::make_pair(QR.solve(b), R_inv*R_inv.transpose());
}

} /* namespace pracprog */
