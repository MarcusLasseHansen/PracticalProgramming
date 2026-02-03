#include "sfuns.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>

int main() {
  std::cout << std::setprecision(15);

  // 1:
  double a = std::sqrt(2.0);
  std::cout << "sqrt(2)= " << a << std::endl;

  double b = std::pow(2.0, 1.5);
  std::cout << "2^1.5= " << b << std::endl;

  double c = std::exp(std::numbers::pi);
  std::cout << "e^pi= " << c << std::endl;

  double d = std::pow(std::numbers::pi, std::numbers::e);
  std::cout << "pi^e= " << d << std::endl;

  // 2:
  for (double x = 1; x < 11; ++x) {
    std::cout << "fgamma(" << x << ") = " << sfuns::fgamma(x) << std::endl;
  }

  // 3:
  for (double x = 1; x < 11; ++x) {
    std::cout << "lnfgamma(" << x << ") = " << sfuns::lnfgamma(x) << std::endl;
  }
}
