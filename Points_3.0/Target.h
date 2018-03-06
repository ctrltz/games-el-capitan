#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "BodyBasics.h"
using namespace sf;


class Target
{
private:
	float x, y;
	int number;
	int k;
public:
	//Target(String F, float X, float Y, float W, float H);
	float w, h;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	bool isActive;
	bool animationStart;
	Clock animationClock;
	int animationTime;
	int tarAnim;
	int spriteX;
	int spriteY;

	Target(float X, float Y, int n);
	Target() {};

	void targetDraw(sf::RenderWindow & window);

	float getTargetcoordinateX() {
		return x;
	}
	float getTargetcoordinateY() {
		return y;
	}
	int getTargetNumber() {
		return number;
	}

};
