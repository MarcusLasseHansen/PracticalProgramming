#pragma once
#include "../linalg/linalg.hpp" // linear algebra base class

namespace pracprog {
class evd {
public:
  pracprog::matrix V;
  pracprog::vector w;

public:
  evd(matrix A);
  static void timesJ(pracprog::matrix &A, int p, int q, double theta);
  static void Jtimes(pracprog::matrix &A, int p, int q, double theta);
};

} /* namespace pracprog */
