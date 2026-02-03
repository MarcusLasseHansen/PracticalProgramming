CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm
Out.txt : main
	./main > Out.txt

main : main.o sfuns.o
	$(CXX) main.o sfuns.o -o main $(LDLIBS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

sfuns.o : sfuns.cpp
	$(CXX) $(CXXFLAGS) -c sfuns.cpp -o sfuns.o

.PHONEY:clean
clean:
	$(RM) main main.o Out.txt
