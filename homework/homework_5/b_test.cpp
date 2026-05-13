#include "ode.hpp"

static pracprog::vector vec2(double a, double b) {
  pracprog::vector v(2);
  v[0] = a;
  v[1] = b;
  return v;
}

void test_1() {
  auto f = [](double, pracprog::vector y) -> pracprog::vector {
    return vec2(y[1],1-y[0]);
  };
  auto [angles,us] = pracprog::driver(f,0,200,vec2(1.0,0.0));
  for (unsigned int i = 0; i < angles.size(); i++) {
    std::cout << angles[i] << " " << us[i][0] << "\n";
  }
  std::cout << std::endl;
}

void test_2() {
  auto f = [](double, pracprog::vector y) -> pracprog::vector {
    return vec2(y[1],1-y[0]);
  };
  auto [angles,us] = pracprog::driver(f,0,200,vec2(1.0,-0.5));
  for (unsigned int i = 0; i < angles.size(); i++) {
    std::cout << angles[i] << " " << us[i][0] << "\n";
  }
  std::cout << std::endl;
}

void test_3() {
  auto f = [](double, pracprog::vector y) -> pracprog::vector {
    return vec2(y[1],1-y[0]+0.01*y[0]*y[0]);
  };
  auto [angles,us] = pracprog::driver(f,0,1000,vec2(1.0,-0.5));
  for (unsigned int i = 0; i < angles.size(); i++) {
    std::cout << angles[i] << " " << us[i][0] << "\n";
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    if (std::string_view(argv[i]) == "1") {
      test_1();
      break;
    } else if (std::string_view(argv[i]) == "2") {
      test_2();
      break;
    } else if (std::string_view(argv[i]) == "3") {
      test_3();
      break;
    }
  }

  return EXIT_SUCCESS;
}
