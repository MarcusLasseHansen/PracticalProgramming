#include "../homework_9/minimization.hpp"
#include "../linalg/linalg.hpp"
#include <cmath>
#include <functional>
#include <random>

/*
 * I could not for the life of me get this to work. So i ended up
 * uploading this file to claude AI. It suggested several improvements
 * I have commented throughout where the AI improvements have been made.
 * Before this it did not minimize the cost function properly.
 *
 */

namespace pracprog {
struct ann {
  int n;
  double xmin, xmax;
  std::function<double(double)> f;
  pracprog::vector p; /* parameters: (a_i, log(b_i), w_i) per neuron, NB: AI
                         suggested changing param 2 to log-width */

  ann(int n, double xmin = -1, double xmax = 1)
      : n(n), xmin(xmin), xmax(xmax), p(3 * n) {
    f = [](double z) { return z * std::exp(-z * z); };

    std::default_random_engine gen(42);
    std::uniform_real_distribution<double> rnd_w(-0.5, 0.5);
    double spacing = (xmax - xmin) / n;
    for (int i = 0; i < n; i++) {
      // AI suggest evenly spread a_i initialization in the neurons,
      // with random weights and dynamically sized widths
      p[3 * i] = xmin + spacing * (i + 0.5);  /* center  a_i              */
      p[3 * i + 1] = std::log(3.0 * spacing); /* log-width q_i = log(b_i) */
      p[3 * i + 2] = rnd_w(gen);              /* weight  w_i              */
    }
  }

  double response(double x) {
    double y = 0.0;
    for (int i = 0; i < n; i++) {
      double a = p[3 * i], b = std::exp(p[3 * i + 1]), w = p[3 * i + 2];
      y += f((x - a) / b) * w;
    }
    return y;
  }

  double response(double x, const pracprog::vector &aP) {
    double y = 0.0;
    for (int i = 0; i < n; i++) {
      double a = aP[3 * i], b = std::exp(aP[3 * i + 1]), w = aP[3 * i + 2];
      y += f((x - a) / b) * w;
    }
    return y;
  }

  pracprog::vector gradient(const pracprog::vector &xs,
                            const pracprog::vector &ys) {
    pracprog::vector grad(3 * n);
    for (int j = 0; j < 3 * n; j++)
      grad[j] = 0.0;

    for (int k = 0; k < (int)xs.size(); k++) {
      double ek = response(xs[k]) - ys[k];
      for (int i = 0; i < n; i++) {
        double a = p[3 * i];
        double b = std::exp(p[3 * i + 1]);
        double w = p[3 * i + 2];
        double z = (xs[k] - a) / b;
        double fp = std::exp(-z * z) * (1.0 - 2.0 * z * z); // f'(z)
        grad[3 * i] += 2.0 * ek * (-w / b) * fp;     // partial deriv w.r.t. a
        grad[3 * i + 1] += 2.0 * ek * (-w * z) * fp; // partial deriv w.r.t. q
        grad[3 * i + 2] +=
            2.0 * ek * z * std::exp(-z * z); // partial deriv w.r.t. w
      }
    }
    return grad;
  }

