CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm
Out.txt : main
	./main > Out.txt

main : main.o hello.o
	$(CXX) main.o hello.o -o main $(LDLIBS)

main.o : main.cpp hello.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

hello.o : hello.cpp hello.hpp
	$(CXX) $(CXXFLAGS) -c hello.cpp -o hello.o

.PHONEY:clean
clean:
	$(RM) main main.o Out.txt hello.o
