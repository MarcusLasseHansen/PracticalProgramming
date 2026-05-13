#pragma once
#include "../homework_1/linalg_qr.hpp"
#include <functional>
#include <utility>

namespace pracprog {

std::pair<pracprog::vector, pracprog::matrix>
lsfit(const std::vector<std::function<double(double)>> &fs,
      const pracprog::vector &x, const pracprog::vector &y,
      const pracprog::vector &dy);

} /* namespace pracprog */
