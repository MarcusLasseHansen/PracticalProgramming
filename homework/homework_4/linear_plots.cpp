#include "linalg_splines.hpp"

int main()
{
  const int n = (9.0/0.5)+1;
  pracprog::vector x(n);
  pracprog::vector y(n);
  for (int i = 0; i< n; ++i) {
    x[i] = i * 0.5;
    y[i] = std::cos(x[i]);
  }

  for (double z = 0; z<9; z+=0.1) {
    std:: cout << z << " "
               << pracprog::linterp(x,y,z) << " "
               << std::cos(z) << " "
               << pracprog::linterpInteg(x,y,z) << " "
               << std::sin(z)-std::sin(0) << " "
               << "\n";
  }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
