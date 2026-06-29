#pragma once
#include "../homework/linalg/linalg.hpp" // my linear algebra base class
#include "../homework/homework_2/linalg_evd.hpp" // my Jacobi class

namespace pracprog {
class hessenberg {
private:
  matrix H;
  matrix Q;

public:
  matrix &getQ() { return Q; };
  matrix &getH() { return H; };
  const matrix &getQ() const { return Q; };
  const matrix &getH() const { return H; };

  hessenberg(const matrix &A) : H(A), Q(matrix::identity( A.cols() ) ) {
  const size_t n = A.cols();
    for (size_t p = 1; p < n-1; ++p) {
      for (size_t q = p+1; q < n; ++q) {
        double theta = std::atan2(-H(p-1,q), H(p-1,p));
        evd::Jtimes(H, p, q, -theta);   // J^T*H
        evd::timesJ(H, p, q,  theta);   // H*J
        evd::timesJ(Q, p, q,  theta);   // Q*J this accumulates the total transformation matrix
      }
    }
  };
};
} /* namespace pracprog */