  // I used to use my newton minimization algorithm from homework 9, but it
  // didn't work I also tried modfiying the homework 9 minimization algorithm to
  // use the analytical gradient, but still a numerical hessian. It still did
  // not work claude AI rewrote this function with the Adaptive Moment
  // Estimation optimizer: This is a neural network standard algorithm more
  // information can be found here:
  //   https://en.wikipedia.org/wiki/Stochastic_gradient_descent#Adam
  //   https://doi.org/10.48550/arXiv.1412.6980
  /* -----------------------------------------------------------------------
   * Train with Adam using the analytic gradient.
   * Adam is robust on non-convex problems with many parameters and does not
   * require tuning a single global learning rate the way SGD does.
   * Standard hyper-parameters: α=0.01, β₁=0.9, β₂=0.999.
   * ----------------------------------------------------------------------- */
  void train(pracprog::vector xs, pracprog::vector ys) {
    const int max_iter = 3000;
    const double alpha = 0.01;
    const double beta1 = 0.9, beta2 = 0.999, eps = 1e-8;

    pracprog::vector m(3 * n), v(3 * n);
    for (int j = 0; j < 3 * n; j++) {
      m[j] = 0.0;
      v[j] = 0.0;
    }

    for (int t = 1; t <= max_iter; t++) {
      auto g = gradient(xs, ys);
      double b1t = 1.0 - std::pow(beta1, t); /* bias-correction: 1 − β₁ᵗ */
      double b2t = 1.0 - std::pow(beta2, t); /* bias-correction: 1 − β₂ᵗ */
      for (int j = 0; j < 3 * n; j++) {
        m[j] = beta1 * m[j] + (1.0 - beta1) * g[j];
        v[j] = beta2 * v[j] + (1.0 - beta2) * g[j] * g[j];
        p[j] -= alpha * (m[j] / b1t) / (std::sqrt(v[j] / b2t) + eps);
      }
    }
  }

  // exercise B stuff:

  double derivative(double x) {
    double dy = 0.0;
    for (int i = 0; i < n; i++) {
      double a = p[3 * i], b = std::exp(p[3 * i + 1]), w = p[3 * i + 2];
      double z = (x - a) / b;
      dy += (w / b) * std::exp(-z * z) * (1.0 - 2.0 * z * z);
    }
    return dy;
  }

  double second_derivative(double x) {
    double d2y = 0.0;
    for (int i = 0; i < n; i++) {
      double a = p[3 * i], b = std::exp(p[3 * i + 1]), w = p[3 * i + 2];
      double z = (x - a) / b;
      d2y += (w / (b * b)) * 2.0 * z * std::exp(-z * z) * (2.0 * z * z - 3.0);
    }
    return d2y;
  }

  double antiderivative(double x) {
    double F = 0.0;
    for (int i = 0; i < n; i++) {
      double a = p[3 * i], b = std::exp(p[3 * i + 1]), w = p[3 * i + 2];
      double z = (x - a) / b;
      double z0 = (0.0 - a) / b;
      F += w * (-b / 2.0) * (std::exp(-z * z) - std::exp(-z0 * z0));
    }
    return F;
  }
};

struct ann_ode {
  int n;
  std::function<double(double)> f;
  pracprog::vector p; /* parameters: (a_i, log(b_i), w_i) per neuron, NB: AI
                         suggested changing param 2 to log-width */
  double xmin, xmax;
  ann_ode(int n, double xmin = -1, double xmax = 1)
      : n(n), p(3 * n), xmin(xmin), xmax(xmax) {
    f = [](double z) { return z * std::exp(-z * z); };

    std::default_random_engine gen(42);
    std::uniform_real_distribution<double> rnd_w(-0.5, 0.5);
    double spacing = (xmax - xmin) / n;
    for (int i = 0; i < n; i++) {
      // AI suggest evenly spread a_i initialization in the neurons,
      // with random weights and dynamically sized widths
      p[3 * i] = xmin + spacing * (i + 0.5);  /* center  a_i              */
      p[3 * i + 1] = std::log(3.0 * spacing); /* log-width q_i = log(b_i) */
      p[3 * i + 2] = rnd_w(gen);              /* weight  w_i              */
    }
  }

  double response(double x) {
    double y = 0.0;
    for (int i = 0; i < n; i++) {
      double a = p[3 * i], b = std::exp(p[3 * i + 1]), w = p[3 * i + 2];
      y += f((x - a) / b) * w;
    }
    return y;
  }

  double response(double x, const pracprog::vector &aP) {
    double y = 0.0;
    for (int i = 0; i < n; i++) {
      double a = aP[3 * i], b = std::exp(aP[3 * i + 1]), w = aP[3 * i + 2];
      y += f((x - a) / b) * w;
    }
    return y;
  }

