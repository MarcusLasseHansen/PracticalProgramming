#include "network.hpp"
#include <cmath>
#include <iomanip>

bool ode_test() {
  auto Phi = [](double ypp, double, double y, double) {
    return ypp + y;
  };

  const double xa = 0.0, xb = M_PI;
  const double c = 0.0, yc = 1.0, ypc = 0.0;

  pracprog::ann_ode net(8, xa, xb);
  net.train(Phi, xa, xb, c, yc, ypc);

  std::cout << std::fixed << std::setprecision(8);

  double max_err = 0.0;
  for (int k = 0; k <= 100; k++) {
    double x = xa + (xb - xa) * k / 100;
    double err = std::abs(net.response(x) - std::cos(x));
    if (err > max_err)
      max_err = err;
  }
  std::cout << "Max error vs cos(x): " << max_err << "\n";

  if (max_err < 0.1) {
    std::cout << "[PASS]\n";
    return true;
  }
  std::cout << "[FAIL]\n";
  return false;
}

int main() {
  std::cout << "--C CHECKS--\n";
  if (ode_test()) {
    std::cout << "--All C checks passed--\n";
    return EXIT_SUCCESS;
  }
  std::cout << "--One or more C checks failed--\n";
  return EXIT_FAILURE;
}
