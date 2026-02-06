CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm
Out.txt : main
	./main > Out.txt

main : main.o vec.o
	$(CXX) main.o vec.o -o main $(LDLIBS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

vec.o : vec.cpp
	$(CXX) $(CXXFLAGS) -c vec.cpp -o vec.o

.PHONEY:clean
clean:
	$(RM) main main.o Out.txt
