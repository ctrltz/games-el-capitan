#include <SFML/Graphics.hpp>
#include <iostream>
#include "BodyBasics.h"
using namespace sf;

int main() {
	CBodyBasics skilet;
	skilet.Run();

	sf::RenderWindow window(sf::VideoMode(1100, 645), "Kolibroka");
	sf::Texture texture;
	Image image;
	Sprite sprite;

	image.loadFromFile("images/krug.png");
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 150, 150));
	Clock clock;

	while (window.isOpen())
	{
		window.clear();
		float X = skilet.skeletonPoints(7).X;
		float Y = -skilet.skeletonPoints(7).Y;
		float Z = skilet.skeletonPoints(7).Z;

		float x = X * 1100 / 4 + 550;
		float y = Y * 645 / 2 + 323;
		if (clock.getElapsedTime().asMilliseconds() > 500) {
			std::cout << X << " " << Y << " " << Z << "\n";
			clock.restart();
		}
		if ((Z > 2.0) && (Z < 2.2)) {
			sprite.setTextureRect(IntRect(0, 0, 150, 150));
		}
		else
		{
			sprite.setTextureRect(IntRect(170, 0, 150, 150));
		}
		sprite.setPosition(x, y);
		window.draw(sprite);
		window.display();
		
	}


}
