// Framework copied from A3_tests.cpp, and thus developed by claude sonnet 4.6
#include "ode.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

using pracprog::vector;

static vector vec2(double a, double b) {
  vector v(2);
  v[0] = a;
  v[1] = b;
  return v;
}

bool check(const std::string &label, const vector &y_numeric,
           const vector &y_exact, int n_steps, double tol = 1e-6) {
  double err = (y_numeric - y_exact).norm();
  bool ok = err <= tol;
  std::cout << (ok ? "[PASS]" : "[FAIL]") << "  " << label << "\n"
            << "        ||error|| = " << std::scientific << std::setprecision(3)
            << err << "  (tol=" << tol << ")  steps=" << n_steps << "\n";
  return ok;
}

//   oscillator with friction -
//   https://docs.scipy.org/doc/scipy/reference/generated/scipy.integrate.odeint.html
bool test_oscillator() {
  const double b = 0.25;
  const double c = 5.0;
  auto f = [b, c](double, vector y) -> vector {
    return vec2(y[1], -b * y[1] - c * std::sin(y[0]));
  };

  vector y0 = vec2(M_PI - 0.1, 0.0);

  auto [xs, ys] = pracprog::driver(f, 0.0, 10.0, y0, 0.125, 1e-8, 1e-8);

  // Reference from scipy odeint at rtol=atol=1e-12
  vector y_ref = vec2(0.020011530841621, 1.567818262711030);

  return check(
      "Harmonic oscillator with friction  theta''+ 0.25*theta'+ 5*sin(theta)=0,  y0=[pi-0.1, 0]",
      ys.back(), y_ref, (int)xs.size() - 1, 1e-5);
}

int main() {
  bool ok = true;
  ok &= test_oscillator();
  std::cout << "\n"
            << (ok ? "All exercise A4 tests passed." : "One or more tests FAILED.") << "\n\n";
  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
