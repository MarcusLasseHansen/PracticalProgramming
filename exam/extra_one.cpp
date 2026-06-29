#include "hessenberg.hpp"
#include "../homework/homework_1/linalg_qr.hpp"
#include <chrono>

int main() {
  constexpr size_t size = 500;
  pracprog::matrix A(size, size);
  int x = 10;
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      A(i, j) = x;
      x++;
    }
  }
  auto t1 = std::chrono::steady_clock::now();
  pracprog::hessenberg hessenberg(A);
  auto t2 = std::chrono::steady_clock::now();
  pracprog::qr QR(A);
  auto t3 = std::chrono::steady_clock::now();
  std::cout << "Extra One - What factorization is faster?\n";
  std::cout << "Hessenberg took: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms.\n"
            << "QR took:         " << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << " ms." << std::endl;
  std::cout << ((std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() > std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count()) ? "QR " : "Hessenberg ")
            << "factorization was faster!" << std::endl;
  return EXIT_SUCCESS;
}
