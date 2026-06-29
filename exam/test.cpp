#include "hessenberg.hpp"

int main() {
  pracprog::matrix A(5, 5);
  int x = 0;
  for (size_t i = 0; i < 5; ++i) {
    for (size_t j = 0; j < 5; ++j) {
      A(i, j) = x;
      x++;
    }
  }

  std::cout << "A:" << "\n" << A;
  pracprog::hessenberg hessenberg(A);
  std::cout << "H:" << "\n" << hessenberg.getH();
  std::cout << "A reconstructed:" << "\n" << hessenberg.getQ()*hessenberg.getH()*hessenberg.getQ().transpose();
  return EXIT_SUCCESS;
}
