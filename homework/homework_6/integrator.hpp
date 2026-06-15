#pragma once
#include <functional>
#include <limits>
#include <cmath>

namespace pracprog {
std::pair<double,size_t> integrate_with_count(std::function<double(double)> f
                , double a
                , double b
                , double acc = 0.001
                , double eps = 0.001                );

double integrate(std::function<double(double)> f
                , double a
                , double b
                , double acc = 0.001
                , double eps = 0.001
                , double f2 = std::numeric_limits<double>::quiet_NaN()
                , double f3 = std::numeric_limits<double>::quiet_NaN()
                , unsigned int depth = 0
                );

std::pair<double,double> integrate_error_prop(std::function<double(double)> f
                , double a
                , double b
                , double acc = 0.001
                , double eps = 0.001
                , double f2 = std::numeric_limits<double>::quiet_NaN()
                , double f3 = std::numeric_limits<double>::quiet_NaN()
                , unsigned int depth = 0
                );


std::pair<double,size_t> cc_vt_integral_with_count(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc = 0.001
                    , double eps = 0.001
                    );

double cc_vt_integral(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc = 0.001
                    , double eps = 0.001
                    );

std::pair<double,double> cc_vt_integral_error_prop(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc = 0.001
                    , double eps = 0.001
                    );

std::pair<double,double> generalized_integral_error_prop(std::function<double(double)> f
                    , double a = std::numeric_limits<double>::quiet_NaN()
                    , double b = std::numeric_limits<double>::quiet_NaN()
                    , double acc = 0.001
                    , double eps = 0.001
                    );
double generalized_integral(std::function<double(double)> f
                    , double a = std::numeric_limits<double>::quiet_NaN()
                    , double b = std::numeric_limits<double>::quiet_NaN()
                    , double acc = 0.001
                    , double eps = 0.001
                    );
std::pair<double,size_t> generalized_integral_with_count(std::function<double(double)> f
                    , double a = std::numeric_limits<double>::quiet_NaN()
                    , double b = std::numeric_limits<double>::quiet_NaN()
                    , double acc = 0.001
                    , double eps = 0.001
                    );

} /* namespace pracprog */
