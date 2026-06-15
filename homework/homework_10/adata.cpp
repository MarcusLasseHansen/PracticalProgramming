#include "network.hpp"
#include <iomanip>

void ann_test() {
  auto g = [](double x) { return std::cos(5 * x - 1) * std::exp(-x * x); };
  const int N = 300;
  pracprog::vector xs(N), ys(N);
  for (int i = 0; i < N; i++) {
    xs[i] = -1.0 + 2.0 * i / (N - 1);
    ys[i] = g(xs[i]);
  }
  pracprog::ann net(20);
  net.train(xs, ys);

  for (int i = 0; i < 10000; ++i) {
    double x = -1 + static_cast<double>(i) * (1 - -1) / (10000 - 1);
    std::cout << x << " " << g(x) << " " << net.response(x) << " "
              << std::abs(net.response(x) - g(x)) << "\n";
  }
}

int main() {
  ann_test();
  return EXIT_SUCCESS;
}
