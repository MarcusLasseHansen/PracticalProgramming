#include "linalg_ols.hpp"
#include <iomanip>

int main() {
pracprog::vector t(9), dy(9), y(9), lny(9), dlny(9);
 t[0] =  1; y[0] = 117.0; dy[0] = 6;
 t[1] =  2; y[1] = 100.0; dy[1] = 5;
 t[2] =  3; y[2] =  88.0; dy[2] = 4;
 t[3] =  4; y[3] =  72.0; dy[3] = 4;
 t[4] =  6; y[4] =  53.0; dy[4] = 4;
 t[5] =  9; y[5] =  29.5; dy[5] = 3;
 t[6] = 10; y[6] =  25.2; dy[6] = 3;
 t[7] = 13; y[7] =  15.2; dy[7] = 2;
 t[8] = 15; y[8] =  11.1; dy[8] = 2;

 for (size_t i = 0; i < 9; i++) {
   lny[i] = std::log(y[i]);
   dlny[i] = dy[i] / y[i];
 }
 std::vector<std::function<double(double)>> fs = {[]( [[maybe_unused]] double z) { return 1.0; },
                                                  [](double z) { return z; }};

 // This could also have been handled with structural binding, but this has already been written
 std::pair<pracprog::vector,pracprog::matrix> lsfit_data = pracprog::lsfit(fs, t, lny, dlny);

 double ln_a = lsfit_data.first[0];
 double lambda = -lsfit_data.first[1];
 double a = std::exp(ln_a);

 std::cout << "Fit result: a = " << a << ", λ = " << lambda << " +- " << std::sqrt(lsfit_data.second(1,1)) << "\n";
 std::cout << "Fitted half-life:  T_1/2 = ln(2)/λ = " << std::log(2.0) / lambda << " +- " << (std::log(2.0) / (lambda*lambda)) * std::sqrt(lsfit_data.second(1,1)) // Error found via standard error propagation of T_1/2
           << "\n" << "Modern half-life: T_1/2 = 3.632" << std::endl;

 std::cout << "\n"
           << std::setw(5) << "t" << std::setw(8) << "y" << std::setw(8)
           << "y_fit" << std::setw(10) << "residual" << std::setw(6) << "dy"
           << "\n";

 for (size_t i = 0; i < 9; i++) {
   double y_fit = a * std::exp(-lambda * t[i]);
   std::cout << std::fixed << std::setprecision(2) << std::setw(5) << t[i]
             << std::setw(8) << y[i] << std::setprecision(3)
             << std::setw(8) << y_fit << std::setw(10)
             << (y[i] - y_fit) / dy[i] << std::setprecision(2)
             << std::setw(6) << dy[i] << "\n";
 }

std::cout << "Uncertainties: d_lna = " << std::sqrt(lsfit_data.second(0,0)) << ", d_lambda = " << std::sqrt(lsfit_data.second(1,1)) << "\n";

 return EXIT_SUCCESS;
}
