output: main.o memorymanager.o 
	g++ -g -std=c++11 -Wall -Wextra -v main.o memorymanager.o -o output

test: test.o memorymanager.o 
	g++ -g -std=c++11 -Wall -Wextra -v test.o memorymanager.o -o output

main.o: main.cpp
	g++ -c -std=c++11 -g main.cpp

memorymanager.o: memorymanager.cpp
	g++ -c -std=c++11 -g memorymanager.cpp

test.o: test.cpp
	g++ -c -std=c++11 -g test.cpp

clean:
	rm *.o output

         

