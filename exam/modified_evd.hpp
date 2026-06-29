#pragma once
#include "../homework/linalg/linalg.hpp" // linear algebra base class

namespace pracprog {
class modified_evd {
private:
  pracprog::vector w;

public:
  const vector &getw() const { return w; }
  vector &getw() { return w; }

  modified_evd(matrix A) : w(A.cols()) {
    const size_t n = A.cols();
    if (n == 0)
      return;

    constexpr double eps = 1e-12;
    double normsq = 0.0;
    for (size_t i = 0; i < n; ++i) {
      normsq += A(i, i) * A(i, i);
      if (i + 1 < n)
        normsq += 2.0 * A(i, i + 1) * A(i, i + 1);
    }
    const double tol = eps * std::sqrt(normsq);
    unsigned int iter = 0;
    const size_t max_iter = 30 * n;
    bool converged = (n <= 1);
    while (!converged && iter < max_iter) {
      converged = true;
      for (size_t p = 0; p < n - 1; ++p) {
        const size_t q = p + 1;
        if (std::abs(A(p, q)) <= tol)
          continue;
        converged = false;
        const double apq = A(p, q);
        const double app = A(p, p);
        const double aqq = A(q, q);
        double c, s;
        double tau = (aqq - app) / (2.0 * apq);
        double t = (tau >= 0.0 ? 1.0 : -1.0) /
                   (std::abs(tau) + std::sqrt(1.0 + tau * tau));
        c = 1.0 / std::sqrt(1.0 + t * t);
        s = t * c;

        for (size_t i = 0; i < n; ++i) {
          if (i == p || i == q)
            continue;
          const double aip = A(i, p), aiq = A(i, q);
          if (aip == 0.0 && aiq == 0.0)
            continue;
          A(i, p) = c * aip - s * aiq;
          A(p, i) = A(i, p);
          A(i, q) = c * aiq + s * aip;
          A(q, i) = A(i, q);
        }

        A(p, p) = c * c * app - 2.0 * c * s * apq + s * s * aqq;
        A(q, q) = s * s * app + 2.0 * c * s * apq + c * c * aqq;
        A(p, q) = 0.0;
        A(q, p) = 0.0;
      }
      ++iter;
    }

    for (size_t i = 0; i < n; ++i)
      w[i] = A(i, i);
    for (size_t i = 0; i + 1 < n; ++i) {
      size_t k = i;
      for (size_t j = i + 1; j < n; ++j)
        if (w[j] < w[k])
          k = j;
      if (k != i)
        std::swap(w[i], w[k]);
    }
  }

  static void timesJ(pracprog::matrix &A, int p, int q, double theta) {
    double c = std::cos(theta), s = std::sin(theta);
    for (size_t i = 0; i < A.rows(); i++) {
      double aip = A(i, p), aiq = A(i, q);
      A(i, p) = c * aip - s * aiq;
      A(i, q) = s * aip + c * aiq;
    }
  }
  static void Jtimes(pracprog::matrix &A, int p, int q, double theta) {
    double c = std::cos(theta), s = std::sin(theta);
    for (size_t j = 0; j < A.rows(); j++) {
      double apj = A(p, j), aqj = A(q, j);
      A(p, j) = c * apj + s * aqj;
      A(q, j) = -s * apj + c * aqj;
    }
  }
};

} /* namespace pracprog */
