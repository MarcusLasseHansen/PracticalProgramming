#pragma once
#include "../homework/linalg/linalg.hpp" // my linear algebra base class
#include "hessenberg.hpp"
#include "../homework/homework_2/linalg_evd.hpp"

namespace pracprog {
class qr {
private:
  matrix Q;
  matrix R;
public:
  const matrix &getQ() {return Q;}
  const matrix &getR() {return R;}
  qr(const pracprog::hessenberg &hessenberg) : Q(hessenberg.getH()), R(hessenberg.getH().cols(), hessenberg.getH().cols()) {
    for (size_t p = 1; p < R.cols(); ++p) {
      double theta = std::atan2(R(p,p-1),R(p-1,p-1));
      evd::Jtimes(R,p-1,p,theta);
      evd::timesJ(Q,p-1,p,-theta);
    }
  };
};
} /* namespace pracprog */
