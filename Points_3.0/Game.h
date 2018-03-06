#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "BodyBasics.h"
using namespace sf;

class GameProcess
{
public:
	GameProcess();
	~GameProcess();
	void gameProces(sf::RenderWindow & window, CBodyBasics & skelet);

	bool getIsGameProcess() {
		return isGameProcess_;
	}
	void setIsGameProcess(bool isGameProcess) {
		isGameProcess_ = isGameProcess;
	}
	int whatNext();
	void setNext(int nextState);
	float getTime();
private:
	bool isGameProcess_;
	int nextState_;
	float gTime;

};