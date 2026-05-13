#include "ode.hpp"
#include "../homework_4/linalg_splines.hpp"

static pracprog::vector vec12(double a, double b, double c, double d, double e,
                              double f, double g, double h, double i, double j,
                              double k, double l) {
  pracprog::vector v(12);
  v[0] = a;
  v[1] = b;
  v[2] = c;
  v[3] = d;
  v[4] = e;
  v[5] = f;
  v[6] = g;
  v[7] = h;
  v[8] = i;
  v[9] = j;
  v[10] = k;
  v[11] = l;

  return v;
}

int main() {
  auto f = [](double, pracprog::vector y) -> pracprog::vector {
    pracprog::vector res(12);
    res[6] = y[0];
    res[7] = y[1];
    res[8] = y[2];
    res[9] = y[3];
    res[10] = y[4];
    res[11] = y[5];
    auto update_velocity = [&](int i, int j, double &ax, double &ay) {
      const int ix = 6 + 2 * i;
      const int iy = ix + 1;
      const int jx = 6 + 2 * j;
      const int jy = jx + 1;

      const double dx = y[jx] - y[ix];
      const double dy = y[jy] - y[iy];

      const double r2 = dx * dx + dy * dy;
      const double inv_r3 = 1.0 / (r2 * std::sqrt(r2)); // equivalent to r^3

      ax += dx * inv_r3;
      ay += dy * inv_r3;
    };
    {
      double ax = 0.0, ay = 0.0;
      update_velocity(0, 1, ax, ay);
      update_velocity(0, 2, ax, ay);
      res[0] = ax;
      res[1] = ay;
    }

    {
      double ax = 0.0, ay = 0.0;
      update_velocity(1, 0, ax, ay);
      update_velocity(1, 2, ax, ay);
      res[2] = ax;
      res[3] = ay;
    }
    {
      double ax = 0.0, ay = 0.0;
      update_velocity(2, 0, ax, ay);
      update_velocity(2, 1, ax, ay);
      res[4] = ax;
      res[5] = ay;
    }

    return res;
  };
  auto [xs, ys] = pracprog::driver(
      f, 0, 20,
      vec12(0.93240737/2
                 ,0.86473146/2
                 ,0.93240737/2
                 ,0.86473146/2
                 ,-0.93240737
                 ,-0.86473146
                 ,0.97000436
                 ,-0.24308753
                 ,-0.97000436
                 ,0.24308753
                 ,0
                 ,0));

  for (unsigned int i = 0; i < xs.size(); i++) {
    std::cout << xs[i] << " " << ys[i][6] << " " << ys[i][7] << " " << ys[i][8]
              << " " << ys[i][9] << " " << ys[i][10] << " " << ys[i][11]
              << "\n";
  }

  std::cout << std::endl;
}
