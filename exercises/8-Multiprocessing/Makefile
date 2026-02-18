CXX := g++
CXXFLAGS += -std=c++23 -Wall -O
LDLIBS := -lstdc++ -lm -lpthread
TIME = time --append --output $@ --format "$$nthreads %e %U"
NTERMS :=1e9

.PHONY: all clean

all: times.svg

times.svg: out.times
	echo '\
		set terminal svg ;\
		set output "$@" ;\
		set xlabel "number of threads" ;\
		set ylabel "real time" ;\
		plot "$<" using 1:2 with linespoints title "times" ;\
		' | tee log.times | gnuplot
out.times: main Makefile
	>$@
	>log.main
	for nthreads in 1 2 3 4 5 6 7 8 9 10 11 12; \
		do $(TIME) ./main --terms $(NTERMS) --threads $$nthreads >> log.main; \
	done

main: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f main out.times log.main times.svg log.times
