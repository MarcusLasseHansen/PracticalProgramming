CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = linalg_evd.cpp ../linalg/linalg.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

dr_Ns := $(shell LC_NUMERIC=C seq 1 0.5 8)
rmax_Ns := $(shell LC_NUMERIC=C seq 0.01 0.01 0.3)
benchmark_Ns := $(shell seq 3 10 150)

.PHONY: all clean

all: Out.txt Convergence_dr.png Convergence_rmax.png Wavefunctions.png Out_diag_benchmark.png Out_parallel.png

Out.txt: test_suite Makefile hydrogen_atom
	./test_suite > Out.txt
	./hydrogen_atom >> Out.txt

Out_diag_benchmark.png: out.times.data Makefile
	@gnuplot -e "set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
	            set output '$@'; \
	            set title 'Runtime vs N'; \
	            set xlabel 'N'; \
	            set ylabel 'Time (s)'; \
	            set grid; \
		    set fit quiet; \
	            f(x) = a*x**3; \
	            fit f(x) '$<' using 1:2 via a; \
	            plot '$<' using 1:2 with linespoints pt 7 ps 1.2 lw 2 lc rgb '#0072B2' title 'data', \
	                 f(x) with lines lw 2 lc rgb '#D55E00' title sprintf('%.3e * N^3', a)"
out.times.data: benchmark_tool
	for N in $(benchmark_Ns); do \
		( time --format "$$N %e" --output bm_log.$$N --append \
		  ./$< $$N 1>bm_out.$$N 2>bm_err.$$N ) & \
	done; wait
	> $@
	for N in $(benchmark_Ns); do \
		cat bm_log.$$N >> $@; \
	done
	rm -f bm_log.* bm_out.* bm_err.*
benchmark_tool: benchmark_tool.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

benchmark_tool.o: benchmark_tool.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


Convergence_dr.png: hydrogen_atom Makefile
	for N in $(dr_Ns); do \
		./hydrogen_atom -rmax $$N -dr 0.04 -energy > temp_dr_$$N.data & \
	done; wait
	> temp_conv_dr.data
	for N in $(dr_Ns); do \
		cat temp_dr_$$N.data >> temp_conv_dr.data; \
	done
	@gnuplot -e "set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
            set output 'Out_rmax_vs_energy.png'; \
            set title 'Energy vs r_{max} (dr = 0.04)'; \
            set xlabel 'r_{max}'; \
            set ylabel 'Energy'; \
            set grid; \
            set datafile separator ','; \
            plot 'temp_conv_dr.data' using 1:3 with linespoints lw 2 lc rgb '#0072B2' title 'Energy'"
	rm -f temp_dr_*.data temp_conv_dr.data

Out_parallel.png: Makefile
	> makefile_parallel.data
	for N in $$(seq 1 10); do \
		echo "Running with $$N parallel jobs..."; \
		/usr/bin/time --format="$$N %e" --output=makefile_parallel.data --append \
			make Convergence_dr.png -j $$N 1>mf_out 2>mf_err; \
	done
	@echo "Plotting results..."
	@gnuplot -e "set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
            set output 'Out_parallel.png'; \
            set title 'Time to measure convergence vs cores used'; \
            set xlabel 'Cores used'; \
            set ylabel 'Time (s)'; \
            set grid; \
            plot 'makefile_parallel.data' using 1:2 with linespoints lw 2 lc rgb '#0072B2' title 'Energy';"
	@rm -f makefile_parallel.data

Convergence_rmax.png: hydrogen_atom Makefile
	for dr in $(rmax_Ns); do \
		./hydrogen_atom -rmax 7 -dr $$dr -energy > temp_rmax_$$dr.data & \
	done; wait
	> temp_conv_rmax.data
	for dr in $(rmax_Ns); do \
		cat temp_rmax_$$dr.data >> temp_conv_rmax.data; \
	done
	@gnuplot -e "set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
            set output 'Out_dr_vs_energy.png'; \
            set title 'Energy vs dr (rmax = 7)'; \
            set xlabel 'dr'; \
            set ylabel 'Energy'; \
            set grid; \
            set datafile separator ','; \
            plot 'temp_conv_rmax.data' using 2:3 with linespoints lw 2 lc rgb '#0072B2' title 'Energy'"
	rm -f temp_rmax_*.data temp_conv_rmax.data

Wavefunctions.png: hydrogen_atom Makefile
	>temp_wf.data
	./hydrogen_atom -wf -rmax 10 -dr 0.02 >> temp_wf.data
	@gnuplot -e "set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
            set output 'Out_wavefunctions.png'; \
            set title 'Hydrogen Wavefunctions'; \
            set xlabel 'r'; \
            set ylabel 'psi(r)'; \
            set grid; \
            set datafile separator ','; \
            plot 'temp_wf.data' using 1:2 with lines lw 2 lc rgb '#0072B2' title 'n=1', \
                 'temp_wf.data' using 1:3 with lines lw 2 lc rgb '#D55E00' title 'n=2', \
                 'temp_wf.data' using 1:4 with lines lw 2 lc rgb '#009E73' title 'n=3'"
	rm temp_wf.data

hydrogen_atom: hydrogen_atom.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

test_suite: test_suite.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

test_suite.o: test_suite.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

hydrogen_atom.o: hydrogen_atom.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) test_suite $(SHARED_OBJS) test_suite.o Out.txt hydrogen_atom hydrogen_atom.o. Out_dr_vs_energy.png *.png *.data bm_log.* bm_out.* bm_err.* temp_rmax_*.data temp_conv_rmax.data temp_wf.data bm_log.* bm_out.* bm_err.* temp_dr_*.data temp_conv_dr.data Out_rmax_vs_energy.png Out_diag_benchmark.png benchmark_tool.o fit.log hydrogen_atom.o Out_parallel.png makefile_parallel.data mf_* benchmark_tool err out
