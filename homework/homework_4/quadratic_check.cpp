#include "linalg_splines.hpp"

int main()
{
  const int n = 5;
  pracprog::vector x(n);
  pracprog::vector y(n);
  for (int i = 1; i<=n; ++i) {
    x[i-1] = i;
    y[i-1] = i*i;
  }
  std::cout << y;
  pracprog::quadterp quad_spline(x.size(),std::move(x),std::move(y));

  pracprog::vector manual_c(n-1), manual_b(n-1);
  manual_c[0] = 0; manual_c[1] = 1; manual_c[2]=1; manual_c[3]=1;
  manual_b[0] = 3; manual_b[1] = 4; manual_b[2]=6; manual_b[3]=8;

  std::cout << "Computer calculated\nb: " << quad_spline.get_b() << "c: " << quad_spline.get_c();
  std::cout << "Manually calculated\nb: " << manual_b << "c: " << manual_c;
  std::cout << "Fits except the element of c is 0 instead of 1 (this also causes b[0] to be off by one).\nThis is because i only used forward when calculating manually." << std::endl;


  std::cout << std::endl;

  return EXIT_SUCCESS;
}
