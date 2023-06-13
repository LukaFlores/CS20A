output: main.o memorymanager.o wordlist.o 
	g++ -g -std=c++11 -Wall -Wextra -v main.o memorymanager.o wordlist.o -o output

test: main.o memorymanager.o wordlist.o p2unittests.o
	g++ -g -std=c++11 -Wall -Wextra -v  p2unittests.o memorymanager.o wordlist.o -o output

main.o: main.cpp
	g++ -c -std=c++11 -g main.cpp

memorymanager.o: memorymanager.cpp
	g++ -c -std=c++11 -g memorymanager.cpp

wordlist.o: wordlist.cpp
	g++ -c -std=c++11 -g wordlist.cpp

p2unittests.o: p2unittests.cpp
	g++ -c -std=c++11 -g p2unittests.cpp

clean:
	rm *.o output

         
