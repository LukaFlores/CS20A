output: main.o life.o pent.o square.o slider.o blink4.o world.o simulation.o
	g++ -g -std=c++11 -Wall -Wextra -v main.o life.o pent.o square.o slider.o blink4.o world.o simulation.o -o output

main.o: main.cpp
	g++ -c -std=c++11 -g main.cpp

life.o: life.cpp
	g++ -c -std=c++11 -g life.cpp

pent.o: pent.cpp
	g++ -c -std=c++11 -g pent.cpp

square.o: square.cpp
	g++ -c -std=c++11 -g square.cpp

slider.o: slider.cpp
	g++ -c -std=c++11 -g slider.cpp

blink4.o: blink4.cpp
	g++ -c -std=c++11 -g blink4.cpp

world.o: world.cpp
	g++ -c -std=c++11 -g world.cpp

simulation.o: simulation.cpp
	g++ -c  -std=c++11 -g simulation.cpp

decode.o: decode.cpp
	g++ -std=c++11 -c decode.cpp

decode: decode.o
	g++ -std=c++11 -Wall -Wextra -v decode.o -o decode

clean:
	rm *.o output
