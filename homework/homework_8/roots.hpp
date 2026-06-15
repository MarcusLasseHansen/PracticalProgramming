#pragma once
#include "../homework_1/linalg_qr.hpp"
#include "../linalg/linalg.hpp"
#include <functional>

namespace pracprog {
// updated to reuse the matrix for exercise C
void Jacobian(const std::function<pracprog::vector(pracprog::vector &)> &f,
              pracprog::vector x, const pracprog::vector &fx,
              pracprog::matrix &J, const size_t &n) {
  pracprog::vector dx(n);
  for (unsigned int i = 0; i < n; ++i) {
    dx[i] = (std::abs(x[i]) + 1.0) * std::pow(2, -26); // changed to fix x_i=0
  }
  for (unsigned int j = 0; j < n; ++j) {
    x[j] += dx[j];
    auto df = f(x) - fx;
    for (unsigned int i = 0; i < n; ++i) {
      J(i, j) = df[i] / dx[j];
    }
    x[j] -= dx[j];
  }
}

pracprog::vector
newton(const std::function<pracprog::vector(pracprog::vector &)> &f,
       pracprog::vector x, const double acc = 1e-2,
       const double alpha_min = 1e-3, const double max_iter = 100) {
  auto fx = f(x);
  double alpha = 1;
  const size_t n = x.size();
  pracprog::matrix J(n, n);
  for (unsigned int i = 0; i < max_iter; ++i) {
    if (fx.norm() < acc) {
      break;
    }
    pracprog::Jacobian(f, x, fx, J, n);
    pracprog::qr QRJ(J);
    auto Dx = QRJ.solve(-fx);
    alpha = 1;
    while (true) {
      auto z = x + alpha * Dx;
      auto fz = f(z);
      // if (fz.norm() < (1-alpha/2)* fx.norm()) { x=z; fx=fz; break; } // ???
      if (fz.norm() < fx.norm()) {
        x = z;
        fx = fz;
        break;
      }
      if (alpha < alpha_min) {
        x = z;
        fx = fz;
        break;
      }
      alpha /= 2;
    }
  }
  return x;
}

pracprog::vector
quad_interp(const std::function<pracprog::vector(pracprog::vector &)> &f,
            pracprog::vector x, const double acc = 1e-2,
            const double lambda_min = 1e-3, const double max_iter = 100) {
  auto fx = f(x);
  const size_t n = x.size();
  pracprog::matrix J(n, n);

  for (unsigned int i = 0; i < max_iter; ++i) {
    if (fx.norm() < acc)
      break;
    pracprog::Jacobian(f, x, fx, J, n);
    pracprog::qr QRJ(J);
    auto Dx = QRJ.solve(-fx);
    double phi0 = 0.5 * fx.norm() * fx.norm();
    double dphi0 = -fx.norm() * fx.norm();
    double lambda = 1.0;
    while (true) {
      auto z = x + lambda * Dx;
      auto fz = f(z);
      if (fz.norm() < (1.0 - lambda / 2.0) * fx.norm()) {
        x = z;
        fx = fz;
        break;
      }
      if (lambda < lambda_min) {
        x = z;
        fx = fz;
        break;
      }
      double phi_lambda = 0.5 * fz.norm() * fz.norm();
      double c = (phi_lambda - phi0 - dphi0 * lambda) / (lambda * lambda);
      lambda = -dphi0 / (2.0 * c);
    }
  }
  return x;
}

} // namespace pracprog
