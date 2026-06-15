// output of this file made cleaner with AI
#include <iostream>
#include <iomanip>
#include "minimization.hpp"

bool rosenbrock_min() {
  auto phi_raw = [](const pracprog::vector& x) {
    return std::pow(1 - x[0], 2) + 100 * std::pow(x[1] - x[0]*x[0], 2);
  };

  unsigned int evals_forward = 0, evals_central = 0;
  auto phi_f = [&](const pracprog::vector& x) { evals_forward++; return phi_raw(x); };
  auto phi_c = [&](const pracprog::vector& x) { evals_central++; return phi_raw(x); };

  pracprog::vector x(2);
  x[0] = 0; x[1] = 0;

  auto [result,         steps]         = pracprog::newton(phi_f, x);
  auto [result_central, steps_central] = pracprog::newton_central(phi_c, x);

  std::cout << std::setprecision(18)
            << "Calculated minimum of Rosenbrock's valley function:\n"
            << "  forward: " << result         << " steps: " << steps         << " evals: " << evals_forward  << "\n"
            << "  central: " << result_central << " steps: " << steps_central << " evals: " << evals_central  << "\n"
            << "  expected: [ 1.00 1.00 ]\n";

  if (pracprog::approx_equal(result[0],         1.0, 1e-3) &&
      pracprog::approx_equal(result[1],         1.0, 1e-3) &&
      pracprog::approx_equal(result_central[0], 1.0, 1e-3) &&
      pracprog::approx_equal(result_central[1], 1.0, 1e-3)) {
    std::cout << "[PASS]\n";
    return true;
  }
  std::cout << "[FAIL]\n";
  return false;
}

bool himmelblau_min() {
  auto phi_raw = [](const pracprog::vector& x) {
    return std::pow(x[0]*x[0] + x[1] - 11, 2) + std::pow(x[0] + x[1]*x[1] - 7, 2);
  };

  unsigned int e1=0, e2=0, e3=0, e4=0;
  unsigned int e5=0, e6=0, e7=0, e8=0;
  auto phi1 = [&](const pracprog::vector& x) { e1++; return phi_raw(x); };
  auto phi2 = [&](const pracprog::vector& x) { e2++; return phi_raw(x); };
  auto phi3 = [&](const pracprog::vector& x) { e3++; return phi_raw(x); };
  auto phi4 = [&](const pracprog::vector& x) { e4++; return phi_raw(x); };
  auto phi5 = [&](const pracprog::vector& x) { e5++; return phi_raw(x); };
  auto phi6 = [&](const pracprog::vector& x) { e6++; return phi_raw(x); };
  auto phi7 = [&](const pracprog::vector& x) { e7++; return phi_raw(x); };
  auto phi8 = [&](const pracprog::vector& x) { e8++; return phi_raw(x); };

  // Himmelblau has 4 minima
  pracprog::vector x1(2); x1[0] =  2; x1[1] =  2;
  pracprog::vector x2(2); x2[0] = -2; x2[1] =  2;
  pracprog::vector x3(2); x3[0] = -3; x3[1] = -3;
  pracprog::vector x4(2); x4[0] =  3; x4[1] = -2;

  auto [r1, s1] = pracprog::newton(phi1, x1);
  auto [r2, s2] = pracprog::newton(phi2, x2);
  auto [r3, s3] = pracprog::newton(phi3, x3);
  auto [r4, s4] = pracprog::newton(phi4, x4);

  auto [r5, s5] = pracprog::newton_central(phi5, x1);
  auto [r6, s6] = pracprog::newton_central(phi6, x2);
  auto [r7, s7] = pracprog::newton_central(phi7, x3);
  auto [r8, s8] = pracprog::newton_central(phi8, x4);

  std::cout << std::setprecision(6)
            << "Calculated minima of Himmelblau's function:\n"
            << "  forward  " << r1 << " steps: " << s1 << " evals: " << e1 << " expected [ 3.00000  2.00000 ]\n"
            << "  forward  " << r2 << " steps: " << s2 << " evals: " << e2 << " expected [ -2.80512  3.13131 ]\n"
            << "  forward  " << r3 << " steps: " << s3 << " evals: " << e3 << " expected [ -3.77931 -3.28319 ]\n"
            << "  forward  " << r4 << " steps: " << s4 << " evals: " << e4 << " expected [  3.58443 -1.84813 ]\n"
            << "  central  " << r5 << " steps: " << s5 << " evals: " << e5 << " expected [ 3.00000  2.00000 ]\n"
            << "  central  " << r6 << " steps: " << s6 << " evals: " << e6 << " expected [ -2.80512  3.13131 ]\n"
            << "  central  " << r7 << " steps: " << s7 << " evals: " << e7 << " expected [ -3.77931 -3.28319 ]\n"
            << "  central  " << r8 << " steps: " << s8 << " evals: " << e8 << " expected [  3.58443 -1.84813 ]\n";

  if (pracprog::approx_equal(r1[0],  3.00000, 1e-3) && pracprog::approx_equal(r1[1],  2.00000, 1e-3) &&
      pracprog::approx_equal(r2[0], -2.80512, 1e-3) && pracprog::approx_equal(r2[1],  3.13131, 1e-3) &&
      pracprog::approx_equal(r3[0], -3.77931, 1e-3) && pracprog::approx_equal(r3[1], -3.28319, 1e-3) &&
      pracprog::approx_equal(r4[0],  3.58443, 1e-3) && pracprog::approx_equal(r4[1], -1.84813, 1e-3) &&
      pracprog::approx_equal(r5[0],  3.00000, 1e-3) && pracprog::approx_equal(r5[1],  2.00000, 1e-3) &&
      pracprog::approx_equal(r6[0], -2.80512, 1e-3) && pracprog::approx_equal(r6[1],  3.13131, 1e-3) &&
      pracprog::approx_equal(r7[0], -3.77931, 1e-3) && pracprog::approx_equal(r7[1], -3.28319, 1e-3) &&
      pracprog::approx_equal(r8[0],  3.58443, 1e-3) && pracprog::approx_equal(r8[1], -1.84813, 1e-3)) {
    std::cout << "[PASS]\n";
    return true;
  }
  std::cout << "[FAIL]\n";
  return false;
}

int main() {
  std::cout << "--C CHECKS--\n";
  if (rosenbrock_min() && himmelblau_min()) {
    std::cout << "--All C checks passed--\n";
    return EXIT_SUCCESS;
  }
  std::cout << "--One or more C checks failed--\n";
  return EXIT_FAILURE;
}
