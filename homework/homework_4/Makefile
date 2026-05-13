CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = linalg_splines.cpp ../linalg/linalg.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Lin_spline.png Quad_spline.png Cube_spline.png Cube_spline_comparison.png

linear_data.txt: linear_plots Makefile
	./linear_plots > linear_data.txt

quadratic_data.txt: quadratic_plots Makefile
	./quadratic_plots > quadratic_data.txt

cubic_data.txt: cubic_plots Makefile
	./cubic_plots > cubic_data.txt

Lin_spline.png: linear_data.txt
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > plot.gnu
	@printf 'set grid\n' >> plot.gnu

	@# --- Function plot ---
	@printf 'set output "Lin_spline.png"\n' >> plot.gnu
	@printf 'set title "Linear Spline vs cos(x)"\n' >> plot.gnu
	@printf 'set xlabel "x"; set ylabel "y"\n' >> plot.gnu
	@printf 'plot "Out.txt" using 1:2 with lines lw 2 lc rgb "red" title "Spline", \\\n' >> plot.gnu
	@printf '     "Out.txt" using 1:3 with lines lw 2 lc rgb "blue" title "cos(x)"\n' >> plot.gnu

	@# --- Integral plot ---
	@printf 'set output "Lin_spline_int.png"\n' >> plot.gnu
	@printf 'set title "Spline Integral vs True Integral"\n' >> plot.gnu
	@printf 'set xlabel "x"; set ylabel "Integral"\n' >> plot.gnu
	@printf 'plot "Out.txt" using 1:4 with lines lw 2 lc rgb "green" title "Spline Integral", \\\n' >> plot.gnu
	@printf '     "Out.txt" using 1:5 with lines lw 2 lc rgb "black" title "True Integral"\n' >> plot.gnu

	gnuplot plot.gnu
	@$(RM) plot.gnu

Quad_spline.png: quadratic_data.txt
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > quad_plot.gnu
	@printf 'set grid\n' >> quad_plot.gnu

	@printf 'set output "Quad_spline.png"\n' >> quad_plot.gnu
	@printf 'set title "Quadratic Spline vs y=1,y=x,y=x*x"\n' >> quad_plot.gnu
	@printf 'set xlabel "x"; set ylabel "y"\n' >> quad_plot.gnu
	@printf 'plot "quadratic_data.txt" using 1:2 with lines lw 2 lc rgb "red" title "Spline 1", \\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:3 with lines lw 2 lc rgb "blue" title "1",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:4 with lines lw 2 lc rgb "red" title "Spline x",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:5 with lines lw 2 lc rgb "blue" title "x",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:6 with lines lw 2 lc rgb "red" title "Spline x*x",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:7 with lines lw 2 lc rgb "blue" title "x*x"\n' >> quad_plot.gnu


	@printf 'set output "Quad_spline_int.png"\n' >> quad_plot.gnu
	@printf 'set title "Spline Integral vs True Integral"\n' >> quad_plot.gnu
	@printf 'set xlabel "x"; set ylabel "Integral"\n' >> quad_plot.gnu
	@printf 'plot "quadratic_data.txt" using 1:8 with lines lw 2 lc rgb "red" title "Spline int(1)", \\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:9 with lines lw 2 lc rgb "blue" title "x",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:10 with lines lw 2 lc rgb "red" title "Spline int(x)",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:11 with lines lw 2 lc rgb "blue" title "1/2*x*x",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:12 with lines lw 2 lc rgb "red" title "Spline int(x*x)",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:13 with lines lw 2 lc rgb "blue" title "1/3*x*x*x"\n' >> quad_plot.gnu

	@printf 'set output "Quad_spline_deriv.png"\n' >> quad_plot.gnu
	@printf 'set title "Spline Derivative vs True Derivative"\n' >> quad_plot.gnu
	@printf 'set xlabel "x"; set ylabel "Derivative"\n' >> quad_plot.gnu
	@printf 'plot "quadratic_data.txt" using 1:14 with lines lw 2 lc rgb "red" title "Spline deriv(x)", \\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:15 with lines lw 2 lc rgb "blue" title "1",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:16 with lines lw 2 lc rgb "red" title "Spline deriv(x*x)",\\\n' >> quad_plot.gnu
	@printf '     "quadratic_data.txt" using 1:17 with lines lw 2 lc rgb "blue" title "2x"\n' >> quad_plot.gnu

	gnuplot quad_plot.gnu
	@$(RM) quad_plot.gnu

