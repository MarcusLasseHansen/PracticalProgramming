#include "linalg_evd.hpp"

namespace pracprog {
/* NB: stolen from homework assignment    */
void evd::timesJ(pracprog::matrix &A, int p, int q, double theta) {
  double c = std::cos(theta), s = std::sin(theta);
  for (size_t i = 0; i < A.rows(); i++) {
    double aip = A(i, p), aiq = A(i, q);
    A(i, p) = c * aip - s * aiq;
    A(i, q) = s * aip + c * aiq;
  }
}

/* NB: stolen from homework assignment    */
void evd::Jtimes(pracprog::matrix &A, int p, int q, double theta) {
  double c = std::cos(theta), s = std::sin(theta);
  for (size_t j = 0; j < A.rows(); j++) {
    double apj = A(p, j), aqj = A(q, j);
    A(p, j) = c * apj + s * aqj;
    A(q, j) = -s * apj + c * aqj;
  }
}

evd::evd(matrix A) : V(matrix::identity(A.cols())), w(A.cols()) {
  if (A.rows() != A.cols())
    throw std::invalid_argument("EVD error: Non-square matrix passed ( cols: " +
                                std::to_string(A.cols()) +
                                " vs rows: " + std::to_string(A.rows()) + " )");
  constexpr double eps = 1e-12;
  size_t n = A.cols();
  double norm = 0.0;
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < n; ++j)
      norm += A(i, j) * A(i, j);
  norm = std::sqrt(norm);
  double tol = eps * norm;
  size_t max_iter = 10 * n * n * n;
  size_t iter = 0;
  bool converged = false;

  while (!converged && iter < max_iter) {
    converged = true;
    for (size_t p = 0; p < n - 1; ++p) {
      for (size_t q = p + 1; q < n; ++q) {
        double apq = A(p, q);

        if (std::abs(apq) > tol) {
          converged = false;
          double app = A(p, p);
          double aqq = A(q, q);

          double tau = (aqq - app) / (2.0 * apq);
          double t = (tau >= 0.0 ? 1.0 : -1.0) /
                     (std::abs(tau) + std::sqrt(1.0 + tau * tau));
          double c = 1.0 / std::sqrt(1.0 + t * t);
          double s = t * c;

          for (size_t i = 0; i < n; ++i) {
            if (i != p && i != q) {
              double aip = A(i, p);
              double aiq = A(i, q);
              A(i, p) = c * aip - s * aiq;
              A(p, i) = A(i, p);
              A(i, q) = c * aiq + s * aip;
              A(q, i) = A(i, q);
            }
          }

          double app_new = c * c * app - 2.0 * c * s * apq + s * s * aqq;
          double aqq_new = s * s * app + 2.0 * c * s * apq + c * c * aqq;
          A(p, p) = app_new;
          A(q, q) = aqq_new;
          A(p, q) = 0.0;
          A(q, p) = 0.0;

          for (size_t i = 0; i < n; ++i) {
            double vip = V(i, p);
            double viq = V(i, q);
            V(i, p) = c * vip - s * viq;
            V(i, q) = s * vip + c * viq;
          }
        }
      }
    }

    iter++;
  }

  for (size_t i = 0; i < n; ++i)
    w[i] = A(i, i);

  for (size_t i = 0; i < n - 1; ++i) {
    size_t k = i;
    for (size_t j = i + 1; j < n; ++j) {
      if (w[j] < w[k]) {
        k = j;
      }
    }
    if (k != i) {
      std::swap(w[i], w[k]);
      V.swap_cols(i, k);
    }
  }
}

} /* namespace pracprog */
