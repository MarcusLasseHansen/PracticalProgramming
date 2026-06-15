#include "integrator.hpp"

constexpr unsigned int max_depth = 30;

std::pair<double,size_t> pracprog::integrate_with_count(std::function<double(double)> f
                , double a
                , double b
                , double acc
                , double eps
                ) {
  size_t calls = 0;
  auto f_counted = [&](double x) {
    ++calls;
    return f(x);
  };
  return std::make_pair(pracprog::integrate(f_counted,a,b,acc,eps),calls);
}

double pracprog::integrate(std::function<double(double)> f
                , double a
                , double b
                , double acc
                , double eps
                , double f2
                , double f3
                , unsigned int depth
                ) {
  double h = b-a;
  if (f2 != f2) {
    f2=f(a+2*h/6);
    f3=f(a+4*h/6);
  }
  double f1=f(a+h/6);
  double f4=f(a+5*h/6);
  double Q = (2*f1+f2+f3+2*f4)/6*(b-a);
  double q = (f1+f2+f3+f4)/4*(b-a);
  double err = std::abs(Q-q);
  double tol = acc+eps*std::abs(Q);
  if (depth > max_depth) return Q; // ← bail out HERE, after Q is computed
  if (err < tol) {
    return Q;
  }
  else {
    return integrate(f,a,(a+b)/2,acc/std::sqrt(2),eps,f1,f2,depth+1) +
           integrate(f,(a+b)/2,b,acc/std::sqrt(2),eps,f3,f4,depth+1);
  }
}

std::pair<double,double> pracprog::integrate_error_prop(std::function<double(double)> f
                , double a
                , double b
                , double acc
                , double eps
                , double f2
                , double f3
                , unsigned int depth
                ) {

    double h = b-a;

    if (std::isnan(f2)) {
        f2 = f(a + 2*h/6);
        f3 = f(a + 4*h/6);
    }

    double f1 = f(a + h/6);
    double f4 = f(a + 5*h/6);

    double Q = (2*f1 + f2 + f3 + 2*f4)/6 * (b-a);
    double q = (f1 + f2 + f3 + f4)/4 * (b-a);

    double err = std::abs(Q-q);
    double tol = acc + eps*std::abs(Q);

    if (err < tol) {
        return {Q, err};
    }

    if (depth > max_depth) {
      return {Q, err};
    }

    auto left = integrate_error_prop(
        f,a,(a+b)/2,
        acc/std::sqrt(2),eps,
        f1,f2,depth+1
    );

    auto right = integrate_error_prop(
        f,(a+b)/2,b,
        acc/std::sqrt(2),eps,
        f3,f4, depth+1
    );

    return {
        left.first + right.first,
        std::sqrt(
            left.second*left.second +
            right.second*right.second
        )
    };
}

std::pair<double,size_t> pracprog::cc_vt_integral_with_count(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc
                    , double eps
                    ) {
  auto new_f = [a,b,f](double phi) -> double {return
    f((a+b)/2 + (b-a)/2*std::cos(phi))*std::sin(phi)*(b-a)/2;
  };
  return pracprog::integrate_with_count(new_f,0,std::numbers::pi,acc,eps);
}

double pracprog::cc_vt_integral(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc
                    , double eps
                    ) {
  auto new_f = [a,b,f](double phi) -> double {return
    f((a+b)/2 + (b-a)/2*std::cos(phi))*std::sin(phi)*(b-a)/2;
  };
  return pracprog::integrate(new_f,0,std::numbers::pi,acc,eps);
}

std::pair<double,double> pracprog::cc_vt_integral_error_prop(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc
                    , double eps
                    ) {
  auto new_f = [a,b,f](double phi) -> double {return
    f((a+b)/2 + (b-a)/2*std::cos(phi))*std::sin(phi)*(b-a)/2;
  };
  return pracprog::integrate_error_prop(new_f,0,std::numbers::pi,acc,eps);
}


double pracprog::generalized_integral(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc
                    , double eps
                    ) {
  if (a!=a && b!=b) { // both inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(t/(1-(t*t)))*((1+(t*t))/((1-(t*t))*(1-(t*t))));
    };
    return pracprog::cc_vt_integral(new_f,-1,1,acc,eps);
  }
  if (a!=a && b==b) { // a is inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(b+(t/(1+t))) * (1/((1+t)*(1+t)));
    };
    return pracprog::cc_vt_integral(new_f,-1,0,acc,eps);
  }
  if (a==a && b!=b) { // b is inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(a+(t/(1-t))) * (1/((1-t)*(1-t)));
    };
    return pracprog::cc_vt_integral(new_f,0,1,acc,eps);
  }
  return pracprog::cc_vt_integral(f,a,b,acc,eps);
}

std::pair<double,double> pracprog::generalized_integral_error_prop(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc
                    , double eps
                    ) {
  if (a!=a && b!=b) { // both inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(t/(1-(t*t)))*((1+(t*t))/((1-(t*t))*(1-(t*t))));
    };
    return pracprog::cc_vt_integral_error_prop(new_f,-1,1,acc,eps);
  }
  if (a!=a && b==b) { // a is inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(b+(t/(1+t))) * (1/((1+t)*(1+t)));
    };
    return pracprog::cc_vt_integral_error_prop(new_f,-1,0,acc,eps);
  }
  if (a==a && b!=b) { // b is inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(a+(t/(1-t))) * (1/((1-t)*(1-t)));
    };
    return pracprog::cc_vt_integral_error_prop(new_f,0,1,acc,eps);
  }
  return pracprog::cc_vt_integral_error_prop(f,a,b,acc,eps);
}

std::pair<double,size_t> pracprog::generalized_integral_with_count(std::function<double(double)> f
                    , double a
                    , double b
                    , double acc
                    , double eps
                    ) {
  if (a!=a && b!=b) { // both inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(t/(1-(t*t)))*((1+(t*t))/((1-(t*t))*(1-(t*t))));
    };
    return pracprog::cc_vt_integral_with_count(new_f,-1,1,acc,eps);
  }
  if (a!=a && b==b) { // a is inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(b+(t/(1+t))) * (1/((1+t)*(1+t)));
    };
    return pracprog::cc_vt_integral_with_count(new_f,-1,0,acc,eps);
  }
  if (a==a && b!=b) { // b is inf limit
    auto new_f = [a,b,f](double t) -> double {return
      f(a+(t/(1-t))) * (1/((1-t)*(1-t)));
    };
    return pracprog::cc_vt_integral_with_count(new_f,0,1,acc,eps);
  }
  return pracprog::cc_vt_integral_with_count(f,a,b,acc,eps);
}
