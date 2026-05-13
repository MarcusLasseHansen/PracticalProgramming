#include "linalg_splines.hpp"

namespace pracprog {

    int binsearch(const pracprog::vector& x, double& z)
	{/* locates the interval for z by bisection */
	assert( z>=x[0] && z<=x[x.size()-1] );
	int i=0, j=x.size()-1;
	while(j-i>1){
		int mid=(i+j)/2;
		if(z>x[mid]) i=mid; else j=mid;
		}
	return i;
	}


    double linterp(pracprog::vector x, pracprog::vector y, double z){
	int i=binsearch(x,z);
  	double dx=x[i+1]-x[i];
  	assert(dx>0);
  	double dy=y[i+1]-y[i];
  	return y[i]+dy/dx*(z-x[i]);
  	}

    double linterpInteg(pracprog::vector x, pracprog::vector y, double z) {
      double result = 0;
      int i = binsearch(x,z);
      for (int idx = 0; idx < i; ++idx)
      {
        const double dx = x[idx+1] - x[idx];
        double p = (y[idx+1] - y[idx])/dx;
        result += y[idx] * dx + p * dx * dx / 2;
      }
      double dz = (z - x[i]);
      double p  = (y[i+1] - y[i]) / (x[i+1] - x[i]);
      result += y[i] * dz + p * dz * dz / 2.0;
      return result;
    }

      double quadterp::eval(double z) {
        assert(z>=x[0]&&z<=x[size-1]);
	int i=binsearch(x,z);
        double h = z-x[i];
        return y[i]+h*(b[i]+h*c[i]);
      }

      double quadterp::eval_int(double z) {
        assert(z>=x[0]&&z<=x[size-1]);
	int i=binsearch(x,z);
        double result = 0;
        for(int k = 0; k < i; k++) {
          double h = x[k+1] - x[k];
          result += y[k]*h + h*h*(0.5*b[k] + (1.0/3.0)*h*c[k]);
        }
        double h = z-x[i];
        return result + y[i]*h+h*h*(0.5*b[i]+(1.0/3.0)*h*c[i]);
      }

      double quadterp::eval_deriv(double z) {
        assert(z>=x[0]&&z<=x[size-1]);
	int i=binsearch(x,z);
        double result = 0;
        for(int k = 0; k < i; k++) {
          double h = x[k+1] - x[k];
          result += b[k] + 2*h*c[k];
        }
        double h = z-x[i];
        return (b[i]+2*h*c[i]);
      }

      double cubeterp::eval(double z) {
        assert(z>=x[0]&&z<=x[size-1]);
	int i=binsearch(x,z);
        double h = z-x[i];
        return y[i]+h*(b[i]+h*(c[i]+h*d[i]));
      }

      double cubeterp::eval_int(double z) {
        assert(z>=x[0]&&z<=x[size-1]);
	int i=binsearch(x,z);
        double result = 0;
        for(int k = 0; k < i; k++) {
          double h = x[k+1] - x[k];
          result += h*(y[k]+h*(0.5*b[k]+h*((1.0/3.0)*c[k]+0.25*h*d[k])));
        }
        double h = z-x[i];
        return result + h*(y[i]+h*(0.5*b[i]+h*((1.0/3.0)*c[i]+0.25*h*d[i])));
      }

      double cubeterp::eval_deriv(double z) {
        assert(z>=x[0]&&z<=x[size-1]);
	int i=binsearch(x,z);
        double result = 0;
        for(int k = 0; k < i; k++) {
          double h = x[k+1] - x[k];
          result += b[k]+h*(2*c[k]+3*h*d[k]);
        }
        double h = z-x[i];
        return b[i]+h*(2*c[i]+3*h*d[i]);;
      }
} /* namespace pracprog */
