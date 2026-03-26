#include "linalg_qr.hpp"
#include <chrono>
#include <iomanip>
#include <random> // for random numbers

//  idk what is of modest size for you, if you want set them to millions
constexpr size_t MAX_COL = 4;
constexpr size_t MAX_ROW = 10;
constexpr bool PRINT_MATRICES =
    false; // Change this if you want to see the matrices at the checks

bool is_upper_triangular(const pracprog::matrix &A, const double tol = 1e-10) {
  for (size_t j = 0; j < A.cols(); j++)
    for (size_t i = j + 1; i < A.rows(); i++)
      if (std::abs(A(i, j)) > tol)
        return false;
  return true;
}

bool exercise_A2(std::mt19937 &generator, const size_t& n, const size_t& m) {
  pracprog::matrix A(m, n);
  for (unsigned int col = 0; col < n; ++col) {
    for (unsigned int row = 0; row < m; ++row) {
      A(row, col) = generator() % 10;
    }
  }

  // Decomposing
  pracprog::qr QR(A);

  // Checks:
  std::cout << "Exercise A.2 checks:\n";
  std::cout << std::fixed << std::setprecision(10);
  pracprog::matrix Q_transposed = QR.Q.transpose();
  bool trig_check = is_upper_triangular(QR.R);
  bool identity_check = pracprog::approx_equal(Q_transposed * QR.Q,
                                               pracprog::matrix::identity(n));
  bool recomp_check = pracprog::approx_equal(QR.Q * QR.R, A);

  // Print checks and matrices
  std::cout << "R triangular?: " << std::boolalpha << trig_check << std::endl;
  if (PRINT_MATRICES) {
    std::cout << QR.R << std::endl;
  }
  std::cout << "Q^(T)Q = I?: " << std::boolalpha << identity_check << std::endl;
  if (PRINT_MATRICES) {
    std::cout << (QR.Q.transpose() * QR.Q);
  }
  std::cout << "QR=A: " << std::boolalpha << recomp_check << std::endl;
  if (PRINT_MATRICES) {
    std::cout << "QR:\n" << QR.Q * QR.R << "A:\n" << A;
  }

  if (!trig_check || !identity_check || !recomp_check)
    return false;
  return true;
}

bool exercise_A3(std::mt19937 &generator, const size_t& size) {

  // construct matrices
  pracprog::matrix A(size, size);
  pracprog::vector b(size);
  for (unsigned int col = 0; col < size; ++col) {
    for (unsigned int row = 0; row < size; ++row) {
      A(row, col) = generator() % 10;
    }
    b[col] = generator() % 10;
  }
  pracprog::qr QR(A);
  pracprog::vector x = QR.solve(b);

  // Check
  bool linear_check = pracprog::approx_equal(A * x, b);

  // Print checks and matrices
  std::cout << "Exercise A.3 checks:\n";
  std::cout << "Ax=b?: " << std::boolalpha << linear_check << std::endl;
  if (PRINT_MATRICES) {
    std::cout << "A:\n"
              << A << "Q:\n"
              << QR.Q << "R:\n"
              << QR.R << "b:\n"
              << b << "x:\n"
              << x << std::endl;
  }
  if (!linear_check)
    return false;
  return true;
}

bool exercise_A4(std::mt19937 &generator, const size_t& size) {
  // construct matrices
  pracprog::matrix A(size, size);
  for (unsigned int col = 0; col < size; ++col) {
    for (unsigned int row = 0; row < size; ++row) {
      A(row, col) = generator() % 10;
    }
  }
  pracprog::qr QR(A);

  // Checks:
  bool determinant_check =
      pracprog::approx_equal(std::abs(A.det()), std::abs(QR.det()));
  // note std::abs since Gram-Schmidt has arbitrary column signs

  // Print checks and matrices
  std::cout << "Exercise A.4 checks:\n";
  std::cout << "det(A)=det(R)?: " << std::boolalpha << determinant_check
            << std::endl;
  if (PRINT_MATRICES) {
    std::cout << "A:\n" << A << "R:\n" << QR.R << std::endl;
  }
  if (!determinant_check)
    return false;
  return true;
}

bool exercise_A(std::mt19937 &rng_gen, const size_t& n, const size_t& m,
                const size_t& square_size) {
  if (exercise_A2(rng_gen, n, m) && exercise_A3(rng_gen, square_size) &&
      exercise_A4(rng_gen, square_size))
    return true;
  return false;
}

bool exercise_B(std::mt19937 &rng_gen, const size_t& square_size) {
  // construct matrix
  pracprog::matrix A(square_size, square_size);
  for (unsigned int col = 0; col < square_size; ++col) {
    for (unsigned int row = 0; row < square_size; ++row) {
      A(row, col) = rng_gen() % 10;
    }
  }
  pracprog::qr QR(A);
  pracprog::matrix A_inv = QR.inverse();

  //check
  bool inverse_check = pracprog::approx_equal(
      A * A_inv, pracprog::matrix::identity(square_size));

  // print chekcs and matrices
  std::cout << "Exercise B checks:\n";
  std::cout << "A*A_inverse=I?: " << std::boolalpha << inverse_check
            << std::endl;
  if (PRINT_MATRICES) {
    std::cout << "A:\n"
              << A << "A_inverse:\n"
              << A_inv << "A*A_inverse:\n"
              << A * A_inv << std::endl;
  }

  if (!inverse_check)
    return false;
  return true;
}

int main() {
  // setup rng and random matrix sizes
  long seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng_gen(seed);
  const size_t n = 1+(rng_gen() % (MAX_COL-1));
  size_t m = rng_gen() % MAX_ROW;
  while (m < n) {
    m = rng_gen() % MAX_ROW;
  }
  size_t square_size = (n + m) / 2;

  // check if exercies work
  if (!exercise_A(rng_gen, n, m, square_size) ||
      !exercise_B(rng_gen, square_size)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
