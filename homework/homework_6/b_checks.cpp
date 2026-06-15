#include "integrator.hpp"
#include <iostream>
#include <iomanip>

bool check(const std::string label, const double &numeric, const double &exact,
           double tol = 0.001) {
  double err = std::abs(numeric - exact);
  bool ok = err <= tol;
  std::cout << (ok ? "[PASS]" : "[FAIL]") << "  " << label << "\n"
            << "        ||error|| = " << std::scientific << std::setprecision(3)
            << err << "  (tol=" << tol << ")" << "\n";
  return ok;
}

void test_1() {
  auto f = [](double x) -> double { return std::sqrt(x); };
  std::cout << "sqrt(x) - cc_vt evaluations: "
            << pracprog::cc_vt_integral_with_count(f, 0, 1).second
            << "  standard method evaluations: "
            << pracprog::integrate_with_count(f, 0, 1).second << std::endl;
}
void test_2() {
  auto f = [](double x) -> double { return 1 / std::sqrt(x); };
  std::cout << "1/sqrt(x) - cc_vt evaluations: "
            << pracprog::cc_vt_integral_with_count(f, 0, 1).second
            << "  standard method evaluations: "
            << pracprog::integrate_with_count(f, 0, 1).second << std::endl;
}
void test_3() {
  auto f = [](double x) -> double { return std::sqrt(1 - (x * x)); };
  std::cout << "sqrt(1-x^2) - cc_vt evaluations: "
            << pracprog::cc_vt_integral_with_count(f, 0, 1).second
            << "  standard method evaluations: "
            << pracprog::integrate_with_count(f, 0, 1).second << std::endl;
}
void test_4() {
  auto f = [](double x) -> double { return std::log(x) / std::sqrt(x); };
  std::cout << "ln(x)/sqrt(x) - cc_vt evaluations: "
            << pracprog::cc_vt_integral_with_count(f, 0, 1).second
            << "  standard method evaluations: "
            << pracprog::integrate_with_count(f, 0, 1).second << std::endl;
}

bool test_5() {
  auto f = [](double x) -> double { return std::exp(-x) * std::sin(x); };
  auto res = pracprog::generalized_integral_with_count(f, 0);
  std::cout << "e^(-x)*sin(x) - cc_vt evaluations: " << res.second << std::endl;
  return check("sqrt(x)", res.first, 1.0 / 2.0);
}

bool test_6() {
  auto f = [](double x) -> double { return std::exp(-(x*x)); };
  auto res = pracprog::generalized_integral_with_count(f, 0);
  std::cout << "e^(-x^2) - cc_vt evaluations: " << res.second << std::endl;
  return check("sqrt(x)", res.first, std::sqrt(std::numbers::pi) / 2.0);
}

int main() {
  test_1();
  test_2();
  test_3();
  test_4();
  std::cout << "numpy only has trapz method that scales with the gridspace used, thus is not "
               "comparable."
            << std::endl;
  bool ok = true;
  ok &= test_5();
  ok &= test_6();
  std::cout << "\n"
            << (ok ? "All B tests passed." : "One or more tests FAILED.") << "\n\n";
  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
