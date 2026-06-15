#include "monte_carlo.hpp"
#include <iomanip>
#include <numbers>

int main() {
  std::cout << std::fixed << std::setprecision(8);

  pracprog::lcg rng(1234);

  bool all_ok = true;

  // Area of unit circle
  auto unit_circle = [](const pracprog::vector &x) -> double {
    double r2 = x[0] * x[0] + x[1] * x[1];
    return (r2 <= 1.0) ? 1.0 : 0.0;
  };

  pracprog::vector a2(2);
  pracprog::vector b2(2);
  a2[0] = -1.0;
  a2[1] = -1.0;
  b2[0] = 1.0;
  b2[1] = 1.0;

  const double exact_area = std::numbers::pi;

  std::vector<int> sample_sizes = {100, 300, 1000, 3000, 10000, 30000, 100000};

  double first_error = 0.0;
  double last_error = 0.0;

  for (int N : sample_sizes) {

    auto [estimate, estimated_error] = plainmc(unit_circle, a2, b2, N, rng);

    double actual_error = std::abs(estimate - exact_area);

    std::cout << N << " " << estimate << " " << actual_error << " "
              << estimated_error << "\n";
    if (first_error == 0.0)
      first_error = actual_error;
    last_error = actual_error;
  }
  double ratio_actual = first_error / last_error;
  double ratio_expected =
      std::sqrt((double)sample_sizes.back() / sample_sizes.front());
  bool scaling_ok = (ratio_actual > 0.3 * ratio_expected);

  std::cout << "\n";
  std::cout << "Exact area = " << exact_area << "\n";

  if (scaling_ok) {
    std::cout << "[PASS] Actual error roughly follows 1/sqrt(N) scaling.\n";
  } else {
    std::cout << "[FAIL] Error scaling check failed.\n";
    all_ok = false;
  }

  // Volume of ellipsoid
  const double A = 1.0;
  const double B = 2.0;
  const double C = 3.0;

  auto ellipsoid = [A, B, C](const pracprog::vector &x) -> double {
    double value =
        x[0] * x[0] / (A * A) + x[1] * x[1] / (B * B) + x[2] * x[2] / (C * C);

    return (value <= 1.0) ? 1.0 : 0.0;
  };

  pracprog::vector a3(3);
  a3[0] = -A;
  a3[1] = -B;
  a3[2] = -C;
  pracprog::vector b3(3);
  b3[0] = A;
  b3[1] = B;
  b3[2] = C;

  const double exact_volume = (4.0 / 3.0) * std::numbers::pi * A * B * C;

  const int N_ellipsoid = 1000000;

  auto [volume_estimate, volume_error] =
      plainmc(ellipsoid, a3, b3, N_ellipsoid, rng);

  double actual_volume_error = std::abs(volume_estimate - exact_volume);

  std::cout << "\n";
  std::cout << "Estimated volume : " << volume_estimate << "\n";
  std::cout << "Exact volume     : " << exact_volume << "\n";
  std::cout << "Actual error     : " << actual_volume_error << "\n";
  std::cout << "Estimated error  : " << volume_error << "\n";

  const double tolerance = 5e-2;

  if (actual_volume_error < tolerance) {
    std::cout << "[PASS] Ellipsoid volume check passed.\n";
  } else {
    std::cout << "[FAIL] Ellipsoid volume check failed.\n";
    all_ok = false;
  }

  if (all_ok) {
    std::cout << "All exercise A checks passed.\n";
    return EXIT_SUCCESS;
  } else {
    std::cout << "One or more exercise A checks failed.\n";
    return EXIT_FAILURE;
  }
}
