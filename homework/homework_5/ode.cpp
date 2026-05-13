#include "ode.hpp"

namespace pracprog {

std::tuple<pracprog::vector, pracprog::vector>
rkstep12(std::function<pracprog::vector(double, pracprog::vector)>
             f /* the f from dy/dx=f(x,y) */
         ,
         double x /* the current value of the variable */
         ,
         pracprog::vector y /* the current value y(x) of the sought function */
         ,
         double h /* the step to be taken */
) {
  pracprog::vector k0 = f(x, y); /* embedded lower order formula (Euler) */
  pracprog::vector k1 =
      f(x + h / 2, y + k0 * (h / 2));  /* higher order formula (midpoint) */
  pracprog::vector yh = y + k1 * h;    /* y(x+h) estimate */
  pracprog::vector δy = (k1 - k0) * h; /* error estimate */
  return std::make_tuple(yh, δy);
}

std::tuple<std::vector<double>,std::vector<pracprog::vector>> driver(
	std::function<pracprog::vector(double,pracprog::vector)> F,/* the f from dy/dx=f(x,y) */
	double a,double b,           /* initial-point,final-point */
	pracprog::vector yinit,                /* y(initial-point) */
	double h,              /* initial step-size */
	double acc,             /* absolute accuracy goal */
	double eps              /* relative accuracy goal */
){
double x=a; pracprog::vector y(yinit);
std::vector<double> xlist; xlist.push_back(x);
std::vector<pracprog::vector> ylist; ylist.push_back(y);
do{
	if(x>=b) return std::make_tuple(xlist,ylist); /* job done */
	if(x+h>b) h=b-x;               /* last step should end at b */
	auto [yh,δy] = pracprog::rkstep12(F,x,y,h);
	double tol = (acc+eps*yh.norm()) * std::sqrt(h/(b-a));
	double err = δy.norm();
	if(err<=tol){ // accept step
		x+=h; y=yh;
		xlist.push_back(x);
		ylist.push_back(y);
		}
	if(err>0) h *= std::min( std::pow(tol/err,0.25)*0.95 , 2.0); // readjust stepsize
	else h*=2;
	}while(true);
}//driver


} /* namespace pracprog*/
