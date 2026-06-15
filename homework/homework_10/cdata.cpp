#include "network.hpp"
#include <cmath>
#include <iomanip>

int main() {
  auto Phi = [](double ypp, double, double y, double) {
    return ypp + y;
  };

  const double xa = 0.0, xb = M_PI;
  const double c = 0.0, yc = 1.0, ypc = 0.0;

  pracprog::ann_ode net(8, xa, xb);
  net.train(Phi, xa, xb, c, yc, ypc);

  std::cout << std::scientific << std::setprecision(10);
  for (int i = 0; i < 1000; i++) {
    double x = xa + (xb - xa) * i / (1000 - 1);
    std::cout << x
              << " " << std::cos(x)
              << " " << -std::sin(x)
              << " " << net.response(x)
              << "\n";
  }
  return EXIT_SUCCESS;
}
