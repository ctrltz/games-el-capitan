#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "BodyBasics.h"
using namespace sf;


class ScoreBoard
{
private:
	bool isScoreBoard_;
	int nextState_;
public:
	void scoreBoardProcess(sf::RenderWindow & window, CBodyBasics & skelet, float timeRes);
	ScoreBoard();

	void setIsScoreBoard(bool isScoreBoard) {
		isScoreBoard_ = isScoreBoard;
	}
	bool getIsScoreBoard() {
		return isScoreBoard_;
	}
	int whatNext();
	void setNext(int nextState);
	void rectEmpty(sf::RenderWindow & window, int x1, int y1, int x2, int y2);

};