#pragma once
#include "../linalg/linalg.hpp"
#include <cmath>
#include <assert.h>

namespace pracprog {

  double linterp(pracprog::vector x, pracprog::vector y, double z);

  int binsearch(const pracprog::vector& x, double& z);

  double linterpInteg(pracprog::vector x, pracprog::vector y, double z);

  class quadterp {
    private:
      const size_t size;
      const pracprog::vector x;
      const pracprog::vector y;
      pracprog::vector c;
      pracprog::vector b;
    public:
      quadterp( size_t aSize
              , pracprog::vector aX
              , pracprog::vector aY)
              : size(aSize)
              , x(aX)
              , y(aY)
              , c(size-1)
              , b(size-1) {
                pracprog::vector p(size-1);
                pracprog::vector h(size-1);
                for (size_t i = 0; i < size - 1; i++) {
                    h[i] = x[i + 1] - x[i];
                    p[i] = (y[i + 1] - y[i]) / h[i];
                }
                c[0] = 0.0;
                for (size_t i = 0; i < size - 2; i++) {
                    c[i + 1] = (p[i + 1] - p[i] - c[i] * h[i]) / h[i + 1];
                }
                c[size - 2] /= 2.0;
                for (size_t i = size - 3; i < size - 2; i--) {
                    c[i] = (p[i + 1] - p[i] - c[i + 1] * h[i + 1]) / h[i];
                    if (i == 0) break;
                }
                for (size_t i = 0; i < size - 1; i++) {
                    b[i] = p[i] - c[i] * h[i];
                }
              }
      const size_t &get_size() { return size; };
      const pracprog::vector &get_x() const { return x; };
      const pracprog::vector &get_y() const { return y; };
      const pracprog::vector &get_c() const { return c; };
      const pracprog::vector &get_b() const { return b; };
      double eval(double z);

      double eval_int(double z);

      double eval_deriv(double z);
    };

    class cubeterp {
    private:
      const size_t size;
      const pracprog::vector x;
      const pracprog::vector y;
      pracprog::vector b;
      pracprog::vector c;
      pracprog::vector d;
    public:
      cubeterp( size_t aSize
              , pracprog::vector aX
              , pracprog::vector aY)
              : size(aSize)
              , x(aX)
              , y(aY)
              , b(size)
              , c(size-1)
              , d(size-1) {
                pracprog::vector p(size-1);
                pracprog::vector h(size-1);
                for (size_t i = 0; i<size-1;i++) {
                  h[i]=x[i+1]-x[i];
                  assert(h[i]>0);
                }
                for (size_t i = 0; i<size-1;i++) {
                  p[i]=(y[i+1]-y[i])/h[i];
                }
                pracprog::vector D(size), Q(size), B(size);
                D[0]=2;
                Q[0]=1;
                for (size_t i = 0; i<size-2;i++) {
                  D[i+1]=2*h[i]/h[i+1]+2;
                }
                D[size-1] = 2;
                for (size_t i = 0; i<size-2;i++) {
                  Q[i+1]=h[i]/h[i+1];
                }
                for (size_t i = 0; i<size-2;i++) {
                  B[i+1] = 3 * (p[i] + p[i+1] * h[i]/h[i+1]);
                }
                B[0]=3*p[0];
                B[size-1]=3*p[size-2];
                for (size_t i = 1; i<size;i++) {
                  D[i]-=Q[i-1]/D[i-1];
                  B[i]-=B[i-1]/D[i-1];
                }
                b[size-1]=B[size-1]/D[size-1];
                for (int i=static_cast<int>(size)-2;i>=0;i--) {
                  b[i]=(B[i]-Q[i]*b[i+1])/D[i];
                }
                for (size_t i = 0; i<size-1;i++) {
                  c[i] = (-2*b[i] - b[i+1] + 3*p[i]) / h[i];
                  d[i]=(b[i]+b[i+1]-2*p[i])/h[i]/h[i];
                }
              }
      const size_t &get_size() { return size; };
      const pracprog::vector &get_x() const { return x; };
      const pracprog::vector &get_y() const { return y; };
      const pracprog::vector &get_c() const { return c; };
      const pracprog::vector &get_b() const { return b; };
      const pracprog::vector &get_d() const { return d; };
      double eval(double z);

      double eval_int(double z);

      double eval_deriv(double z);
    };
} /* namespace pracprog */
