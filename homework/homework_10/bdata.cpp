#include "network.hpp"
#include <cmath>
#include <iomanip>
#include <vector>

int main() {
  // gp is g prime (g')
  auto g = [](double x) { return std::cos(5 * x - 1) * std::exp(-x * x); };
  auto gp = [](double x) {
    return std::exp(-x * x) *
           (-5.0 * std::sin(5 * x - 1) - 2.0 * x * std::cos(5 * x - 1));
  };
  auto gpp = [](double x) {
    return std::exp(-x * x) * ((4.0 * x * x - 27.0) * std::cos(5 * x - 1) +
                               20.0 * x * std::sin(5 * x - 1));
  };

  const int N = 300;
  pracprog::vector xs(N), ys(N);
  for (int i = 0; i < N; i++) {
    xs[i] = -1.0 + 2.0 * i / (N - 1);
    ys[i] = g(xs[i]);
  }
  pracprog::ann net(20);
  net.train(xs, ys);

  const int M = 10000;
  const double x0 = -1.0, x1 = 1.0;
  std::vector<double> gx(M + 1), Gx(M + 1);
  Gx[0] = 0.0;
  for (int i = 0; i <= M; i++)
    gx[i] = g(x0 + (x1 - x0) * i / M);
  for (int i = 1; i <= M; i++) {
    double dx = (x1 - x0) / M;
    Gx[i] = Gx[i - 1] + 0.5 * dx * (gx[i - 1] + gx[i]);
  }

  auto g_antideriv_analytical = [&](double x) -> double {
    double t = (x - x0) / (x1 - x0) * M;
    int j = (int)t;
    if (j < 0)
      return Gx[0];
    if (j >= M)
      return Gx[M];
    double frac = t - j;
    return Gx[j] + frac * (Gx[j + 1] - Gx[j]);
  };

  double shift = net.antiderivative(-1.0);

  const int OUT = 1000;
  std::cout << std::scientific << std::setprecision(10);
  for (int i = 0; i < OUT; i++) {
    double x = x0 + (x1 - x0) * i / (OUT - 1);
    std::cout << x << " " << g(x) << " " << gp(x) << " " << gpp(x) << " "
              << g_antideriv_analytical(x) << " " << net.response(x) << " "
              << net.derivative(x) << " " << net.second_derivative(x) << " "
              << (net.antiderivative(x) - shift) << "\n";
  }
  return EXIT_SUCCESS;
}
