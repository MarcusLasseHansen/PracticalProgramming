// Test written by claude code

#include "monte_carlo.hpp"
#include <cmath>
#include <numbers>
#include <random>

int main() {
  // expected to be more accurate for the stratified mc
  auto f = [](const pracprog::vector &x) -> double {
    double dx = x[0] - 0.3, dy = x[1] - 0.7;
    return std::exp(-100.0 * (dx * dx + dy * dy));
  };

  pracprog::vector a(2), b(2);
  a[0] = 0.0;
  a[1] = 0.0;
  b[0] = std::numbers::pi;
  b[1] = std::numbers::pi;

  const double exact = std::numbers::pi / 100.0;
  const int N = 10000;

  // Plain MC for comparison
  std::mt19937_64 eng(42);
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  auto gen = [&]() { return dist(eng); };
  auto [plain_est, plain_err] = pracprog::plainmc(f, a, b, N, gen);

  // Stratified
  auto [strat_est, strat_err] = pracprog::stratified(f, a, b, N);

  const double plain_actual = std::abs(plain_est - exact);
  const double strat_actual = std::abs(strat_est - exact);

  bool plain_ok = plain_actual < 0.005;
  bool strat_ok = strat_actual < 0.005;
  bool improvement = strat_actual < plain_actual;

  std::cout << "Integrand: exp(-100((x-0.3)^2+(y-0.7)^2)) over [0,pi]^2,  exact = " << exact << "\n";
  std::cout << "N = " << N << "\n\n";
  std::cout << "Plain MC  : estimate = " << plain_est
            << "  |error| = " << plain_actual << "  (est. error = " << plain_err
            << ")\n";
  std::cout << "Stratified: estimate = " << strat_est
            << "  |error| = " << strat_actual << "  (est. error = " << strat_err
            << ")\n";

  std::cout << "\n";
  std::cout << (plain_ok ? "[PASS]" : "[FAIL]")
            << " Plain MC within 0.05 of exact\n";
  std::cout << (strat_ok ? "[PASS]" : "[FAIL]")
            << " Stratified within 0.05 of exact\n";
  std::cout << (improvement ? "[PASS]" : "[FAIL]")
            << " Stratified more accurate than plain MC\n";

  if (plain_ok && strat_ok && improvement) {
    std::cout << "\nAll exercise C checks passed.\n";
    return EXIT_SUCCESS;
  } else {
    std::cout << "\nOne or more exercise C checks failed.\n";
    return EXIT_FAILURE;
  }
}
