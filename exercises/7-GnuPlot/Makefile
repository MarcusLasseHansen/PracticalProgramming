CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm
all: Plot_erf.png Plot_sgamma.png Plot_lngamma.png

Plot_erf.png: main
	./main --function 0 > erf.txt
	gnuplot -e "set terminal pngcairo size 800,600; \
	            set output 'Plot_erf.png'; \
	            set title 'Error Function (erf)'; \
	            set xlabel 'x'; \
	            set ylabel 'erf(x)'; \
	            set grid; \
	            plot 'erf.txt' using 1:2 with lines lw 2 lc rgb 'blue' title 'erf(x)', \
	                 'err_data.txt' using 1:2 with points pt 7 ps 1.5 lc rgb 'red' title 'Error Data'"

Plot_sgamma.png: main
	./main --function 1 > sgamma.txt
	gnuplot -e "set terminal pngcairo size 800,600; \
	            set output 'Plot_sgamma.png'; \
	            set title 'Sign Gamma Function (sgamma)'; \
	            set xlabel 'x'; \
	            set ylabel 'sgamma(x)'; \
	            set grid; \
	            plot 'sgamma.txt' using 1:2 with lines lw 2 lc rgb 'red' title 'sgamma(x)', \
	                 'gamma_data.txt' using 1:2 with points pt 7 ps 1.5 lc rgb 'blue' title 'Error Data'"

Plot_lngamma.png: main
	./main --function 2 > lngamma.txt
	gnuplot -e "set terminal pngcairo size 800,600; \
	            set output 'Plot_lngamma.png'; \
	            set title 'Log Gamma Function (lngamma)'; \
	            set xlabel 'x'; \
	            set ylabel 'lngamma(x)'; \
	            set grid; \
	            plot 'lngamma.txt' using 1:2 with lines lw 2 lc rgb 'green' title 'lngamma(x)', \
	                 'lngamma_data.txt' using 1:2 with points pt 7 ps 1.5 lc rgb 'red' title 'Error Data'"

main : main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

.PHONY:clean
clean:
	$(RM) main main.o erf.txt sgamma.txt lngamma.txt Plot_erf.png Plot_sgamma.png Plot_lngamma.png
