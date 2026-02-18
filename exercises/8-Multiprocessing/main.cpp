#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

struct data {
  int start, end;
  double sum;
};

void harm(data &p) {
  int start = p.start, end = p.end;
  double sum = 0;
  for (int i = start; i < end; ++i) {
    sum += 1.0 / i;
  }
  p.sum = sum;
}

int main(int argc, char **argv) {
  int nterms = (int)1e9; // Numbers of terms in harmonic sum
  int nthreads = 1;      // Numbers of threads to use
  for (int i = 0; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "--terms" && i + 1 < argc) {
      nterms = static_cast<int>(std::stod(argv[i + 1]));
    } else if (arg == "--threads" && i + 1 < argc) {
      nthreads = std::stoi(argv[i + 1]);
    }
  }

  std::vector<std::thread> threads;
  threads.reserve(nthreads);
  std::vector<data> data_v(nthreads);
  for (int i = 0; i < nthreads; ++i) {
    data_v[i].start = 1 + (nterms / nthreads) * i;
    data_v[i].end = 1 + (nterms / nthreads) * (i + 1);
    threads.emplace_back(harm, std::ref(data_v[i]));
  }
  for (std::thread &thread : threads) {
    thread.join();
  }
  double total = 0;
  for (data &d : data_v) {
    total += d.sum;
  }
  std::cout << "Total : " << total << std::endl;

  return EXIT_SUCCESS;
}
