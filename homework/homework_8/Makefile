CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = ../linalg/linalg.cpp ../homework_1/linalg_qr.cpp ../homework_5/ode.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt WF.png H_energy_convergence_rmax.png H_energy_convergence_rmin.png H_energy_convergence_acc.png H_energy_convergence_eps.png

Out.txt: a_checks c_checks Makefile
	./a_checks > Out.txt
	./c_checks >> Out.txt

WF.png: b_wavefunction.data Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > wf_gnuplot.gnu
	@printf 'set grid\n' >> wf_gnuplot.gnu
	@printf 'set output "WF.png"\n' >> wf_gnuplot.gnu
	@printf 'set title "Numerically found WF vs Exact"\n' >> wf_gnuplot.gnu
	@printf 'set xlabel "r"; set ylabel "f"\n' >> wf_gnuplot.gnu
	@printf 'plot "b_wavefunction.data" using 1:2 with points lw 2 lc rgb "red" title "Numerical", \\\n' >> wf_gnuplot.gnu
	@printf '     "b_wavefunction.data" using 1:3 with points lw 2 lc rgb "blue" title "Exact"\n' >> wf_gnuplot.gnu
	gnuplot wf_gnuplot.gnu
	@$(RM) wf_gnuplot.gnu

H_energy_convergence_rmax.png: b_convergence_rmax.data Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > H_energy_convergence_rmax.gnu
	@printf 'set grid\n' >> H_energy_convergence_rmax.gnu
	@printf 'set logscale x\n' >> H_energy_convergence_rmax.gnu
	@printf 'set output "H_energy_convergence_rmax.png"\n' >> H_energy_convergence_rmax.gnu
	@printf 'set title "Convergence of hydrogen energy with rmax"\n' >> H_energy_convergence_rmax.gnu
	@printf 'set xlabel "r"; set ylabel "f"\n' >> H_energy_convergence_rmax.gnu
	@printf 'plot "b_convergence_rmax.data" using 1:2 with points lw 2 lc rgb "red" title "Numerical"\n' >> H_energy_convergence_rmax.gnu
	gnuplot H_energy_convergence_rmax.gnu
	@$(RM) H_energy_convergence_rmax.gnu

H_energy_convergence_rmin.png: b_convergence_rmin.data Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > H_energy_convergence_rmin.gnu
	@printf 'set grid\n' >> H_energy_convergence_rmin.gnu
	@printf 'set logscale x\n' >> H_energy_convergence_rmin.gnu
	@printf 'set output "H_energy_convergence_rmin.png"\n' >> H_energy_convergence_rmin.gnu
	@printf 'set title "Convergence of hydrogen energy with rmin"\n' >> H_energy_convergence_rmin.gnu
	@printf 'set xlabel "r"; set ylabel "f"\n' >> H_energy_convergence_rmin.gnu
	@printf 'plot "b_convergence_rmin.data" using 1:2 with points lw 2 lc rgb "red" title "Numerical"\n' >> H_energy_convergence_rmin.gnu
	gnuplot H_energy_convergence_rmin.gnu
	@$(RM) H_energy_convergence_rmin.gnu

H_energy_convergence_acc.png: b_convergence_acc.data Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > H_energy_convergence_acc.gnu
	@printf 'set grid\n' >> H_energy_convergence_acc.gnu
	@printf 'set logscale x\n' >> H_energy_convergence_acc.gnu
	@printf 'set output "H_energy_convergence_acc.png"\n' >> H_energy_convergence_acc.gnu
	@printf 'set title "Convergence of hydrogen energy with integrator acc"\n' >> H_energy_convergence_acc.gnu
	@printf 'set xlabel "r"; set ylabel "f"\n' >> H_energy_convergence_acc.gnu
	@printf 'plot "b_convergence_acc.data" using 1:2 with points lw 2 lc rgb "red" title "Numerical"\n' >> H_energy_convergence_acc.gnu
	gnuplot H_energy_convergence_acc.gnu
	@$(RM) H_energy_convergence_acc.gnu

H_energy_convergence_eps.png: b_convergence_eps.data Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > H_energy_convergence_eps.gnu
	@printf 'set grid\n' >> H_energy_convergence_eps.gnu
	@printf 'set logscale x\n' >> H_energy_convergence_eps.gnu
	@printf 'set output "H_energy_convergence_eps.png"\n' >> H_energy_convergence_eps.gnu
	@printf 'set title "Convergence of hydrogen energy with integrator eps"\n' >> H_energy_convergence_eps.gnu
	@printf 'set xlabel "r"; set ylabel "f"\n' >> H_energy_convergence_eps.gnu
	@printf 'plot "b_convergence_eps.data" using 1:2 with points lw 2 lc rgb "red" title "Numerical"\n' >> H_energy_convergence_eps.gnu
	gnuplot H_energy_convergence_eps.gnu
	@$(RM) H_energy_convergence_eps.gnu

b_convergence_rmax.data: b_convergence
	./b_convergence rmax > b_convergence_rmax.data
b_convergence_rmin.data: b_convergence
	./b_convergence rmin > b_convergence_rmin.data
b_convergence_acc.data: b_convergence
	./b_convergence acc > b_convergence_acc.data
b_convergence_eps.data: b_convergence
	./b_convergence eps > b_convergence_eps.data



b_wavefunction.data: b_wavefunction
	./b_wavefunction > b_wavefunction.data

a_checks: a_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

a_checks.o: a_checks.cpp roots.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

b_wavefunction: b_wavefunction.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

b_wavefunction.o: b_wavefunction.cpp roots.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


b_convergence: b_convergence.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

b_convergence.o: b_convergence.cpp roots.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

c_checks: c_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

c_checks.o: c_checks.cpp roots.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) \
		*.o      \
		Out.txt \
		a_checks \
		c_checks \
		b_wavefunction \
		*~ \
		b_wavefunction.data \
		wf_gnuplot.gnu \
		b_convergence_rmax.data \
		b_convergence_rmin.data \
		b_convergence_acc.data \
		b_convergence_eps.data \
		H_energy_convergence_rmin.data \
		H_energy_convergence_rmax.data \
		H_energy_convergence_acc.data \
		H_energy_convergence_eps.data \
		H_energy_convergence_rmin.png \
		H_energy_convergence_rmax.png \
		H_energy_convergence_acc.png \
		H_energy_convergence_eps.png \
		WF.png \
		b_convergence \
