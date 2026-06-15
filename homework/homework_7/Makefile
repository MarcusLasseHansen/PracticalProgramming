CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS   = -lstdc++ -lm

SHARED_SRCS = ../linalg/linalg.cpp
SHARED_OBJS = $(SHARED_SRCS:.cpp=.o)

.PHONY: all clean

all: Out.txt

Out.txt: a_checks b_checks c_checks
	./a_checks > Out.txt
	./b_checks >> Out.txt
	./c_checks >> Out.txt

a_checks: a_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

a_checks.o: a_checks.cpp monte_carlo.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

b_checks: b_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

b_checks.o: b_checks.cpp monte_carlo.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

c_checks: c_checks.o $(SHARED_OBJS)
	$(CXX) $^ -o $@ $(LDLIBS)

c_checks.o: c_checks.cpp monte_carlo.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) \
		*.o      \
		Out.txt \
		a_checks \
		b_checks \
		*~ \
		c_checks \
