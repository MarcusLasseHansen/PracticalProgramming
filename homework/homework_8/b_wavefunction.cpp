#include "../homework_5/ode.hpp"
#include "roots.hpp"

double ME(double rmin, double rmax, double E) {
  auto f = [&E](double r, pracprog::vector y) -> pracprog::vector {
    pracprog::vector res(2);
    res[0] = y[1];
    res[1] = -2 * ((1 / r) + E) * y[0];
    return res;
  };
  pracprog::vector initial(2);
  initial[0] = rmin - rmin * rmin;
  initial[1] = 1 - 2 * rmin;
  return std::get<1>(pracprog::driver(f, rmin, rmax, initial)).back()[0];
}

void WaveFunction(double rmin, double rmax, double E)
{
  auto f = [&E](double r, pracprog::vector y) -> pracprog::vector {
    pracprog::vector res(2);
    res[0] = y[1];
    res[1] = -2 * ((1 / r) + E) * y[0];
    return res;
  };
  pracprog::vector initial(2);
  initial[0] = rmin - rmin * rmin;
  initial[1] = 1 - 2 * rmin;
  auto [xs,ys] = pracprog::driver(f, rmin, rmax, initial);

  for (unsigned int i = 0; i < xs.size(); ++i) {
    std::cout << xs[i] << " " << ys[i][0] << " " << xs[i]*std::exp(-xs[i]) << "\n";
  }
}

int main() {
  pracprog::vector newton_init(1);
  newton_init[0] = -0.6;
  auto f = [](pracprog::vector &x) -> pracprog::vector {
    pracprog::vector res(1);
    res[0] = ME(0.01, 8, x[0]);
    return res;
  };
  pracprog::vector root = pracprog::newton(f, newton_init, 1e-8);

  WaveFunction(0.01,8,root[0]);

  return EXIT_SUCCESS;
}
