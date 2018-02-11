all: sfml-game

sfml-game:  main.o game.o puck.o
	g++ main.o game.o puck.o -o sfml-game -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp game.hpp
	g++ -c -Wall -std=gnu++11 main.cpp game.hpp

game.o: game.cpp game.hpp puck.hpp
	g++ -c -Wall -std=gnu++11 game.cpp game.hpp
	
puck.o: puck.cpp puck.hpp
	g++ -c -Wall -std=gnu++11 puck.cpp puck.hpp
    
clean:
	rm *.o *.hpp.gch sfml-game
