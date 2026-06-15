//Error estimation test created with AI (chatgpt 4.0)

#include "integrator.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <string>

bool check_error(
    const std::string& label,
    double numeric,
    double exact,
    double estimated_error,
    double factor = 5.0
) {
    double actual_error = std::abs(numeric - exact);

    bool ok = actual_error <= factor * estimated_error;

    std::cout << (ok ? "[PASS]" : "[FAIL]")
              << "  " << label << "\n";

    std::cout << "    numeric value   = "
              << std::setprecision(16)
              << numeric << "\n";

    std::cout << "    exact value     = "
              << exact << "\n";

    std::cout << "    estimated error = "
              << estimated_error << "\n";

    std::cout << "    actual error    = "
              << actual_error << "\n\n";

    return ok;
}

bool test_1() {
    // Integral:
    // ∫₀^∞ exp(-x) sin(x) dx = 1/2

    auto f = [](double x) {
        return std::exp(-x) * std::sin(x);
    };

    auto res = pracprog::generalized_integral_error_prop(
        f,
        0,
        std::numeric_limits<double>::quiet_NaN()
    );

    return check_error(
        "exp(-x) sin(x)",
        res.first,
        0.5,
        res.second
    );
}

bool test_2() {
    // Integral:
    // ∫₀¹ log(x)/sqrt(x) dx = -4

    auto f = [](double x) {
        return std::log(x) / std::sqrt(x);
    };

    auto res = pracprog::cc_vt_integral_error_prop(
        f,
        0,
        1
    );

    return check_error(
        "log(x)/sqrt(x)",
        res.first,
        -4.0,
        res.second
    );
}

bool test_3() {
    // Integral:
    // ∫₀^∞ exp(-x²) dx = sqrt(pi)/2

    auto f = [](double x) {
        return std::exp(-(x * x));
    };

    auto res = pracprog::generalized_integral_error_prop(
        f,
        0,
        std::numeric_limits<double>::quiet_NaN()
    );

    return check_error(
        "exp(-x²)",
        res.first,
        std::sqrt(std::numbers::pi) / 2.0,
        res.second
    );
}

int main() {
    bool ok = true;

    ok &= test_1();
    ok &= test_2();
    ok &= test_3();

    std::cout << "\n"
              << (ok ? "All C tests passed."
                     : "One or more tests FAILED.")
              << "\n\n";

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
