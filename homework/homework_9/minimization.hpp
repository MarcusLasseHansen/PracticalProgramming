#pragma once
#include "../homework_1/linalg_qr.hpp"
#include "../linalg/linalg.hpp"
#include <functional>

namespace pracprog {
pracprog::vector gradient(std::function<double(const pracprog::vector &)> phi,
                          const pracprog::vector &x) {
  double phi_x = phi(x);
  pracprog::vector g(x.size());
  pracprog::vector xp = x;
  for (size_t i = 0; i < x.size(); i++) {
    double dx = (1 + std::abs(x[i])) * std::pow(2.0, -26);
    xp[i] += dx;
    g[i] = (phi(xp) - phi_x) / dx;
    xp[i] -= dx;
  }
  return g;
}

pracprog::matrix hessian(std::function<double(const pracprog::vector &)> phi,
                         const pracprog::vector &x) {
  int n = x.size();
  pracprog::matrix H(n, n);
  pracprog::vector g0 = gradient(phi, x);
  pracprog::vector xp = x;
  for (int j = 0; j < n; j++) {
    double dx = (1 + std::abs(x[j])) * std::pow(2.0, -13);
    xp[j] += dx;
    pracprog::vector dg = gradient(phi, xp) - g0;
    for (int i = 0; i < n; i++)
      H(i, j) = dg[i] / dx;
    xp[j] -= dx;
  }
  return H;
}

std::pair<pracprog::vector, unsigned int>
newton(std::function<double(const pracprog::vector &)> phi, pracprog::vector x,
       double acc = 1e-3) {
  unsigned int steps = 0;
  while (true) {
    pracprog::vector g = gradient(phi, x);
    if (g.norm() < acc)
      break;
    steps++;

    pracprog::matrix H = hessian(phi, x);
    for (size_t i = 0; i < H.rows(); i++)
      H(i, i) += 1e-6;

    pracprog::qr QR(H);
    pracprog::vector dx = QR.solve(-g);

    bool good = false;
    double phi_x = phi(x);
    double lambda = 1.0;
    while (lambda >= 1.0 / 1024) {
      if (phi(x + lambda * dx) < phi_x) {
        good = true;
        break;
      }
      lambda /= 2;
    }
    if (!good) { // algorithm kept failing on higgs data, AI suggested falling
                 // back to changing direction
      dx = -g;
      lambda = 1.0;
    }
    x = x + lambda * dx;
  }
  return {x, steps};
}

pracprog::vector
gradient_central(std::function<double(const pracprog::vector &)> phi,
                 const pracprog::vector &x) {
  pracprog::vector g(x.size());
  pracprog::vector xp = x, xm = x;
  for (size_t i = 0; i < x.size(); i++) {
    double dx = (1 + std::abs(x[i])) * std::pow(2.0, -13);
    xp[i] += dx;
    xm[i] -= dx;
    g[i] = (phi(xp) - phi(xm)) / (2.0 * dx);
    xp[i] = x[i];
    xm[i] = x[i];
  }
  return g;
}

pracprog::matrix
hessian_central(std::function<double(const pracprog::vector &)> phi,
                const pracprog::vector &x) {
  int n = x.size();
  pracprog::matrix H(n, n);
  pracprog::vector g0 = gradient_central(phi, x);
  pracprog::vector xp = x;
  for (int j = 0; j < n; j++) {
    double dx = (1 + std::abs(x[j])) * std::pow(2.0, -13);
    xp[j] += dx;
    pracprog::vector dg = gradient_central(phi, xp) - g0;
    for (int i = 0; i < n; i++)
      H(i, j) = dg[i] / dx;
    xp[j] -= dx;
  }
  return H;
}
std::pair<pracprog::vector, unsigned int>
newton_central(std::function<double(const pracprog::vector &)> phi,
               pracprog::vector x, double acc = 1e-3) {
  unsigned int steps = 0;
  while (true) {
    pracprog::vector g = gradient_central(phi, x);

    if (g.norm() < acc || steps > 10000)
      break;
    steps++;

    pracprog::matrix H = hessian_central(phi, x);
    for (size_t i = 0; i < H.rows(); i++)
      H(i, i) += 1e-4;

    pracprog::qr QR(H);
    pracprog::vector dx = QR.solve(-g);

    bool good = false;
    double phi_x = phi(x);
    double lambda = 1.0;
    while (lambda >= 1.0 / 1024) {
      if (phi(x + lambda * dx) < phi_x) {
        good = true;
        break;
      }
      lambda /= 2;
    }
    if (!good) {
      dx = -g;
      lambda = 1.0;
      if (phi(x + lambda * dx) < phi_x) {
        good = true;
      }
    }

    if (good) {
      x = x + lambda * dx;
    } else {
      break; 
    }
  }
  return {x, steps};
}
} /* namespace pracprog */
