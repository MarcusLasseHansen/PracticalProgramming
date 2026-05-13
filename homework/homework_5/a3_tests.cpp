// Entire test program written by claude sonnet 4.6
#include "ode.hpp"
#include <cmath>
#include <iomanip>

using pracprog::vector;

static vector vec1(double a) {
  vector v(1);
  v[0] = a;
  return v;
}
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

// ── Test 1 : exponential decay  y'=-y, y(0)=1  →  y(x)=e^{-x} ─────────────
bool test_exponential() {
  auto f = [](double, vector y) -> vector { return vec1(-y[0]); };
  auto [xs, ys] = pracprog::driver(f, 0.0, 3.0, vec1(1.0), 0.125, 1e-8, 1e-8);
  double x_end = xs.back();
  return check("Exponential decay  y'=-y, y(0)=1", ys.back(),
               vec1(std::exp(-x_end)), (int)xs.size() - 1);
}

// ── Test 2 : harmonic oscillator  [y,v]'=[v,-y], y(0)=[0,1]  (one period) ──
bool test_harmonic() {
  auto f = [](double, vector y) -> vector { return vec2(y[1], -y[0]); };
  auto [xs, ys] =
      pracprog::driver(f, 0.0, 2.0 * M_PI, vec2(0.0, 1.0), 0.125, 1e-8, 1e-8);
  double x_end = xs.back();
  return check("Harmonic oscillator (one period)", ys.back(),
               vec2(std::sin(x_end), std::cos(x_end)), (int)xs.size() - 1);
}

// ── Test 3 : logistic  y'=2y(1-y), y(0)=0.1  →  1/(1+9e^{-2x}) ────────────
bool test_logistic() {
  const double r = 2.0;
  auto f = [r](double, vector y) -> vector {
    return vec1(r * y[0] * (1.0 - y[0]));
  };
  auto [xs, ys] = pracprog::driver(f, 0.0, 5.0, vec1(0.1), 0.125, 1e-8, 1e-8);
  double x_end = xs.back();
  return check("Logistic equation  y'=2y(1-y), y(0)=0.1", ys.back(),
               vec1(1.0 / (1.0 + 9.0 * std::exp(-r * x_end))),
               (int)xs.size() - 1);
}

int main() {
  bool ok = true;
  ok &= test_exponential();
  ok &= test_harmonic();
  ok &= test_logistic();
  std::cout << "\n"
            << (ok ? "All A3 tests passed." : "One or more tests FAILED.") << "\n\n";
  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
