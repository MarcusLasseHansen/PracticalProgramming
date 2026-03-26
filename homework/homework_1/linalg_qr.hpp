#pragma once
#include "../linalg/linalg.hpp" // my linear algebra base class

namespace pracprog {
class qr {
private:
  //! Should only be called at initialization
  void decompose(); // using stabilized Gram-Schmidt

public:
  matrix Q;
  matrix R;
  qr(const matrix &A) : Q(A), R(A.cols(), A.cols()) { decompose(); };

  vector solve(const vector &) const;
  double det() const;
  matrix inverse() const;
};
} /* namespace pracprog */
