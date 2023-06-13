output: main.o game.o entity.o shark.o room.o player.o maze.o
	g++ -g -std=c++11 -Wall -Wextra -v main.o game.o entity.o shark.o room.o player.o maze.o -o output

main.o: main.cpp
	g++ -c -std=c++11 -g main.cpp

entity.o: entity.cpp
	g++ -c -std=c++11 -g entity.cpp

game.o: game.cpp
	g++ -c -std=c++11 -g game.cpp

maze.o: maze.cpp
	g++ -c -std=c++11 -g maze.cpp

player.o: player.cpp
	g++ -c -std=c++11 -g player.cpp

room.o: room.cpp
	g++ -c -std=c++11 -g room.cpp

shark.o: shark.cpp
	g++ -c -std=c++11 -g shark.cpp

clean:
	rm *.o output

