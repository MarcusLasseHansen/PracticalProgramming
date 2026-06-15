#include "../linalg/linalg.hpp"
#include <cmath>
#include <functional>
#include <random>

namespace pracprog {

class lcg {
private:
  unsigned long seed;
  unsigned long a;
  unsigned long c;
  unsigned long m;

public:
  lcg(unsigned long seed, unsigned long a = 1664525,
      unsigned long c = 1013904223, unsigned long m = std::pow(2, 32))
      : seed(seed), a(a), c(c), m(m) {}

  double operator()() {
    seed = (a * seed + c) % m;

    return static_cast<double>(seed + 1) / static_cast<double>(m + 1);
  }
};

template <typename RNG> // to handle both the LCG class and the stl rng - makes
                        // me write the entire monte-carlo in the hpp file
                        std::pair<double, double>
                        plainmc(const std::function<
                                    double(const pracprog::vector &)> &f,
                                const pracprog::vector &a,
                                const pracprog::vector &b, int N, RNG &rng) {
  int dim = a.size();
  double V = 1.0;
  double sum1 = 0.0;
  double sum2 = 0.0;

  for (int i = 0; i < dim; ++i)
    V *= (b[i] - a[i]);

  pracprog::vector x(dim);
  for (int n = 0; n < N; ++n) {
    for (int i = 0; i < dim; ++i)
      x[i] = a[i] + rng() * (b[i] - a[i]);
    double fx = f(x);
    sum1 += fx;
    sum2 += fx * fx;
  }

  double mean = sum1 / N;
  double sigma = std::sqrt(sum2 / N - mean * mean);

  return {mean * V, sigma * V / std::sqrt(N)};
}

double corput(int n, int base) {
  double q = 0.0;
  double bk = 1.0 / base;

  while (n > 0) {
    q += (n % base) * bk;
    n /= base;
    bk /= base;
  }

  return q;
}

std::vector<int> prime_numbers(int dim) {
  std::vector<int> primes;
  int candidate = 2;
  while ((int)primes.size() < dim) {
    bool is_prime = true;
    for (int p : primes) {
      if (p * p > candidate)
        break;
      if (candidate % p == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
      primes.push_back(candidate);
    candidate++;
  }
  return primes;
}

class Halton {
private:
  std::vector<int> bases;

public:
  Halton(int dim, int offset = 0) {
    auto primes = prime_numbers(dim + offset);
    for (int i = 0; i < dim; ++i)
      bases.push_back(primes[i + offset]);
  }
  pracprog::vector operator()(int n) const {
    pracprog::vector x(bases.size());
    for (int i = 0; i < (int)bases.size(); ++i)
      x[i] = corput(n, bases[i]);
    return x;
  }
};

std::pair<double, double>
quasimc(const std::function<double(const pracprog::vector &)> &f,
        const pracprog::vector &a, const pracprog::vector &b, int N) {
  int dim = a.size();
  Halton seq1(dim, 0);
  Halton seq2(dim, 1);
  double V = 1.0;
  for (int i = 0; i < dim; ++i)
    V *= (b[i] - a[i]);
  double sum1 = 0.0;
  double sum2 = 0.0;
  for (int n = 1; n <= N; ++n) {
    auto x1 = seq1(n);
    auto x2 = seq2(n);
    for (int i = 0; i < dim; ++i) {
      x1[i] = a[i] + x1[i] * (b[i] - a[i]);
      x2[i] = a[i] + x2[i] * (b[i] - a[i]);
    }
    sum1 += f(x1);
    sum2 += f(x2);
  }

  double I1 = V * sum1 / N;
  double I2 = V * sum2 / N;
  double error = std::abs(I1 - I2);
  return {I1, error};
}

// Implementation optimized by claude code
std::pair<double, double>
stratified(const std::function<double(const pracprog::vector &)> &f,
           const pracprog::vector &a, const pracprog::vector &b, int N,
           int nmin = 32) {
  int dim = a.size();

  if (N < nmin) {
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_real_distribution<double> u(0.0, 1.0);
    auto gen = [&]() { return u(rng); };
    return plainmc(f, a, b, N, gen);
  }

  std::mt19937_64 rng(std::random_device{}());
  std::uniform_real_distribution<double> u(0.0, 1.0);

  std::vector<double> sum_lo(dim, 0.0), sum_hi(dim, 0.0);
  std::vector<int> cnt_lo(dim, 0), cnt_hi(dim, 0);

  pracprog::vector x(dim);
  double sum1 = 0.0, sum2 = 0.0;

  for (int n = 0; n < nmin; ++n) {
    for (int i = 0; i < dim; ++i)
      x[i] = a[i] + u(rng) * (b[i] - a[i]);
    double fx = f(x);
    sum1 += fx;
    sum2 += fx * fx;
    for (int i = 0; i < dim; ++i) {
      double mid = 0.5 * (a[i] + b[i]);
      if (x[i] < mid) {
        sum_lo[i] += fx;
        cnt_lo[i]++;
      } else {
        sum_hi[i] += fx;
        cnt_hi[i]++;
      }
    }
  }

  int split_dim = 0;
  double max_var = -1.0;
  for (int i = 0; i < dim; ++i) {
    double mean_lo = (cnt_lo[i] > 0) ? sum_lo[i] / cnt_lo[i] : 0.0;
    double mean_hi = (cnt_hi[i] > 0) ? sum_hi[i] / cnt_hi[i] : 0.0;
    double var_i = (mean_lo - mean_hi) * (mean_lo - mean_hi);
    if (var_i > max_var) {
      max_var = var_i;
      split_dim = i;
    }
  }

  double var_lo = (cnt_lo[split_dim] > 0)
                      ? std::abs(sum_lo[split_dim] / cnt_lo[split_dim])
                      : 0.0;
  double var_hi = (cnt_hi[split_dim] > 0)
                      ? std::abs(sum_hi[split_dim] / cnt_hi[split_dim])
                      : 0.0;

  int N_remaining = N - nmin;
  int N_lo;
  double total_var = var_lo + var_hi;
  if (total_var > 0.0)
    N_lo = static_cast<int>(std::round(N_remaining * var_lo / total_var));
  else
    N_lo = N_remaining / 2;
  N_lo = std::max(1, N_lo);
  int N_hi = std::max(1, N_remaining - N_lo);

  pracprog::vector a_lo = a, b_lo = b;
  pracprog::vector a_hi = a, b_hi = b;
  double mid = 0.5 * (a[split_dim] + b[split_dim]);
  b_lo[split_dim] = mid;
  a_hi[split_dim] = mid;

  auto [I_lo, e_lo] = stratified(f, a_lo, b_lo, N_lo, nmin);
  auto [I_hi, e_hi] = stratified(f, a_hi, b_hi, N_hi, nmin);

  return {I_lo + I_hi, std::sqrt(e_lo * e_lo + e_hi * e_hi)};
}
} // namespace pracprog
