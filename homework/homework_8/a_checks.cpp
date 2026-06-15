#include "roots.hpp"
#include <iomanip>

bool rosenbrock_roots()
{
  auto gradient = [](pracprog::vector &x) {
    pracprog::vector f(2);
    f[0] = 400*x[0]*x[0]*x[0]-400*x[0]*x[1]+2*x[0]-2;
    f[1] = 200*x[1]-200*x[0]*x[0];
    return f;
  };
  pracprog::vector x(2);
  x[0] = 0; x[1] = 0;
  pracprog::vector roots = pracprog::newton(gradient,x,1e-5);
  std::cout << std::setprecision(18) << "Calculated roots of rosenbrock gradient: " << roots
            << "Expected roots: [ 1.00 1.00 ]\n";
  if (pracprog::approx_equal(roots[0],1.00,1e-5) && pracprog::approx_equal(roots[1],1.00,1e-5)) {

    std::cout << "[PASS]" << std::endl;
    return true;
  }
  std::cout << "[FAIL]" << std::endl;
  return false;
}

bool himmelblau_roots()
{
  auto gradient = [](pracprog::vector &x) {
    pracprog::vector f(2);
    f[0] = 4*x[0]*x[0]*x[0] + 4*x[0]*x[1] - 42*x[0] + 2*x[1]*x[1] - 14;
    f[1] = 2*x[0]*x[0] + 4*x[0]*x[1] + 4*x[1]*x[1]*x[1] - 26*x[1] - 22;
    return f;
  };
  pracprog::vector x1(2);
  x1[0] = 2; x1[1] = 1;
  pracprog::vector roots1 = pracprog::newton(gradient,x1,1e-8);
  pracprog::vector x2(2);
  x2[0] = -3; x2[1] = -3;
  pracprog::vector roots2 = pracprog::newton(gradient,x2,1e-8);

  std::cout << std::setprecision(18) << "Calculated minima of himmelblau function:\n" << roots1 << roots2
            << "Expected roots:\n[ 3.00 2.00 ]\n[ -3.77931 -3.28319 ]\n";
  if (pracprog::approx_equal(roots1[0],3   ,1e-5) && pracprog::approx_equal(roots1[1], 2,1e-5) && pracprog::approx_equal(roots2[0],-3.77931   ,1e-5) && pracprog::approx_equal(roots2[1], -3.28319,1e-5)) {

    std::cout << "[PASS]" << std::endl;
    return true;
  }
  std::cout << "[FAIL]" << std::endl;
  return false;
}

int main() {
  std::cout << "--A CHECKS--\n";
  if ( rosenbrock_roots() && himmelblau_roots() ) {
    std::cout << "--All A checks passsed--" << std::endl;
    return EXIT_SUCCESS;
  }
  std::cout << "--One or more A checks failed--" << std::endl;
  return EXIT_FAILURE;
}
