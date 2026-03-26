#include "linalg_evd.hpp"
#include <chrono>
#include <iomanip>
#include <random> // for random numbers

constexpr size_t MAX_COL = 4;
constexpr size_t MAX_ROW = 10;
constexpr bool PRINT_MATRICES =
    false; // Change this if you want to see the matrices at the checks

bool exercise_A3(std::mt19937 &generator, const size_t &square_size) {
  pracprog::matrix A(square_size, square_size);
  for (unsigned int col = 0; col < square_size; ++col) {
    for (unsigned int row = 0; row < square_size; ++row) {
      A(row, col) = generator() % 10;
      A(col, row) =
          A(row, col); // can be optimized in diagonals, but this is fine
    }
  }

  // Decomposing
  pracprog::evd EVD(A);
  pracprog::matrix D(square_size, square_size);
  for (size_t i = 0; i < square_size; ++i) {
    D(i, i) = EVD.w[i];
  }
  pracprog::matrix I = pracprog::matrix::identity(square_size);

  // Checks:
  std::cout << "Exercise A.3 checks:\n";
  std::cout << std::fixed << std::setprecision(10);
  pracprog::matrix V_transposed = EVD.V.transpose();
  bool diag_check = pracprog::approx_equal(V_transposed * A * EVD.V, D);
  bool reverse_diag_check = pracprog::approx_equal(EVD.V * D * V_transposed, A);
  bool identity_check = pracprog::approx_equal(V_transposed * EVD.V, I);
  bool reverse_identity_check = pracprog::approx_equal(EVD.V * V_transposed, I);

  if (PRINT_MATRICES) {
    std::cout << "A:\n" << A << std::endl;
    std::cout << "V:\n" << EVD.V << std::endl;
    std::cout << "D:\n" << D << std::endl;
  }
  // Print checks and matrices
  std::cout << "VtAV=D?: " << std::boolalpha << diag_check << std::endl;
  if (PRINT_MATRICES) {
    std::cout << "VtAV:\n" << V_transposed * A * EVD.V << std::endl;
  }
  std::cout << "VDVt=A?: " << std::boolalpha << reverse_diag_check << std::endl;
  if (PRINT_MATRICES) {
    std::cout << "VDVt:\n" << EVD.V * D * V_transposed << std::endl;
  }
  std::cout << "VtV=I? : " << std::boolalpha << identity_check << std::endl;
  if (PRINT_MATRICES) {
    std::cout << "VtV:\n" << V_transposed * EVD.V << std::endl;
  }
  std::cout << "VVt=I? : " << std::boolalpha << reverse_identity_check
            << std::endl;
  if (PRINT_MATRICES) {
    std::cout << "VVt:\n" << EVD.V * V_transposed << std::endl;
  }

  if (!diag_check || !reverse_diag_check || !identity_check ||
      !reverse_identity_check)
    return false;
  return true;
}

int main() {
  // setup rng and random matrix sizes
  long seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng_gen(seed);
  const size_t n = 1 + (rng_gen() % (MAX_COL - 1));
  size_t m = rng_gen() % MAX_ROW;
  while (m < n) {
    m = rng_gen() % MAX_ROW;
  }
  size_t square_size = (n + m) / 2;

  if (!exercise_A3(rng_gen, square_size))
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
