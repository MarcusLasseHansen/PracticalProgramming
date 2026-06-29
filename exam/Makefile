CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = ../homework/linalg/linalg.cpp ../homework/homework_2/linalg_evd.cpp ../homework/homework_1/linalg_qr.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt Extra_two.png Extra_three.png

Out.txt: Makefile extra_one
	./extra_one > Out.txt

Extra_two.png: extra_two.data 
	gnuplot -e "set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
	            set output '$@'; \
	            set title 'Runtime vs Matrix Size'; \
	            set xlabel 'Matrix Size'; \
	            set ylabel 'Time (ms)'; \
	            set grid; \
		    set fit quiet; \
	            f(x) = a*x**2; \
	            fit f(x) '$<' using 1:2 via a; \
	            plot '$<' using 1:2 with linespoints pt 7 ps 1.2 lw 2 lc rgb '#0072B2' title 'data', \
	                 f(x) with lines lw 2 lc rgb '#D55E00' title sprintf('%.3e * N^2', a)"

Extra_three.png: extra_three.data 
	gnuplot -e "set terminal pngcairo enhanced font 'Arial,12' size 800,600; \
	            set output '$@'; \
	            set title 'Runtime vs Matrix Size'; \
	            set xlabel 'Matrix Size'; \
	            set ylabel 'Time (ns)'; \
	            set grid; \
		    set fit quiet; \
	            f(x) = a*x; \
	            fit f(x) '$<' using 1:2 via a; \
	            plot '$<' using 1:2 with linespoints pt 7 ps 1.2 lw 2 lc rgb '#0072B2' title 'data', \
	                 f(x) with lines lw 2 lc rgb '#D55E00' title sprintf('%.3e * N', a)"


extra_two.data: extra_two
	./extra_two > extra_two.data

extra_three.data: extra_three
	./extra_three > extra_three.data

extra_two: extra_two.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

extra_two.o: extra_two.cpp hessenberg.hpp modified_qr.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

extra_three: extra_three.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

extra_three.o: extra_three.cpp hessenberg.hpp modified_evd.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

extra_one: extra_one.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

extra_one.o: extra_one.cpp hessenberg.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) \
		*.o      \
		Out.txt \
		*~ \
