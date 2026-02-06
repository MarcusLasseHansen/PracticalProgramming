#pragma once
#include <iostream>
#include <cmath>

class vec {
private:
  double x;
  double y;
  double z;
public:
  vec(double x, double y, double z) : x(x), y(y), z(z) {}
  vec() : vec(0, 0, 0) {}                                    // default
  vec(const vec&) = default;                                 // copy
  vec(vec&&) = default;                                      // move
  ~vec() = default;                                          // destructor
  vec& operator=(const vec&) = default;                     // copy assignment
  vec& operator=(vec&&) = default;                          // move assignment
  void print() const;
  double getX() const;
  double getY() const;
  double getZ() const;

  vec cross(const vec& v) const;
  double dot(const vec& v) const;

  vec& operator+=(const vec& v);
  vec& operator-=(const vec& v);
  vec& operator*=(const double scalar);
  vec& operator/=(const double scalar);

  friend std::ostream& operator<<(std::ostream& os, const vec& v);
};

vec operator-(const vec& a);
vec operator-(const vec& a, const vec& b);
vec operator+(const vec& a, const vec& b);
vec operator*(const vec& a, double b);
vec operator*(double a, const vec& b);
vec operator/(const vec& a, double b);

bool approx(const vec &a, const vec &b, double acc = 1e-9, double eps = 1e-9);
