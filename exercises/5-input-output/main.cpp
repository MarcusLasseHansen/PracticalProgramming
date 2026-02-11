#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void print_header(std::ostream &os) {
  os << std::setw(15) << "Number" << std::setw(20) << "sin(Number)"
     << std::setw(20) << "cos(Number)" << std::endl;
  os << std::string(55, '-') << std::endl;
}

void print_value(std::ostream &os, double x) {
  os << std::setw(15) << x << std::setw(20) << std::sin(x) << std::setw(20)
     << std::cos(x) << std::endl;
}

int main(int argc, char *argv[]) {

  std::vector<double> cmd_numbers;
  std::string infile = "";
  std::string outfile = "";

  // Parse command-line arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-n" && i + 1 < argc) {
      cmd_numbers.push_back(std::stod(argv[++i]));
    }
    else if (arg == "--input" && i + 1 < argc) {
      infile = argv[++i];
    }
    else if (arg == "--output" && i + 1 < argc) {
      outfile = argv[++i];
    }
  }

  // Task 3
  if (!infile.empty() && !outfile.empty()) {

    std::ifstream input(infile);
    std::ofstream output(outfile);

    if (!input.is_open() || !output.is_open()) {
      std::cerr << "Error opening files: " << infile << " " << outfile
                << std::endl;
      return EXIT_FAILURE;
    }

    print_header(output);

    double x;
    while (input >> x) {
      print_value(output, x);
    }

    input.close();
    output.close();
    return EXIT_SUCCESS;
  }

  // Task 1
  if (!cmd_numbers.empty()) {

    print_header(std::cout);

    for (double n : cmd_numbers) {
      print_value(std::cout, n);
    }

    return EXIT_SUCCESS;
  }

  // Task 2
  print_header(std::cout);

  double x;
  while (std::cin >> x) {
    print_value(std::cout, x);
  }

  return EXIT_SUCCESS;
}
