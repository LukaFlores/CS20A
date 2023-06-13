output: main.o tests.o
	g++ -g -std=c++11 -Wall -Wextra -v main.o tests.o -o output

main.o: main.cpp
	g++ -c -std=c++11 -g main.cpp

tests.o: tests.cpp
	g++ -c -std=c++11 -g tests.cpp

clean:
	rm *.o output

