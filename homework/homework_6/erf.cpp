#include "integrator.hpp"
#include <iostream>
#include <iomanip>
#include <numbers>

double my_erf(const double &x,const double &acc, const double &eps) {
  if (x < 0) {
    return -my_erf(-x,acc,eps);
  }
  else if (0 <= x && x <= 1) {
    auto f = [](double z) -> double {return std::exp(-std::pow(z,2));};
    return 2.0/(std::sqrt(std::numbers::pi)) * pracprog::integrate(f,0,x,acc,eps);
  }
  else {
    auto f = [x](double t) -> double {return
      std::exp(-std::pow(x+(1-t)/t,2))/t/t;
    };
    return 1-2.0/(std::sqrt(std::numbers::pi)) * pracprog::integrate(f,0,1,acc,eps);
  }
}

int main() {
  constexpr double erf_const = 0.84270079294971486934;
  std::cout << "0.01" << " " << my_erf(1,0.01,0) -erf_const << std::endl;
  std::cout << "0.001" << " " << my_erf(1,0.001,0) -erf_const << std::endl;
  std::cout << "0.0001" << " " << my_erf(1,0.0001,0) -erf_const << std::endl;
  std::cout << "0.00001" << " " << my_erf(1,0.00001,0) -erf_const << std::endl;
  std::cout << "0.000001" << " " << my_erf(1,0.000001,0) -erf_const << std::endl;
  std::cout << "0.0000001" << " " << my_erf(1,0.0000001,0) -erf_const << std::endl;
  std::cout << "0.00000001" << " " << my_erf(1,0.00000001,0) -erf_const << std::endl;
  std::cout << "0.000000001" << " " << my_erf(1,0.000000001,0) -erf_const << std::endl;
  std::cout << "0.0000000001" << " " << my_erf(1,0.0000000001,0) -erf_const << std::endl;
  std::cout << "0.00000000001" << " " << my_erf(1,0.00000000001,0) -erf_const << std::endl;
  std::cout << "0.000000000001" << " " << my_erf(1,0.000000000001,0) -erf_const << std::endl;
  std::cout << "0.0000000000001" << " " << my_erf(1,0.0000000000001,0) -erf_const << std::endl;

  return EXIT_SUCCESS;
}
