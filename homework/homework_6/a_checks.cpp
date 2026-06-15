// Test framework used from homework 5, thus made by AI
#include "integrator.hpp"
#include <iostream>
#include <iomanip>
#include <numbers>

bool check(const std::string label
          , const double &numeric
          , const double &exact
          , double tol = 0.001) {
  double err = std::abs(numeric - exact);
  bool ok = err <= tol;
  std::cout << (ok ? "[PASS]" : "[FAIL]") << "  " << label << "\n"
            << "        ||error|| = " << std::scientific << std::setprecision(3)
            << err << "  (tol=" << tol << ")" << "\n";
  return ok;
}

bool test_1() {
  auto f = [](double x) -> double{return std::sqrt(x);};
  return check("sqrt(x)",pracprog::integrate(f,0,1),2.0/3.0);
}
bool test_2() {
  auto f = [](double x) -> double{return 1/std::sqrt(x);};
  return check("1/sqrt(x)",pracprog::integrate(f,0,1), 2.0);
}
bool test_3() {
  auto f = [](double x) -> double{return std::sqrt(1-(x*x));};
  return check("sqrt(1-x^2)",pracprog::integrate(f,0,1),std::numbers::pi/4.0);
}
bool test_4() {
  auto f = [](double x) -> double{return std::log(x)/std::sqrt(x);};
  return check("ln(x)/sqrt(x)",pracprog::integrate(f,0,1),-4);
}

int main() {
  bool ok = true;
  ok &= test_1();
  ok &= test_2();
  ok &= test_3();
  ok &= test_4();
  std::cout << "\n"
            << (ok ? "All A tests passed." : "One or more tests FAILED.") << "\n\n";
  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
