#include <cmath>
#include <iostream>
#include <numbers>
#include <vector>

double erf(double x) {
  // single precision error function (Abramowitz and Stegun, from Wikipedia)
  if (x < 0)
    return -erf(-x);
  std::vector<double> a{0.254829592, -0.284496736, 1.421413741, -1.453152027,
                        1.061405429};
  double t = 1 / (1 + 0.3275911 * x);
  double sum =
      t *
      (a[0] +
       t * (a[1] + t * (a[2] + t * (a[3] + t * a[4])))); /* the right thing */
  return 1 - sum * std::exp(-x * x);
}

double sgamma(double x) {
  if (x < 0)
    return std::numbers::pi / std::sin(std::numbers::pi * x) / sgamma(1 - x);
  if (x < 9)
    return sgamma(x + 1) / x;
  double lnsgamma = std::log(2 * std::numbers::pi) / 2 +
                    (x - 0.5) * std::log(x) - x + (1.0 / 12) / x -
                    (1.0 / 360) / (x * x * x) +
                    (1.0 / 1260) / (x * x * x * x * x);
  return std::exp(lnsgamma);
}

double lngamma(double x) {
  if (x <= 0)
    return std::numeric_limits<double>::quiet_NaN();
  if (x < 9)
    return lngamma(x + 1) - std::log(x);
  return x * std::log(x + 1 / (12 * x - 1 / x / 10)) - x +
         std::log(2 * std::numbers::pi / x) / 2;
}

int main(int argc, char *argv[]) {
  double dx = 0.001, xmin = 0, xmax = 3.5;
  unsigned int plot = 0;
  for (int i = 0; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--max" && i + 1 < argc) {
      xmax = std::stod(argv[i + 1]);
    } else if (arg == "--min" && i + 1 < argc) {
      xmin = std::stod(argv[i + 1]);
    } else if (arg == "--dx" && i + 1 < argc) {
      dx = std::stod(argv[i + 1]);
    } else if (arg == "--function" && i + 1 < argc) {
      plot = std::stoi(argv[i + 1]);
    } else if (arg == "--help") {
      std::cout
          << "Possible arguments:\n --max DOUBLE (Sets max of range)\n --min "
          << "DOUBLE (Sets min of range)\n --dx DOUBLE (Sets steps between "
          << "points)\n --function INT (Sets what function to plot)"
          << "\n 0=erf" << "\n 0=sgamma" << "\n 0=lngamma" << std::endl;
      return EXIT_FAILURE;
    }
  }

  std::cout << std::scientific;
  switch (plot) {
  case 0: {
    for (double x = xmin; x <= xmax; x += dx) {
      std::cout << x << " " << erf(x) << "\n";
    }
    break;
  }
  case 1: {
    for (double x = xmin; x <= xmax; x += dx) {
      std::cout << x << " " << sgamma(x) << "\n";
    }
    break;
  }
  case 2: {
    for (double x = xmin; x <= xmax; x += dx) {
      std::cout << x << " " << lngamma(x) << "\n";
    }
    break;
  }
  default: {
    std::cout << "Failed to find matching function to plot\n";
    return EXIT_FAILURE;
  }
  }
  return EXIT_SUCCESS;
}
