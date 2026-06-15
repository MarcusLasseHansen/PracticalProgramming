#include "minimization.hpp"
#include <iomanip>
#include <iostream>
#include <vector>

int main(int argc, char * argv[]) {
  bool plot_out = false;
  for(int i = 0; i < argc ; i++)
  {
    std::string arg(argv[i]);
    if(arg == "--plot_output")
    {
      plot_out = true;
      break;
    }
  }
  std::vector<double> energy, signal, error;
  double x, y, z;
  while (std::cin >> x >> y >> z) {
    energy.push_back(x);
    signal.push_back(y);
    error.push_back(z);
  }

  auto BW = [](double E, double m, double Gamma, double A) {
    return A / ((E - m) * (E - m) + Gamma * Gamma / 4.0);
  };

  auto Deviation = [&](const pracprog::vector &p) {
    double m = p[0], Gamma = p[1], A = p[2];
    double sum = 0.0;
    for (size_t i = 0; i < energy.size(); i++) {
      double residual = (BW(energy[i], m, Gamma, A) - signal[i]) / error[i];
      sum += residual * residual;
    }
    return sum;
  };
  pracprog::vector x_vec(3);
  x_vec[0] = 130; // m
  x_vec[1] = 4;   // gamma
  x_vec[2] = 5;  // A
  auto [res, steps] = pracprog::newton(Deviation,x_vec, 1e-6);
  if (plot_out) {
    for(unsigned int i = 0; i < energy.size(); ++i) {
    std::cout << energy[i] << " " << signal[i] << " " << BW(energy[i], res[0], res[1], res[2]) << "\n";
    }
    std::cout << std::endl;
  } else {
  std::cout << "D(start) = " << Deviation(x_vec) << "\n";
  std::cout << std::setprecision(18) << std::fixed
            << "m: " << res[0] << " "
            << "gamma: " << res[1] << " "
            << "A: " << res[2] << "\n"
            << "Deviation of minimization results: " << Deviation(res) << std::endl;
  }
  return EXIT_SUCCESS;
}
