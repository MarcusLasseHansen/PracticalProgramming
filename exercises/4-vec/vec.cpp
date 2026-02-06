#include "vec.hpp"

double vec::getX() const { return this->x; }
double vec::getY() const { return this->y; }
double vec::getZ() const { return this->z; }

void vec::print() const {
  std::cout << this->x << "\n" << this->y << "\n" << this->z << std::endl;
}

vec &vec::operator+=(const vec &v) {
  this->x = this->x + v.getX();
  this->y = this->y + v.getY();
  this->z = this->z + v.getZ();
  return *this;
}
vec &vec::operator-=(const vec &v) {
  this->x = this->x - v.getX();
  this->y = this->y - v.getY();
  this->z = this->z - v.getZ();
  return *this;
}
vec &vec::operator*=(const double scalar) {
  this->x = this->x * scalar;
  this->y = this->y * scalar;
  this->z = this->z * scalar;
  return *this;
}
vec &vec::operator/=(const double scalar) {
  this->x = this->x / scalar;
  this->y = this->y / scalar;
  this->z = this->z / scalar;
  return *this;
}

vec operator-(const vec &a) { return a * (-1); }

vec operator-(const vec &a, const vec &b) {
  return vec(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}

vec operator+(const vec &a, const vec &b) {
  return vec(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

vec operator*(const vec& a, double b) {
  return vec(a.getX()*b,a.getY()*b,a.getZ()*b);
}

vec operator*(double a, const vec& b) {
  return vec(b.getX()*a,b.getY()*a,b.getZ()*a);
}


// Assuming exceptions will be handled externally from this implementation
// else one could add a check for singularities
vec operator/(const vec& a, double b) {
  return vec(a.getX()/b,a.getY()/b,a.getZ()*b);
}

vec vec::cross(const vec &v) const {
  return vec(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double vec::dot(const vec &v) const { return x * v.x + y * v.y + z * v.z; }

bool approx(const vec &a, const vec &b, double acc, double eps) {
  double diffX = std::abs(a.getX() - b.getX());
  double diffY = std::abs(a.getY() - b.getY());
  double diffZ = std::abs(a.getZ() - b.getZ());
  if (diffX <= acc && diffY <= acc && diffZ <= acc)
    return true; // absolute tolerance
  double max_abX = std::max(std::abs(a.getX()), std::abs(b.getX()));
  double max_abY = std::max(std::abs(a.getY()), std::abs(b.getY()));
  double max_abZ = std::max(std::abs(a.getZ()), std::abs(b.getZ()));
  return (diffX <= eps * max_abX && diffY <= eps * max_abY &&
          diffZ <= eps * max_abZ); // relative tolerance
}

std::ostream &operator<<(std::ostream &os, const vec &v) {
  return os << "(" << v.x << "," << v.y << "," << v.z << ")";
}
