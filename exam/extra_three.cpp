#include "hessenberg.hpp"
#include "modified_evd.hpp"
#include <chrono>

int main() {
  for (size_t size = 100; size < 1000; size = size + 60) {
    pracprog::matrix A(size, size);
    int x = 10;
    // construct sym matrix
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = i; j < size;
           ++j) {
        A(i, j) = x;
        A(j, i) = x;
        ++x;
      }
    }
    // make sym matrix triangular with hessenberg factorization
    pracprog::hessenberg hessenberg(A);

    auto t1 = std::chrono::steady_clock::now();
    pracprog::modified_evd modified_evd(hessenberg.getH()); // test modified jacobi evd
    auto t2 = std::chrono::steady_clock::now();

    std::cout << size << " "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1)
                     .count() / static_cast<double>(modified_evd.getw().size()) // assuming that O(n) is per eigenvalue
              << "\n";
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
