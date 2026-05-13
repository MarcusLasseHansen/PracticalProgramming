CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = linalg_evd.cpp ../linalg/linalg.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

dr_Ns        := $(shell LC_NUMERIC=C seq 1 0.5 8)
rmax_Ns      := $(shell LC_NUMERIC=C seq 0.01 0.01 0.3)
benchmark_Ns := $(shell seq 3 10 150)

.PHONY: all clean

all: Out.txt Convergence_dr.png Convergence_rmax.png Wavefunctions.png Out_diag_benchmark.png Parallel.png

# ── Text output ────────────────────────────────────────────────────────────────

Out.txt: test_suite hydrogen_atom
	./test_suite > $@
	./hydrogen_atom >> $@

# ── Benchmark ──────────────────────────────────────────────────────────────────

Out_diag_benchmark.png: out.times.data
	@gnuplot -e " \
	    set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
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
	@for N in $(benchmark_Ns); do \
		/usr/bin/time --format "$$N %e" --output bm_log.$$N \
		  ./$< $$N 1>bm_out.$$N 2>bm_err.$$N & \
	done; wait
	cat $(foreach N,$(benchmark_Ns),bm_log.$(N)) > $@
	@$(RM) bm_log.* bm_out.* bm_err.*

# ── Convergence plots ──────────────────────────────────────────────────────────
# Each parameter value gets its own target so make -jN schedules them freely.

dr_DATA   = $(foreach N,$(dr_Ns),temp_dr_$(N).data)
rmax_DATA = $(foreach dr,$(rmax_Ns),temp_rmax_$(dr).data)

$(dr_DATA): temp_dr_%.data: hydrogen_atom
	./hydrogen_atom -rmax $* -dr 0.04 -energy > $@

$(rmax_DATA): temp_rmax_%.data: hydrogen_atom
	./hydrogen_atom -rmax 7 -dr $* -energy > $@

Convergence_dr.png: $(dr_DATA)
	cat $^ > temp_conv_dr.data
	@gnuplot -e " \
	    set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
	    set output '$@'; \
	    set title 'Energy vs r_{max} (dr = 0.04)'; \
	    set xlabel 'r_{max}'; \
	    set ylabel 'Energy'; \
	    set grid; \
	    set datafile separator ','; \
	    plot 'temp_conv_dr.data' using 1:3 with linespoints lw 2 lc rgb '#0072B2' title 'Energy'"
	@$(RM) temp_conv_dr.data

Convergence_rmax.png: $(rmax_DATA)
	cat $^ > temp_conv_rmax.data
	@gnuplot -e " \
	    set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
	    set output '$@'; \
	    set title 'Energy vs dr (rmax = 7)'; \
	    set xlabel 'dr'; \
	    set ylabel 'Energy'; \
	    set grid; \
	    set datafile separator ','; \
	    plot 'temp_conv_rmax.data' using 2:3 with linespoints lw 2 lc rgb '#0072B2' title 'Energy'"
	@$(RM) temp_conv_rmax.data

# ── Parallelism benchmark ──────────────────────────────────────────────────────

Parallel.png: Out.txt Convergence_dr.png Convergence_rmax.png Wavefunctions.png Out_diag_benchmark.png
	@> makefile_parallel.data
	@for N in $$(seq 1 10); do \
		echo "Running with $$N parallel jobs..."; \
		$(RM) Convergence_dr.png $(dr_DATA); \
		/usr/bin/time --format="$$N %e" --output=makefile_parallel.data --append \
			$(MAKE) Convergence_dr.png -j $$N 1>mf_out 2>mf_err; \
	done
	@gnuplot -e " \
	    set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
	    set output '$@'; \
	    set title 'Time to measure convergence vs cores used'; \
	    set xlabel 'Cores used'; \
	    set ylabel 'Time (s)'; \
	    set grid; \
	    plot 'makefile_parallel.data' using 1:2 with linespoints lw 2 lc rgb '#0072B2' title 'Time'"
	@$(RM) makefile_parallel.data mf_out mf_err

# ── Wavefunctions ──────────────────────────────────────────────────────────────

Wavefunctions.png: hydrogen_atom
	./hydrogen_atom -wf -rmax 10 -dr 0.02 > temp_wf.data
	@gnuplot -e " \
	    set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
	    set output '$@'; \
	    set title 'Hydrogen Wavefunctions'; \
	    set xlabel 'r'; \
	    set ylabel 'psi(r)'; \
	    set grid; \
	    set datafile separator ','; \
	    plot 'temp_wf.data' using 1:2 with lines lw 2 lc rgb '#0072B2' title 'n=1', \
	         'temp_wf.data' using 1:3 with lines lw 2 lc rgb '#D55E00' title 'n=2', \
	         'temp_wf.data' using 1:4 with lines lw 2 lc rgb '#009E73' title 'n=3'"
	@$(RM) temp_wf.data

# ── Binaries ───────────────────────────────────────────────────────────────────
# hydrogen_atom is listed separately so make resolves it as a file target
# before any convergence jobs that depend on it start running in parallel.

hydrogen_atom: hydrogen_atom.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

benchmark_tool test_suite: %: %.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ── Cleanup ────────────────────────────────────────────────────────────────────

clean:
	@$(RM) test_suite hydrogen_atom benchmark_tool \
	       $(SHARED_OBJS) test_suite.o hydrogen_atom.o benchmark_tool.o \
	       Out.txt fit.log err out Parallel.png \
	       *.png *.data \
	       bm_log.* bm_out.* bm_err.* \
	       $(dr_DATA) temp_conv_dr.data \
	       $(rmax_DATA) temp_conv_rmax.data \
	       temp_wf.data mf_out mf_err \
	       makefile_parallel.data
