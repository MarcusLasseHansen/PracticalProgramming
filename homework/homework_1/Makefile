CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = linalg_qr.cpp ../linalg/linalg.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt Out.png

Out.txt: test_suite Makefile
	./test_suite > Out.txt

Out.png: out.times.data Makefile
	gnuplot -e "set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
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

## change the sequence here for whatever fits your box
out.times.data : benchmark_tool
	>$@
	for N in $$(seq 150 150 1500); do \
		time --format "$$N %e" --output $@ --append \
		./$< $$N 1>out 2>err ;\
	done

test_suite: test_suite.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

benchmark_tool: benchmark_tool.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

test_suite.o: test_suite.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

benchmark_tool.o: benchmark_tool.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) test_suite benchmark_tool $(SHARED_OBJS) test_suite.o benchmark_tool.o Out.txt err out out.times.data Out.png fit.log *.o