  double derivative(double x) {
    double dy = 0.0;
    for (int i = 0; i < n; i++) {
      double a = p[3 * i], b = std::exp(p[3 * i + 1]), w = p[3 * i + 2];
      double z = (x - a) / b;
      dy += (w / b) * std::exp(-z * z) * (1.0 - 2.0 * z * z);
    }
    return dy;
  }

  double second_derivative(double x) {
    double d2y = 0.0;
    for (int i = 0; i < n; i++) {
      double a = p[3 * i], b = std::exp(p[3 * i + 1]), w = p[3 * i + 2];
      double z = (x - a) / b;
      d2y += (w / (b * b)) * 2.0 * z * std::exp(-z * z) * (2.0 * z * z - 3.0);
    }
    return d2y;
  }

  double derivative(double x, const pracprog::vector &aP) {
    double dy = 0.0;
    for (int i = 0; i < n; i++) {
      double a = aP[3 * i], b = std::exp(aP[3 * i + 1]), w = aP[3 * i + 2];
      double z = (x - a) / b;
      dy += (w / b) * std::exp(-z * z) * (1.0 - 2.0 * z * z);
    }
    return dy;
  }

  double second_derivative(double x, const pracprog::vector &aP) {
    double d2y = 0.0;
    for (int i = 0; i < n; i++) {
      double a = aP[3 * i], b = std::exp(aP[3 * i + 1]), w = aP[3 * i + 2];
      double z = (x - a) / b;
      d2y += (w / (b * b)) * 2.0 * z * std::exp(-z * z) * (2.0 * z * z - 3.0);
    }
    return d2y;
  }

  // i once again tried with pracprog::newton and pracprog::newton_central
  // it failed, so i implemented ADAM myself this time.
  void train(std::function<double(double, double, double, double)> Phi,
             double a, double b, double c, double yc, double ypc, double alpha = 1000.0,
             double beta = 1000.0) {
    auto cost = [&](const pracprog::vector & aP) {
    const int N = 100;

    double integral = 0.0;

    for(int i=0;i<N;i++){
        double x = a + (i+0.5)*(b-a)/N;

        double y   = response(x, aP);
        double yp  = derivative(x, aP);
        double ypp = second_derivative(x, aP);

        double phi = Phi(ypp, yp, y, x);

        integral += phi*phi;
    }

    integral *= (b-a)/N;

    double bc =
        alpha*pow(response(c,aP)-yc,2)
      + beta *pow(derivative(c,aP)-ypc,2);

    return integral + bc;
  };

  // if you want to try newton you can comment out the below code and just have
  // the following:
  //auto [res,steps] = pracprog::newton(cost, p);
  //p = res;

  auto num_gradient = [&](const pracprog::vector &aP) {
    pracprog::vector gradient(3*n);
    const double curr_cost = cost(aP);
    for (unsigned int i = 0; i < static_cast<unsigned int>(3*n); ++i) {
      pracprog::vector pertubed_params = aP;
      pertubed_params[i] += 1e-6;
      gradient[i] = (cost(pertubed_params) - curr_cost)/1e-6;
    }
    return gradient;
  };

  const int hyppar_max_iter = 3000;
  const double hyppar_alpha = 0.01;
  const double hyppar_beta1 = 0.9, hyppar_beta2 = 0.999, hyppar_eps = 1e-8;
  pracprog::vector m(3*n),v(3*n);
  for (unsigned int t = 1; t < hyppar_max_iter; ++t) {
    pracprog::vector grad = num_gradient(p);
    for (unsigned int i = 0; i < static_cast<unsigned int>(3*n); ++i) {
      m[i] = hyppar_beta1 * m[i] + (1.0 - hyppar_beta1) * grad[i];
      v[i] = hyppar_beta2 * v[i] + (1.0 - hyppar_beta2) * grad[i] * grad[i];
      p[i] -= hyppar_alpha * (m[i] / (1.0 - std::pow(hyppar_beta1, t))) / (std::sqrt(v[i] / (1.0 - std::pow(hyppar_beta2, t))) + hyppar_eps);
    }
  }
  }
};

} /* namespace pracprog */
