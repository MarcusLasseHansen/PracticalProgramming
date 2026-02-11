CXXFLAGS = -Wall -Wextra -Werror -std=c++23 -O
LDLIBS = -lstdc++ -lm
Out.txt : main
	echo "Task 1" > Out.txt
	./main -n 1 -n 2 -n 3 -n 4 -n 5 >> Out.txt
	echo "Task 2" >> Out.txt
	echo 1 2 3 4 5 | ./main >> Out.txt
	echo "Task 3" >> Out.txt
	./main --input my_input_file.txt --output my_output_file.txt
	cat my_output_file.txt >> Out.txt

main : main.o
	$(CXX) main.o -o main $(LDLIBS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

.PHONEY:clean
clean:
	$(RM) main main.o Out.txt my_output_file.txt
