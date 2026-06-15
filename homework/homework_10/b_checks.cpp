#include "network.hpp"
#include <cmath>
#include <iomanip>

bool check_derivative(pracprog::ann &net, double tol = 1e-5) {
  const double h = 1e-4;
  double max_err = 0.0;
  for (double x = -0.9; x <= 0.9; x += 0.1) {
    double analytic = net.derivative(x);
    double numerical = (net.response(x + h) - net.response(x - h)) / (2.0 * h);
    max_err = std::max(max_err, std::abs(analytic - numerical));
  }
  std::cout << "  1st derivative: " << max_err << "\n";
  return max_err < tol;
}

bool check_second_derivative(pracprog::ann &net, double tol = 1e-4) {
  const double h = 1e-4;
  double max_err = 0.0;
  for (double x = -0.9; x <= 0.9; x += 0.1) {
    double analytic = net.second_derivative(x);
    double numerical =
        (net.derivative(x + h) - net.derivative(x - h)) / (2.0 * h);
    max_err = std::max(max_err, std::abs(analytic - numerical));
  }
  std::cout << "  2nd derivative: " << max_err << "\n";
  return max_err < tol;
}

bool check_antiderivative(pracprog::ann &net, double tol = 1e-5) {
  const double h = 1e-4;
  double max_err = 0.0;
  for (double x = -0.9; x <= 0.9; x += 0.1) {
    double analytic = net.response(x);
    double numerical =
        (net.antiderivative(x + h) - net.antiderivative(x - h)) / (2.0 * h);
    max_err = std::max(max_err, std::abs(analytic - numerical));
  }
  std::cout << "  antiderivative max error: " << max_err << "\n";
  return max_err < tol;
}

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

  std::cout << std::fixed << std::setprecision(8);
  bool ok = true;
  std::cout << "max error vs finite-diff:\n";
  ok &= check_derivative(net);
  ok &= check_second_derivative(net);
  ok &= check_antiderivative(net);

  if (ok)
    std::cout << "[PASS]\n";
  else
    std::cout << "[FAIL]\n";
  return ok;
}

int main() {
  std::cout << "--B CHECKS--\n";
  if (ann_test()) {
    std::cout << "--All B checks passed--\n";
    return EXIT_SUCCESS;
  }
  std::cout << "--One or more B checks failed--\n";
  return EXIT_SUCCESS;
}
