#include "../homework_5/ode.hpp"
#include "roots.hpp"

constexpr double standard_rmin = 0.01;
constexpr double standard_rmax = 8;
constexpr double standard_acc = 0.01;
constexpr double standard_eps = 0.01;

double ME(double rmin, double rmax, double E, double acc, double eps) {
  auto f = [&E](double r, pracprog::vector y) -> pracprog::vector {
    pracprog::vector res(2);
    res[0] = y[1];
    res[1] = -2 * ((1 / r) + E) * y[0];
    return res;
  };
  pracprog::vector initial(2);
  initial[0] = rmin - rmin * rmin;
  initial[1] = 1 - 2 * rmin;
  return std::get<1>(pracprog::driver(f, rmin, rmax, initial, 0.125, acc, eps))
      .back()[0];
}

int main(int argc, char *argv[]) {
  pracprog::vector newton_init(1);
  newton_init[0] = -0.6;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "rmax") {
      std::vector<double> rmaxs = {5, 6, 7, 8, 9, 10, 11, 12, 50};
      for (auto &rmax : rmaxs) {
        auto f = [&rmax](pracprog::vector &x) -> pracprog::vector {
          pracprog::vector res(1);
          res[0] = ME(standard_rmin, rmax, x[0], standard_acc, standard_eps);
          return res;
        };
        pracprog::vector root = pracprog::newton(f, newton_init, 1e-8);
        std::cout << rmax << root;
      }
      return EXIT_SUCCESS;
    } else if (arg == "rmin") {
      std::vector<double> rmins = {1.0,    0.1,     0.01,    0.001,
                                   0.0001, 0.00001, 0.000001};
      for (auto &rmin : rmins) {
        auto f = [&rmin](pracprog::vector &x) -> pracprog::vector {
          pracprog::vector res(1);
          res[0] = ME(rmin, standard_rmax, x[0], standard_acc, standard_eps);
          return res;
        };
        pracprog::vector root = pracprog::newton(f, newton_init, 1e-8);
        std::cout << rmin << root;
      }
      return EXIT_SUCCESS;
    } else if (arg == "acc") {
      std::vector<double> accs = {1.0,    0.1,     0.01,    0.001,
                                  0.0001, 0.00001, 0.000001};
      for (auto &acc : accs) {
        auto f = [&acc](pracprog::vector &x) -> pracprog::vector {
          pracprog::vector res(1);
          res[0] = ME(standard_rmin, standard_rmax, x[0], acc, standard_eps);
          return res;
        };
        pracprog::vector root = pracprog::newton(f, newton_init, 1e-8);
        std::cout << acc << root;
      }
      return EXIT_SUCCESS;
    } else if (arg == "eps") {
      std::vector<double> epss = {1.0,    0.1,     0.01,    0.001,
                                  0.0001, 0.00001, 0.000001};
      for (auto &eps : epss) {
        auto f = [&eps](pracprog::vector &x) -> pracprog::vector {
          pracprog::vector res(1);
          res[0] = ME(standard_rmin, standard_rmax, x[0], standard_acc, eps);
          return res;
        };
        pracprog::vector root = pracprog::newton(f, newton_init, 1e-8);
        std::cout << eps << root;
      }
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}
