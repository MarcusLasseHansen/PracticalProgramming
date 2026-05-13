#pragma once
#include "../linalg/linalg.hpp"
#include <functional>
#include <algorithm>


namespace pracprog {

std::tuple<pracprog::vector, pracprog::vector>
rkstep12( std::function<pracprog::vector(double, pracprog::vector)>
        , double /* the current value of the variable */
        , pracprog::vector /* the current value y(x) of the sought function */
        , double
);

std::tuple<std::vector<double>,std::vector<pracprog::vector>> driver(
	std::function<pracprog::vector(double,pracprog::vector)> F,/* the f from dy/dx=f(x,y) */
	double a,double b,           /* initial-point,final-point */
	pracprog::vector yinit,                /* y(initial-point) */
	double h=0.125,              /* initial step-size */
	double acc=0.01,             /* absolute accuracy goal */
	double eps=0.01              /* relative accuracy goal */
);
} /* namespace pracprog */
