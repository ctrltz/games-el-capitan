#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "BodyBasics.h"
#include "Menu.h"
#include "Target.h"
#include "ScoreBoard.h"
#include "Game.h"
using namespace sf;

float timeRes;


enum States {
	GAME = 1, RC_ORANGE = 3, RC_YELLOW = 5, RC_GREEN = 7, RC_BLUE = 9,
	RC_INDIGO = 11, RC_VIOLET = 13
};

void game(sf::RenderWindow & window) {
	Menu menu;
	ScoreBoard scoreBoard;
	GameProcess gameProcess;
	CBodyBasics application;
	application.Run();


	while (window.isOpen())
	{
		
		if (menu.getIsMenu()) {
			menu.menuProces(window, application);
		}
		switch (menu.whatNext())
		{
		case 2:
			gameProcess.setIsGameProcess(true);
			menu.setNext(0);
			break;
		case 3:
			scoreBoard.setIsScoreBoard(true);
			menu.setNext(0);
			break;
		}

		if (gameProcess.getIsGameProcess()) {
			gameProcess.gameProces(window, application);
		}
		switch (gameProcess.whatNext())
		{
		case 1:
			menu.setIsMenu(true);
			gameProcess.setNext(0);
			break;
		case 3:
			scoreBoard.setIsScoreBoard(true);
			gameProcess.setNext(0);
			break;
		}
		
		if (scoreBoard.getIsScoreBoard() ){
			scoreBoard.scoreBoardProcess(window, application, gameProcess.getTime());
		}
		switch (scoreBoard.whatNext())
		{
		case 2:
			gameProcess.setIsGameProcess(true);
			scoreBoard.setNext(5);
			break;
		case 1:
			menu.setIsMenu(true);
			scoreBoard.setNext(0);
			break;
		}		
	}
}


int main() {
	sf::RenderWindow window(sf::VideoMode(1100, 645), "game");

	game(window);
}