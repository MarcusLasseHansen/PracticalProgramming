#include "vec.hpp"
#include <random>

template <typename T>
bool approx(T a, T b, T acc = 1e-9, T eps = 1e-9) {
  T diff = std::abs(a - b);
  if (diff <= acc)
    return true; // absolute tolerance
  T max_ab = std::max(std::abs(a), std::abs(b));
  return diff <= eps * max_ab; // relative tolerance
}

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  vec u(dis(gen), dis(gen), dis(gen));
  vec v(dis(gen), dis(gen), dis(gen));

  std::cout << "u=";
  u.print();
  std::cout << "v=";
  v.print();
  std::cout << std::endl;

  vec<double> t;

  // unary -
  t = vec(-u.getX(), -u.getY(), -u.getZ());
  (-u).print();
  t.print();
  if (approx(t, -u))
    std::cout << "test 'unary -' passed\n\n";

  // operator -
  t = vec(u.getX() - v.getX(), u.getY() - v.getY(), u.getZ() - v.getZ());
  (u - v).print();
  t.print();
  if (approx(t, u - v))
    std::cout << "test 'operator-' passed\n\n";

  // operator +
  t = vec(u.getX() + v.getX(), u.getY() + v.getY(), u.getZ() + v.getZ());
  (u + v).print();
  t.print();
  if (approx(t, u + v))
    std::cout << "test 'operator+' passed\n\n";

  // scalar multiplication
  double c = dis(gen);
  t = vec(u.getX() * c, u.getY() * c, u.getZ() * c);
  vec tmp = u * c;
  tmp.print();
  t.print();
  if (approx(t, u * c))
    std::cout << "test 'operator*' passed\n\n";

  // dot product
  double d = u.getX() * v.getX() + u.getY() * v.getY() + u.getZ() * v.getZ();
  std::cout << (u.dot(v)) << std::endl;
  std::cout << d << std::endl;
  if (approx(d, u.dot(v)))
    std::cout << "test 'dot product' passed\n\n";

  // cross product
  vec expected(u.getY() * v.getZ() - u.getZ() * v.getY(),
               u.getZ() * v.getX() - u.getX() * v.getZ(),
               u.getX() * v.getY() - u.getY() * v.getX());

  std::cout << u.cross(v) << "\n" << expected << std::endl;

  if (approx(u.cross(v).getX(), expected.getX()) && approx(u.cross(v).getY(), expected.getY()) &&
      approx(u.cross(v).getZ(), expected.getZ())) {
    std::cout << "test 'cross product' passed\n\n";
  }
  return 0;
}
