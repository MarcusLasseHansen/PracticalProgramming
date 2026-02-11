#pragma once
#include <cmath>
#include <iostream>

template <typename T> class vec {
private:
  T x;
  T y;
  T z;

public:
  vec(T x, T y, T z) : x(x), y(y), z(z) {}
  vec() : vec(0, 0, 0) {}                // default
  vec(const vec &) = default;            // copy
  vec(vec &&) = default;                 // move
  ~vec() = default;                      // destructor
  vec &operator=(const vec &) = default; // copy assignment
  vec &operator=(vec &&) = default;      // move assignment
  void print() const {
    std::cout << this->x << "\n" << this->y << "\n" << this->z << std::endl;
  }
  T getX() const { return this->x; }
  T getY() const { return this->y; }
  T getZ() const { return this->z; }

  vec cross(const vec &v) const {
    return vec<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }
  T dot(const vec &v) const { return x * v.x + y * v.y + z * v.z; }

  vec &operator+=(const vec &v) {
    this->x = this->x + v.getX();
    this->y = this->y + v.getY();
    this->z = this->z + v.getZ();
    return *this;
  }
  vec &operator-=(const vec &v) {
    this->x = this->x - v.getX();
    this->y = this->y - v.getY();
    this->z = this->z - v.getZ();
    return *this;
  }
  vec &operator*=(const T scalar) {
    this->x = this->x * scalar;
    this->y = this->y * scalar;
    this->z = this->z * scalar;
    return *this;
  }
  vec &operator/=(const T scalar) {
    this->x = this->x / scalar;
    this->y = this->y / scalar;
    this->z = this->z / scalar;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const vec &v) {
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  }
};

template <typename T> vec<T> operator-(const vec<T> &a) { return a * static_cast<T>(-1); }
template <typename T> vec<T> operator-(const vec<T> &a, const vec<T> &b) {
  return vec<T>(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}
template <typename T> vec<T> operator+(const vec<T> &a, const vec<T> &b) {
  return vec<T>(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}
template <typename T> vec<T> operator*(const vec<T> &a, T b) {
  return vec<T>(a.getX() * b, a.getY() * b, a.getZ() * b);
}
template <typename T> vec<T> operator*(T a, const vec<T> &b) {
  return vec<T>(b.getX() * a, b.getY() * a, b.getZ() * a);
}
template <typename T> vec<T> operator/(const vec<T> &a, T b) {
  return vec<T>(a.getX() / b, a.getY() / b, a.getZ() * b);
}

template <typename T>
bool approx(const vec<T> &a, const vec<T> &b, T acc = 1e-9, T eps = 1e-9) {
  T diffX = std::abs(a.getX() - b.getX());
  T diffY = std::abs(a.getY() - b.getY());
  T diffZ = std::abs(a.getZ() - b.getZ());
  if (diffX <= acc && diffY <= acc && diffZ <= acc)
    return true; // absolute tolerance
  T max_abX = std::max(std::abs(a.getX()), std::abs(b.getX()));
  T max_abY = std::max(std::abs(a.getY()), std::abs(b.getY()));
  T max_abZ = std::max(std::abs(a.getZ()), std::abs(b.getZ()));
  return (diffX <= eps * max_abX && diffY <= eps * max_abY &&
          diffZ <= eps * max_abZ); // relative tolerance
}
