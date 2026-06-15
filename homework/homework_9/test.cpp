#include "minimization.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

bool approx(double a, double b, double tol = 1e-4) {
    return std::abs(a - b) < tol;
}

int main() {

    // =====================================================
    // Test 1: Gradient
    // f(x,y) = x² + y²
    // grad = (2x,2y)
    // =====================================================

    {
        auto f = [](const pracprog::vector& x) {
            return x[0]*x[0] + x[1]*x[1];
        };

        pracprog::vector p(2);
        p[0] = 3;
        p[1] = 4;

        auto g = gradient(f,p);

        std::cout << "Gradient test:\n";
        std::cout << g[0] << " " << g[1] << "\n";

        assert(approx(g[0],6));
        assert(approx(g[1],8));
    }

    // =====================================================
    // Test 2: Hessian
    // f(x,y)=x²+y²
    // Hessian = [[2,0],[0,2]]
    // =====================================================

    {
        auto f = [](const pracprog::vector& x) {
            return x[0]*x[0] + x[1]*x[1];
        };

        pracprog::vector p(2);
        p[0] = 3;
        p[1] = 4;

        auto H = hessian(f,p);

        std::cout << "\nHessian test:\n";
        std::cout << H(0,0) << " "
                  << H(0,1) << " "
                  << H(1,0) << " "
                  << H(1,1) << "\n";

        assert(approx(H(0,0),2));
        assert(approx(H(1,1),2));
        assert(std::abs(H(0,1)) < 1e-3);
        assert(std::abs(H(1,0)) < 1e-3);
    }

    // =====================================================
    // Test 3: QR solve
    //
    // [2 1] [x] = [5]
    // [1 3] [y]   [7]
    //
    // solution:
    // x=1.6
    // y=1.8
    // =====================================================

    {
        pracprog::matrix A(2,2);

        A(0,0)=2;
        A(0,1)=1;
        A(1,0)=1;
        A(1,1)=3;

        pracprog::vector b(2);
        b[0]=5;
        b[1]=7;

        pracprog::qr QR(A);

        auto x = QR.solve(b);

        std::cout << "\nQR test:\n";
        std::cout << x[0] << " " << x[1] << "\n";

        assert(approx(x[0],1.6));
        assert(approx(x[1],1.8));
    }

    // =====================================================
    // Test 4: Newton on simple quadratic
    //
    // f=(x-2)^2+(y+1)^2
    //
    // minimum at (2,-1)
    // =====================================================

    {
        auto f = [](const pracprog::vector& x) {
            return
                (x[0]-2)*(x[0]-2)
              + (x[1]+1)*(x[1]+1);
        };

        pracprog::vector p(2);
        p[0]=10;
        p[1]=10;

        auto [res,steps] = pracprog::newton(f,p,1e-6);

        std::cout << "\nNewton quadratic test:\n";
        std::cout << "x=" << res[0]
                  << " y=" << res[1]
                  << " steps=" << steps
                  << "\n";

        assert(approx(res[0],2,1e-3));
        assert(approx(res[1],-1,1e-3));
    }

    // =====================================================
    // Test 5: Rosenbrock function
    //
    // minimum at (1,1)
    // =====================================================

    {
        auto rosenbrock = [](const pracprog::vector& x) {
            double X=x[0];
            double Y=x[1];

            return
                100*std::pow(Y-X*X,2)
                + std::pow(1-X,2);
        };

        pracprog::vector p(2);
        p[0]=-1.2;
        p[1]=1.0;

        auto [res,steps] =
            pracprog::newton(rosenbrock,p,1e-5);

        std::cout << "\nRosenbrock test:\n";
        std::cout << res[0]
                  << " "
                  << res[1]
                  << "\n";

        assert(approx(res[0],1,1e-2));
        assert(approx(res[1],1,1e-2));
    }

    std::cout << "\nALL TESTS PASSED\n";
}
