#include "linalg_splines.hpp"

int main()
{
  const int n = 6;
  pracprog::vector x(n);
  pracprog::vector y_1(n);
  pracprog::vector y_2(n);
  pracprog::vector y_3(n);
  for (int i = 0; i< n; ++i) {
    x[i] = i;
    y_1[i] = 1;
    y_2[i] = i;
    y_3[i] = i*i;
  }
  pracprog::cubeterp cube_spline_1(x.size(),x,y_1);
  pracprog::cubeterp cube_spline_2(x.size(),x,y_2);
  pracprog::cubeterp cube_spline_3(x.size(),x,y_3);
  for (double z = 0; z<n-1; z+=0.1) {
    std:: cout << z << " "
               << cube_spline_1.eval(z) << " "
               << 1 << " "
               << cube_spline_2.eval(z) << " "
               << z << " "
               << cube_spline_3.eval(z) << " "
               << z*z << " "
               << cube_spline_1.eval_int(z) << " "
               << 1*z << " "
               << cube_spline_2.eval_int(z) << " "
               << 0.5*z*z << " "
               << cube_spline_3.eval_int(z) << " "
               << (1.00/3.00)*z*z*z << " "
               << cube_spline_2.eval_deriv(z) << " "
               << 1 << " "
               << cube_spline_3.eval_deriv(z) << " "
               << 2*z
               << "\n";
  }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