Cube_spline.png: cubic_data.txt
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > cube_1_plot.gnu
	@printf 'set grid\n' >> cube_1_plot.gnu

	@printf 'set output "Cube_spline.png"\n' >> cube_1_plot.gnu
	@printf 'set title "Cubic Spline vs y=1,y=x,y=x*x"\n' >> cube_1_plot.gnu
	@printf 'set xlabel "x"; set ylabel "y"\n' >> cube_1_plot.gnu
	@printf 'plot "cubic_data.txt" using 1:2 with lines lw 2 lc rgb "red" title "Spline 1", \\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:3 with lines lw 2 lc rgb "blue" title "1",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:4 with lines lw 2 lc rgb "red" title "Spline x",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:5 with lines lw 2 lc rgb "blue" title "x",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:6 with lines lw 2 lc rgb "red" title "Spline x*x",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:7 with lines lw 2 lc rgb "blue" title "x*x"\n' >> cube_1_plot.gnu


	@printf 'set output "Cube_spline_int.png"\n' >> cube_1_plot.gnu
	@printf 'set title "Spline Integral vs True Integral"\n' >> cube_1_plot.gnu
	@printf 'set xlabel "x"; set ylabel "Integral"\n' >> cube_1_plot.gnu
	@printf 'plot "cubic_data.txt" using 1:8 with lines lw 2 lc rgb "red" title "Spline int(1)", \\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:9 with lines lw 2 lc rgb "blue" title "x",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:10 with lines lw 2 lc rgb "red" title "Spline int(x)",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:11 with lines lw 2 lc rgb "blue" title "1/2*x*x",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:12 with lines lw 2 lc rgb "red" title "Spline int(x*x)",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:13 with lines lw 2 lc rgb "blue" title "1/3*x*x*x"\n' >> cube_1_plot.gnu

	@printf 'set output "Cube_spline_deriv.png"\n' >> cube_1_plot.gnu
	@printf 'set title "Spline Derivative vs True Derivative"\n' >> cube_1_plot.gnu
	@printf 'set xlabel "x"; set ylabel "Derivative"\n' >> cube_1_plot.gnu
	@printf 'plot "cubic_data.txt" using 1:14 with lines lw 2 lc rgb "red" title "Spline deriv(x)", \\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:15 with lines lw 2 lc rgb "blue" title "1",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:16 with lines lw 2 lc rgb "red" title "Spline deriv(x*x)",\\\n' >> cube_1_plot.gnu
	@printf '     "cubic_data.txt" using 1:17 with lines lw 2 lc rgb "blue" title "2x"\n' >> cube_1_plot.gnu

	gnuplot cube_1_plot.gnu
	@$(RM) cube_1_plot.gnu

## Recipe made with AI
Cube_spline_comparison.png: cubic_data.txt
	@printf 'set terminal pngcairo size 1200,900 enhanced font "Arial,10"\n' > cube_plot.gnu
	@printf 'set output "Cube_spline_comparison.png"\n' >> cube_plot.gnu

	@printf 'set multiplot layout 3,1 title "C++ spline vs gnuplot spline"\n' >> cube_plot.gnu
	@printf 'set grid\n' >> cube_plot.gnu

	@printf 'set datafile separator whitespace\n' >> cube_plot.gnu

	# ------------------------------------------------------------------
	# Function plot
	# ------------------------------------------------------------------
	@printf 'set title "Function: x*x"\n' >> cube_plot.gnu
	@printf 'set xlabel "x"\n' >> cube_plot.gnu
	@printf 'set ylabel "y"\n' >> cube_plot.gnu
	@printf 'plot \\\n' >> cube_plot.gnu
	@printf '    "cubic_data.txt" using 1:7 with lines lw 2 lc rgb "red" title "C++ spline", \\\n' >> cube_plot.gnu
	@printf '    "cubic_data.txt" using 1:7 smooth csplines lw 2 lc rgb "blue" title "gnuplot spline"\n' >> cube_plot.gnu

	# ------------------------------------------------------------------
	# Integral plot
	# ------------------------------------------------------------------
	@printf 'set title "Integral"\n' >> cube_plot.gnu
	@printf 'set xlabel "x"\n' >> cube_plot.gnu
	@printf 'set ylabel "Integral"\n' >> cube_plot.gnu
	@printf 'plot \\\n' >> cube_plot.gnu
	@printf '    "cubic_data.txt" using 1:13 with lines lw 2 lc rgb "red" title "C++ integral", \\\n' >> cube_plot.gnu
	@printf '    "cubic_data.txt" using 1:13 smooth csplines lw 2 lc rgb "blue" title "gnuplot spline integral"\n' >> cube_plot.gnu

	# ------------------------------------------------------------------
	# Derivative plot
	# ------------------------------------------------------------------
	@printf 'set title "Derivative"\n' >> cube_plot.gnu
	@printf 'set xlabel "x"\n' >> cube_plot.gnu
	@printf 'set ylabel "Derivative"\n' >> cube_plot.gnu
	@printf 'plot \\\n' >> cube_plot.gnu
	@printf '    "cubic_data.txt" using 1:17 with lines lw 2 lc rgb "red" title "C++ derivative", \\\n' >> cube_plot.gnu
	@printf '    "cubic_data.txt" using 1:17 smooth csplines lw 2 lc rgb "blue" title "gnuplot spline derivative"\n' >> cube_plot.gnu

	@printf 'unset multiplot\n' >> cube_plot.gnu

	@gnuplot cube_plot.gnu
	@$(RM) cube_plot.gnu

linear_plots: linear_plots.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

linear_plots.o: linear_plots.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

quadratic_plots: quadratic_plots.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

quadratic_plots.o: quadratic_plots.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

cubic_plots: cubic_plots.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

cubic_plots.o: cubic_plots.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

quadratic_check: quadratic_check.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

quadratic_check.o: quadratic_check.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) \
		linear_plots \
		quadratic_plots \
		cubic_plots \
		quadratic_check \
		*.o \
		../linalg/*.o \
		linear_data.txt \
		quadratic_data.txt \
		cubic_data.txt \
		plot.gnu \
		quad_plot.gnu \
		cube_1_plot.gnu \
		cube_plot.gnu \
		Lin_spline.png \
		Lin_spline_int.png \
		Quad_spline.png \
		Quad_spline_int.png \
		Quad_spline_deriv.png \
		Cube_spline.png \
		Cube_spline_int.png \
		Cube_spline_deriv.png \
		Cube_spline_comparison.png \
		Out.txt \
