# makefile reworked with the help of chatgpt
CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = linalg_ols.cpp ../linalg/linalg.cpp ../homework_1/linalg_qr.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt Out_rad.png

Out.txt: rad_decay Makefile
	./rad_decay > Out.txt

# plotting made by chatgpt
Out_rad.png: Out.txt
	@# Extract data: Time, y, and dy
	@awk 'NR>4 && $$1 ~ /^[0-9]/ {printf "%s %s %s\n", $$1, $$2, $$5}' Out.txt > temp_data.txt
	@# Extract coefficients and uncertainties
	@awk '\
		/Fit result:/ { a_val=$$5; gsub(/,/,"",a_val); lam_val=$$8; } \
		/Uncertainties:/ { d_lna=$$4; gsub(/,/,"",d_lna); d_lam=$$7; } \
		END { \
			print "ln_a = log(" a_val ")"; \
			print "lam = " lam_val; \
			print "d_lna = " d_lna; \
			print "d_lam = " d_lam; \
			print "y_fit(x) = exp(ln_a - lam*x)"; \
			print "y_up(x) = exp((ln_a + d_lna) - (lam - d_lam)*x)"; \
			print "y_low(x) = exp((ln_a - d_lna) - (lam + d_lam)*x)"; \
		}' Out.txt > temp_plot.gnu
	@printf 'set terminal pngcairo size 800,600 enhanced font "Arial,10"\n' >> temp_plot.gnu
	@printf 'set output "Out_rad.png"\n' >> temp_plot.gnu
	@printf 'set title "ThX Decay: Best Fit and Uncertainty Envelope"\n' >> temp_plot.gnu
	@printf 'set xlabel "Time (days)"; set ylabel "Activity (relative units)"\n' >> temp_plot.gnu
	@printf 'set grid\n' >> temp_plot.gnu
	@printf 'plot "temp_data.txt" with yerrorbars lc rgb "black" pt 7 title "Data", \\\n' >> temp_plot.gnu
	@printf '     y_fit(x) lw 2 lc rgb "red" title "Best Fit", \\\n' >> temp_plot.gnu
	@printf '     y_up(x) lt 2 lc rgb "blue" title "F(c + {/Symbol d}c)", \\\n' >> temp_plot.gnu
	@printf '     y_low(x) lt 2 lc rgb "blue" title "F(c - {/Symbol d}c)"\n' >> temp_plot.gnu
	gnuplot temp_plot.gnu
	@$(RM) temp_data.txt temp_plot.gnu

rad_decay: rad_decay.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

rad_decay.o: rad_decay.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) rad_decay $(SHARED_OBJS) rad_decay.o Out.txt temp_data.txt Out_rad.png
