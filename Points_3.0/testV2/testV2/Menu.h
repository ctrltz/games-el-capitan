#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "BodyBasics.h"

class Menu
{
public:
	Menu();
	~Menu();
	//bool isMenu = 0;
	void menuProces(sf::RenderWindow & window, CBodyBasics & skelet);
	bool getIsMenu();
	void setIsMenu(bool isMenu);
	int whatNext();
	void setNext(int nextState);

private:
	bool isMenu_;
	int nextState_;
};
