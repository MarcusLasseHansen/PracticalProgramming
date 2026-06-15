CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = ../linalg/linalg.cpp ../homework_1/linalg_qr.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt Higgs.png

Out.txt: Makefile a_checks c_checks b_higgs
	./a_checks > Out.txt
	./b_higgs < higgs.data.txt >> Out.txt
	./c_checks >> Out.txt

Higgs.png: higgs.data Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > higgs_gnuplot.gnu
	@printf 'set grid\n' >> higgs_gnuplot.gnu
	@printf 'set output "Higgs.png"\n' >> higgs_gnuplot.gnu
	@printf 'set title "Numerically found WF vs Exact"\n' >> higgs_gnuplot.gnu
	@printf 'set xlabel "r"; set ylabel "f"\n' >> higgs_gnuplot.gnu
	@printf 'plot "higgs.data" using 1:2 with points lw 2 lc rgb "red" title "Real", \\\n' >> higgs_gnuplot.gnu
	@printf '     "higgs.data" using 1:3 with points lw 2 lc rgb "blue" title "Minimized"\n' >> higgs_gnuplot.gnu
	gnuplot higgs_gnuplot.gnu
	@$(RM) higgs_gnuplot.gnu

higgs.data: b_higgs
	./b_higgs --plot_output < higgs.data.txt > higgs.data

a_checks: a_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

a_checks.o: a_checks.cpp minimization.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

c_checks: c_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

c_checks.o: c_checks.cpp minimization.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

b_higgs: b_higgs.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

b_higgs.o: b_higgs.cpp minimization.hpp higgs.data.txt
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) \
		*.o      \
		Out.txt \
		a_checks \
		c_checks \
		*~ \
		b_higgs \
		higgs_gnuplot.gnu \
		Higgs.png \
		higgs.data \
