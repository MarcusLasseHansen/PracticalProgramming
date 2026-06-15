// output of this file made cleaner with AI
#include <iostream>
#include <iomanip>
#include "minimization.hpp"

bool rosenbrock_min() {
  auto phi = [](const pracprog::vector& x) {
    return std::pow(1 - x[0], 2) + 100 * std::pow(x[1] - x[0]*x[0], 2);
  };
  pracprog::vector x(2);
  x[0] = 0; x[1] = 0;
  auto [result, steps] = pracprog::newton(phi, x);
  std::cout << std::setprecision(18)
            << "Calculated minimum of Rosenbrock's valley function:\n" << result
            << "Expected minimum: [ 1.00 1.00 ]\n"
            << "Steps taken: " << steps << "\n";
  if (pracprog::approx_equal(result[0], 1.0, 1e-3) &&
      pracprog::approx_equal(result[1], 1.0, 1e-3)) {
    std::cout << "[PASS]\n";
    return true;
  }
  std::cout << "[FAIL]\n";
  return false;
}

bool himmelblau_min() {
  auto phi = [](const pracprog::vector& x) {
    return std::pow(x[0]*x[0] + x[1] - 11, 2) + std::pow(x[0] + x[1]*x[1] - 7, 2);
  };
  // Himmelblau has 4 minima
  pracprog::vector x1(2); x1[0] =  2; x1[1] =  2;
  pracprog::vector x2(2); x2[0] = -2; x2[1] =  2;
  pracprog::vector x3(2); x3[0] = -3; x3[1] = -3;
  pracprog::vector x4(2); x4[0] =  3; x4[1] = -2;

  auto [r1, s1] = pracprog::newton(phi, x1);
  auto [r2, s2] = pracprog::newton(phi, x2);
  auto [r3, s3] = pracprog::newton(phi, x3);
  auto [r4, s4] = pracprog::newton(phi, x4);

  std::cout << std::setprecision(6)
            << "Calculated minima of Himmelblau's function:\n"
            << r1 << " (steps: " << s1 << ") expected [ 3.00000  2.00000 ]\n"
            << r2 << " (steps: " << s2 << ") expected [ -2.80512  3.13131 ]\n"
            << r3 << " (steps: " << s3 << ") expected [ -3.77931 -3.28319 ]\n"
            << r4 << " (steps: " << s4 << ") expected [  3.58443 -1.84813 ]\n";

  if (pracprog::approx_equal(r1[0],  3.00000, 1e-3) && pracprog::approx_equal(r1[1],  2.00000, 1e-3) &&
      pracprog::approx_equal(r2[0], -2.80512, 1e-3) && pracprog::approx_equal(r2[1],  3.13131, 1e-3) &&
      pracprog::approx_equal(r3[0], -3.77931, 1e-3) && pracprog::approx_equal(r3[1], -3.28319, 1e-3) &&
      pracprog::approx_equal(r4[0],  3.58443, 1e-3) && pracprog::approx_equal(r4[1], -1.84813, 1e-3)) {
    std::cout << "[PASS]\n";
    return true;
  }
  std::cout << "[FAIL]\n";
  return false;
}

int main() {
  std::cout << "--A CHECKS--\n";
  if (rosenbrock_min() && himmelblau_min()) {
    std::cout << "--All A checks passed--\n";
    return EXIT_SUCCESS;
  }
  std::cout << "--One or more A checks failed--\n";
  return EXIT_FAILURE;
}
