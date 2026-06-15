#include "monte_carlo.hpp"
#include <cmath>
#include <numbers>
#include <random>

int main() {
  auto smooth_f = [](const pracprog::vector &x) -> double {
    return std::sin(x[0]) * std::sin(x[1]);
  };
  pracprog::vector a2(2), b2(2);
  a2[0] = 0.0;
  a2[1] = 0.0;
  b2[0] = std::numbers::pi;
  b2[1] = std::numbers::pi;
  const double exact_smooth = 4.0;
  const int N_lo = 100, N_hi = 100000;
  pracprog::lcg lcg_lo(1), lcg_hi(2);
  std::mt19937_64 stl_lo_eng(1), stl_hi_eng(2);
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  auto stl_gen_lo = [&]() { return dist(stl_lo_eng); };
  auto stl_gen_hi = [&]() { return dist(stl_hi_eng); };
  double e_lcg_lo = pracprog::plainmc(smooth_f, a2, b2, N_lo, lcg_lo).first;
  double e_lcg_hi = pracprog::plainmc(smooth_f, a2, b2, N_hi, lcg_hi).first;
  double e_stl_lo = pracprog::plainmc(smooth_f, a2, b2, N_lo, stl_gen_lo).first;
  double e_stl_hi = pracprog::plainmc(smooth_f, a2, b2, N_hi, stl_gen_hi).first;
  double e_quasi_lo = pracprog::quasimc(smooth_f, a2, b2, N_lo).first;
  double e_quasi_hi = pracprog::quasimc(smooth_f, a2, b2, N_hi).first;
  double expected = std::sqrt((double)N_hi / N_lo);
  bool lcg_ok =
      std::abs(e_lcg_lo - exact_smooth) / std::abs(e_lcg_hi - exact_smooth) >
      0.2 * expected;
  bool stl_ok =
      std::abs(e_stl_lo - exact_smooth) / std::abs(e_stl_hi - exact_smooth) >
      0.2 * expected;
  bool quasi_ok = std::abs(e_quasi_lo - exact_smooth) /
                      std::abs(e_quasi_hi - exact_smooth) >
                  expected;
  std::cout << (lcg_ok ? "[PASS]" : "[FAIL]")
            << " LCG   error scales as 1/sqrt(N)\n";
  std::cout << (stl_ok ? "[PASS]" : "[FAIL]")
            << " STL   error scales as 1/sqrt(N)\n";
  std::cout << (quasi_ok ? "[PASS]" : "[FAIL]")
            << " Quasi converges better than 1/sqrt(N)\n";
  const double exact_singular = 1.3932039296856768591842462603255;
  auto singular_f = [](const pracprog::vector &x) -> double {
    double denom = 1.0 - std::cos(x[0]) * std::cos(x[1]) * std::cos(x[2]);
    if (std::abs(denom) < 1e-14)
      return 0.0;
    return 1.0 /
           (std::numbers::pi * std::numbers::pi * std::numbers::pi * denom);
  };
  pracprog::vector a3(3), b3(3);
  a3[0] = 0.0;
  a3[1] = 0.0;
  a3[2] = 0.0;
  b3[0] = std::numbers::pi;
  b3[1] = std::numbers::pi;
  b3[2] = std::numbers::pi;
  const int N_final = 1000000;
  pracprog::lcg lcg_rng(777777);
  std::mt19937_64 stl_eng(777777);
  std::uniform_real_distribution<double> dist2(0.0, 1.0);
  auto stl_gen = [&]() { return dist2(stl_eng); };
  double lcg_est =
      pracprog::plainmc(singular_f, a3, b3, N_final, lcg_rng).first;
  double stl_est =
      pracprog::plainmc(singular_f, a3, b3, N_final, stl_gen).first;
  double quasi_est = pracprog::quasimc(singular_f, a3, b3, N_final).first;
  const double tol = 0.05;
  lcg_ok = std::abs(lcg_est - exact_singular) < tol;
  stl_ok = std::abs(stl_est - exact_singular) < tol;
  quasi_ok = std::abs(quasi_est - exact_singular) < tol;
  std::cout << (lcg_ok ? "[PASS]" : "[FAIL]") << " LCG   within " << tol
            << " of exact\n";
  std::cout << (stl_ok ? "[PASS]" : "[FAIL]") << " STL   within " << tol
            << " of exact\n";
  std::cout << (quasi_ok ? "[PASS]" : "[FAIL]") << " Quasi within " << tol
            << " of exact\n";
  if (lcg_ok && stl_ok && quasi_ok) {
    std::cout << "\nAll exercise B checks passed.\n";
    return EXIT_SUCCESS;
  } else {
    std::cout << "\nOne or more exercise B checks failed.\n";
    return EXIT_FAILURE;
  }
}
