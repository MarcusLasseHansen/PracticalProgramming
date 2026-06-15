#include "network.hpp"
#include <iomanip>

bool ann_test() {
  auto g = [](double x) { return std::cos(5 * x - 1) * std::exp(-x * x); };
  const int N = 300;
  pracprog::vector xs(N), ys(N);
  for (int i = 0; i < N; i++) {
    xs[i] = -1.0 + 2.0 * i / (N - 1);
    ys[i] = g(xs[i]);
  }
  pracprog::ann net(20);
  net.train(xs, ys);
  double max_error = 0;
  for (double x = -1.0; x <= 1.0; x += 0.05) {
    double error = std::abs(net.response(x) - g(x));
    if (error > max_error)
      max_error = error;
  }

  std::cout << std::fixed << std::setprecision(6);
  std::cout << "Maximum error: " << max_error << "\n";

  if (max_error < 0.1) {
    std::cout << "[PASS]\n";
    return true;
  }

  std::cout << "[FAIL]\n";
  return false;
}

int main() {
  std::cout << "--A CHECKS--\n";

  if (ann_test()) {
    std::cout << "--All A checks passed--\n";
    return EXIT_SUCCESS;
  }

  std::cout << "--One or more A checks failed--\n";
  return EXIT_FAILURE;
}
