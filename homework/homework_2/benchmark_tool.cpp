#include "linalg_evd.hpp"
#include <chrono>
#include <random>

// Usage: ./benchmark_tool N
// Generates a random NxN matrix and performs QR factorization.
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./benchmark_tool N\n";
        return EXIT_FAILURE;
    }
    int size_arg = std::stoi(argv[1]);
    if (size_arg <= 0) {
        std::cerr << "Error: N must be a positive integer.\n";
        return EXIT_FAILURE;
    }
    unsigned int size = static_cast<unsigned int>(size_arg);

    // Create rng
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Generate random NxN matrix
    pracprog::matrix A(size, size);
    for (unsigned int i = 0; i < size; ++i) {
        pracprog::vector& col = A.col(i);
        std::generate(col.begin(), col.end(), [&]() { return dist(rng); });
    }
    pracprog::evd EVD(A);

    return EXIT_SUCCESS;
}
