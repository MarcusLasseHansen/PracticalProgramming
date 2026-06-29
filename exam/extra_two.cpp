#include "modified_qr.hpp"
#include "hessenberg.hpp"
#include <chrono>

int main() {
  for (size_t size = 100; size < 1000; size = size + 60) {
    pracprog::matrix A(size, size);
    int x = 10;
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        A(i, j) = x;
        x++;
      }
    }
    pracprog::hessenberg hessenberg(A);
    auto t1 = std::chrono::steady_clock::now();
    pracprog::qr QR(hessenberg);
    auto t2 = std::chrono::steady_clock::now();

    std::cout << size << " " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "\n";
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;
}
