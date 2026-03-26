#include "linalg_evd.hpp"

int main(int argc, char *argv[]) {
    double rmax = 7.0;
    double dr = 0.02;
    unsigned int calc_type = 0;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-rmax" && i + 1 < argc) {
            rmax = std::stod(argv[++i]);
        } else if (arg == "-dr" && i + 1 < argc) {
            dr = std::stod(argv[++i]);
        } else if (arg == "-energy") {
            calc_type = 1;
        } else if (arg == "-wf") {
            calc_type = 2;
        }
    }
    if (rmax <= 0.0 || dr <= 0.0) {
        std::cerr << "Error: rmax and dr must be positive.\n";
        return EXIT_FAILURE;
    }
    size_t npoints = static_cast<size_t>(rmax / dr);
    if (npoints < 2) {
        std::cerr << "Error: dr too large for the given rmax.\n";
        return EXIT_FAILURE;
    }

    pracprog::vector r(npoints);
    for (size_t i = 0; i < npoints; ++i) {
        r[i] = dr * (i + 1);
    }
    pracprog::matrix H(npoints, npoints);
    double coeff = -0.5 / (dr * dr);
    for (size_t i = 0; i < npoints; ++i) {
        H(i, i) = -2.0 * coeff - 1.0 / r[i];
        if (i < npoints - 1) {
            H(i, i + 1) = coeff;
            H(i + 1, i) = coeff;
        }
    }
    pracprog::evd EVD(H);
    double E0 = EVD.w[0];
    switch(calc_type) {
        case 1: // energy only
            std::cout << rmax << "," << dr << "," << E0 << std::endl;
            break;
        case 2: // wavefunction only
            std::cout << "# r, psi(r)\n";
            for (size_t i = 0; i < npoints; ++i)
                std::cout << r[i] << "," << EVD.V(i, 0) << "," << EVD.V(i, 1) << "," << EVD.V(i, 2) << "\n";
            break;
        default: // full output
            std::cout << "Lowest energy calculated: " << E0 << " Hartree, exact is 0.5 Hartree\n";
            std::cout << "Corresponding wavefunction (r, psi):\n";
            for (size_t i = 0; i < npoints; ++i)
                std::cout << r[i] << "," << EVD.V(i, 0) << "\n";
            break;
    }

    return EXIT_SUCCESS;
}
