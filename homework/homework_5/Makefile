CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = ode.cpp ../linalg/linalg.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt C.gif B_1.png B_2.png B_3.png

Out.txt: a3_test.txt a4_test.txt
	cat a3_test.txt > Out.txt
	cat a4_test.txt >> Out.txt
	rm a3_test.txt a4_test.txt

a3_test.txt: a3_tests Makefile
	./a3_tests > a3_test.txt

a4_test.txt: a4_test Makefile
	./a4_test > a4_test.txt

B_1.png: b_test_1.txt
	gnuplot -e 'set terminal png; set output "B_1.png"; set title "Newtonian circular orbit (epsilon=0, u0=1, u1=0)"; plot "b_test_1.txt" using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle'
	rm b_test_1.txt

B_2.png: b_test_2.txt
	gnuplot -e 'set terminal png; set output "B_2.png"; set title "Newtonian elliptical orbit (epsilon=0, u0=1, u1=-0.5)"; plot "b_test_2.txt" using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle'
	rm b_test_2.txt

B_3.png: b_test_3.txt
	gnuplot -e 'set terminal png; set output "B_3.png"; set title "Relativistic precession (epsilon=0.01, u0=1, u1=-0.5)"; plot "b_test_3.txt" using (1/$$2)*cos($$1):(1/$$2)*sin($$1) with lines notitle'
	rm b_test_3.txt


C.gif: c_test.txt Makefile
	#Gif made by claude sonnet 4.6
	awk 'NR==1{t=$$1; print; next} $$1 >= t + 0.05 {t=$$1; print}' c_test.txt > c_sampled.txt
	printf '%s\n' \
	'set terminal gif animate delay 5 size 800,800' \
	'set output "C.gif"' \
	'set xrange [-3:3]' \
	'set yrange [-3:3]' \
	'set size square' \
	'set grid' \
	'set key outside' \
	'tail = 25' \
	'n = int(system("wc -l < c_sampled.txt"))' \
	'do for [i=1:n] {' \
	'    start = (i > tail) ? i - tail : 0' \
	'    plot \' \
	'        "c_sampled.txt" every ::start::i-1 using 2:3 with lines lc rgb "red" lw 2 title "obj1", \' \
	'        "" every ::start::i-1 using 2:3 with points pt 7 ps 1.5 lc rgb "red" notitle, \' \
	'        "" every ::start::i-1 using 4:5 with lines lc rgb "blue" lw 2 title "obj2", \' \
	'        "" every ::start::i-1 using 4:5 with points pt 7 ps 1.5 lc rgb "blue" notitle, \' \
	'        "" every ::start::i-1 using 6:7 with lines lc rgb "green" lw 2 title "obj3", \' \
	'        "" every ::start::i-1 using 6:7 with points pt 7 ps 1.5 lc rgb "green" notitle' \
	'}' \
	> c_test.gnuplot
	gnuplot c_test.gnuplot
	rm c_test.txt c_sampled.txt c_test.gnuplot

b_test_1.txt: b_test Makefile
	./b_test 1 > b_test_1.txt

b_test_2.txt: b_test Makefile
	./b_test 2 > b_test_2.txt

b_test_3.txt: b_test Makefile
	./b_test 3 > b_test_3.txt

c_test.txt: c_test
	./c_test > c_test.txt

a3_tests: a3_tests.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

a3_tests.o: a3_tests.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

a4_test: a4_test.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

a4_test.o: a4_test.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

b_test: b_test.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

b_test.o: b_test.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

c_test: c_test.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

c_test.o: c_test.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) \
		a3_tests \
		a4_test  \
		b_test   \
		b_test_1.txt \
		b_test_2.txt \
		b_test_3.txt \
		B_1.png \
		B_2.png \
		B_3.png \
		c_test   \
		c_test.txt \
		C.gif \
		c_sampled.txt \
		c_test.gnuplot \
		*.o      \
		../linalg/*.o \
		a3_test.txt \
		a4_test.txt \
		Out.txt \
