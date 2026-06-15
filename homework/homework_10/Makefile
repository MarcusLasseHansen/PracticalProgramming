CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = ../linalg/linalg.cpp ../homework_1/linalg_qr.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt A.png B.png C.png

C.png: cdata.txt Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > c.gnu
	@printf 'set output "C.png"\n' >> c.gnu
	@printf 'set grid\n' >> c.gnu
	@printf 'set xlabel "x"\n' >> c.gnu
	@printf 'set title "ODE Solution y(x)"\n' >> c.gnu
	@printf 'plot "cdata.txt" u 1:2 w l lw 2 lc rgb "red"  title "exact cos(x)", \\\n' >> c.gnu
	@printf '     "cdata.txt" u 1:4 w l lw 2 lc rgb "blue" title "ANN"\n' >> c.gnu
	gnuplot c.gnu
	@$(RM) c.gnu


A.png: adata.txt Makefile
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' > a.gnu
	@printf 'set grid\n' >> a.gnu
	@printf 'set output "A.png"\n' >> a.gnu
	@printf 'set title "ANN solution vs Exact"\n' >> a.gnu
	@printf 'set xlabel "r"; set ylabel "f"\n' >> a.gnu
	@printf 'plot "adata.txt" using 1:2 with points lw 2 lc rgb "red" title "Real", \\\n' >> a.gnu
	@printf '     "adata.txt" using 1:3 with points lw 2 lc rgb "blue" title "ANN fit"\n' >> a.gnu
	gnuplot a.gnu
	@$(RM) a.gnu

adata.txt: adata
	./adata > adata.txt

Out.txt: Makefile a_checks b_checks c_checks
	./a_checks > Out.txt
	./b_checks >> Out.txt
	./c_checks >> Out.txt

a_checks: a_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

a_checks.o: a_checks.cpp ../homework_9/minimization.hpp network.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

adata: adata.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

adata.o: adata.cpp ../homework_9/minimization.hpp network.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


#Got help from claude AI to make several plots in one file
B.png: bdata.txt Makefile
	@printf 'set terminal pngcairo size 1200,900 enhanced font "Arial,10"\n' > b.gnu
	@printf 'set output "B.png"\n' >> b.gnu
	@printf 'set multiplot layout 2,2 title "ANN: response, 1st/2nd derivatives and anti-derivative"\n' >> b.gnu
	@printf 'set grid\n' >> b.gnu
	@printf 'set xlabel "x"\n' >> b.gnu
	@printf 'set title "Response"\n' >> b.gnu
	@printf 'plot "bdata.txt" u 1:2 w l lw 2 lc rgb "red"  title "g(x) exact", \\\n' >> b.gnu
	@printf '     "bdata.txt" u 1:6 w l lw 2 lc rgb "blue" title "ANN fit"\n' >> b.gnu
	@printf 'set title "1st derivative"\n' >> b.gnu
	@printf 'plot "bdata.txt" u 1:3 w l lw 2 lc rgb "red"  title "g'"'"'(x) exact", \\\n' >> b.gnu
	@printf '     "bdata.txt" u 1:7 w l lw 2 lc rgb "blue" title "ANN d/dx"\n' >> b.gnu
	@printf 'set title "2nd derivative"\n' >> b.gnu
	@printf 'plot "bdata.txt" u 1:4 w l lw 2 lc rgb "red"  title "g'"'"''"'"'(x) exact", \\\n' >> b.gnu
	@printf '     "bdata.txt" u 1:8 w l lw 2 lc rgb "blue" title "ANN d²/dx²"\n' >> b.gnu
	@printf 'set title "Anti-derivative"\n' >> b.gnu
	@printf 'plot "bdata.txt" u 1:5 w l lw 2 lc rgb "red"  title "G(x) numeric", \\\n' >> b.gnu
	@printf '     "bdata.txt" u 1:9 w l lw 2 lc rgb "blue" title "ANN anti-deriv"\n' >> b.gnu
	@printf 'unset multiplot\n' >> b.gnu
	gnuplot b.gnu
	@$(RM) b.gnu

bdata.txt: bdata
	./bdata > bdata.txt

b_checks: b_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

b_checks.o: b_checks.cpp ../homework_9/minimization.hpp network.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bdata: bdata.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

bdata.o: bdata.cpp ../homework_9/minimization.hpp network.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

cdata.txt: cdata
	./cdata > cdata.txt

c_checks: c_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

c_checks.o: c_checks.cpp ../homework_9/minimization.hpp network.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

cdata: cdata.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

cdata.o: cdata.cpp ../homework_9/minimization.hpp network.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) \
		*.o      \
		Out.txt \
		a_checks \
		b_checks \
		c_checks \
		*~ \
		adata \
		bdata \
		cdata \
		A.png \
		B.png \
		C.png \
		adata.txt \
		bdata.txt \
		cdata.txt \
		a.gnu \
		b.gnu \
