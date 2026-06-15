#include "roots.hpp"
#include <iomanip>

bool simple_case()
{
  auto f = [](pracprog::vector &x) {
    pracprog::vector r(1);
    r[0] = x[0] * x[0] - 2.0;
    return r;
  };
  pracprog::vector x(1);
  x[0] = 1.0;
  pracprog::vector root = pracprog::quad_interp(f, x, 1e-8, 1e-8);
  std::cout << std::setprecision(18)
            << "sqrt(2) root: " << root
            << "Expected: [ 1.41421356 ]\n";
  if (pracprog::approx_equal(root[0], 1.41421356237, 1e-6)) {
    std::cout << "[PASS]\n";
    return true;
  }
  std::cout << "[FAIL]\n";
  return false;
}

int main() {
  std::cout << "--C CHECKS--\n";
  if ( simple_case() ) {
    std::cout << "--All C checks passsed--" << std::endl;
    return EXIT_SUCCESS;
  }
  std::cout << "--One or more C checks failed--" << std::endl;
  return EXIT_FAILURE;
}
