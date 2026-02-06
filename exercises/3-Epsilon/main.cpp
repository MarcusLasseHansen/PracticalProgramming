#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

bool approx(double a, double b, double acc=1e-9, double eps=1e-9) {
  // absolute requirement
  if (std::abs(a-b) <= acc) { return true; }

  // relative requirement
  if (std::abs(a-b)/(std::max(std::abs(a),std::abs(b))) <= eps) { return true; }

  return false;
}

int exercise_1() {
  std::cout << "Exercise 1:" << std::endl;
  float f = 1.0f;
  while ((float)(1.0f + f) != 1.0f) {
    f /= 2.0f;
  }
  f *= 2.0f;
  double d = 1.0d;
  while ((double)(1.0d + d) != 1.0d) {
    d /= 2.0d;
  }
  d *= 2.0d;
  long double l = 1.0L;
  while ((long double)(1.0L + l) != 1.0L) {
    l /= 2.0L;
  }
  l *= 2.0L;
  std::cout << "From while loop:\n";
  std::printf("      float eps=%g\n", f);
  std::printf("     double eps=%g\n", d);
  std::printf("long double eps=%Lg\n", l);
  std::cout << "From <limits>:\n";
  std::cout << "      float eps=" << std::numeric_limits<float>::epsilon()
            << "\n";
  std::cout << "     double eps=" << std::numeric_limits<double>::epsilon()
            << "\n";
  std::cout << "long double eps=" << std::numeric_limits<long double>::epsilon()
            << "\n";
  std::cout << "std::pow(2,-52): " << std::pow(2, -52) << "\n"
            << "std::pow(2,-23):" << std::pow(2, -23) << std::endl;
  // You see in the output that the numbers match as expected
  return 0;
}

int exercise_2() {
  std::cout << "Exercise 2:" << std::endl;
  // This exercise will be done with double precision
  double epsilon = std::numeric_limits<double>::epsilon();
  double tiny = epsilon / 2;
  double a = 1 + tiny + tiny;
  double b = tiny + tiny + 1;
  std::cout << "a==b ? " << (a == b ? "true" : "false") << "\n";
  std::cout << "a>1  ? " << (a > 1 ? "true" : "false") << "\n";
  std::cout << "b>1  ? " << (b > 1 ? "true" : "false") << "\n";
  /* Since operations are done from left to right we get the following:
   * a = (( 1 + tiny ) + tiny)
   * since 1 + tiny = 1 since tiny < epsilon, we get that the above keeps
   * rounding to 1 b = ((tiny + tiny) + 1) becomes b = epsilon + 1 which
   * evaluates to something different than 1.
   */
  return 0;
}

int exercise_3() {
  std::cout << "Exercise 3:" << std::endl;
  double d1 = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1;
  double d2 = 8 * 0.1;
  std::cout << "d1==d2? " << (d1 == d2 ? "true" : "false") << "\n";
  std::cout << std::fixed << std::setprecision(17);
  std::cout << "d1=" << d1 << "\n";
  std::cout << "d2=" << d2 << "\n";
  std::cout << "d1≃d2? " << (approx(d1,d2) ? "true" : "false") << std::endl;
  return 0;
}

int main() {
  exercise_1();
  exercise_2();
  exercise_3();
  return 0;
}
