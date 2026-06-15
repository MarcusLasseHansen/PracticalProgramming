CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = integrator.cpp ../linalg/linalg.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt Erf_acc.png

Erf_acc.png: erf.data Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > erf_plot.gnu
	@printf 'set grid\n' >> erf_plot.gnu
	@printf 'set logscale xy\n' >> erf_plot.gnu
	@printf 'set output "Erf_acc.png"\n' >> erf_plot.gnu
	@printf 'set title "Erf(1) inaccuracy with intergration routine vs acc"\n' >> erf_plot.gnu
	@printf 'set xlabel "acc"; set ylabel "ΔErf(1)"\n' >> erf_plot.gnu
	@printf 'plot "erf.data" using 1:2 with points lw 2 lc rgb "red" title "ΔErf(1)", \n' >> erf_plot.gnu

	gnuplot erf_plot.gnu
	@$(RM) erf_plot.gnu

erf.data: erf
	./erf > erf.data

Out.txt: a_checks b_checks c_checks
	./a_checks > Out.txt
	./b_checks >> Out.txt
	./c_checks >> Out.txt 

a_checks: a_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

a_checks.o: a_checks.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

c_checks: c_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

c_checks.o: c_checks.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

b_checks: b_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

b_checks.o: b_checks.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

erf: erf.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

erf.o: erf.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) \
		*.o      \
		a_checks \
		Out.txt \
		erf.data \
		Erf_acc.png \
		erf \
		erf_plot.gnu \
		*~ \
		b_checks \
		c_checks \
