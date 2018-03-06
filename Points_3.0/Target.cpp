#include "Target.h"
using namespace sf;


Target::Target(float X, float Y, int n)
{
	k = 0;
	isActive = true;
	animationStart = false;
	image.loadFromFile("images/bang_img.png");
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 150, 150));
	x = X; y = Y;
	tarAnim = 0;
	w = 160;
	h = 160;
}


void Target::targetDraw(sf::RenderWindow & window) {
	if (isActive)
	{
		sprite.setTextureRect(IntRect(0, 0, 150, 150));
		window.draw(sprite);
	}
	else
	{
		if (!animationStart)
		{
			animationClock.restart();
		}
		animationTime = animationClock.getElapsedTime().asMilliseconds();
		animationStart = true;
		if (tarAnim == 0) {
			spriteX = 0;
			spriteY = 150;
		}

		if (animationTime > 17) {
			spriteX = spriteX + 160;
			animationClock.restart();
			tarAnim = tarAnim + 1;
		}

		if (tarAnim == 8) {
			spriteX = 0;
			spriteY = 450;
		}
		sprite.setTextureRect(IntRect(spriteX, spriteY, w, h));
		window.draw(sprite);

		//sprite.setTextureRect(IntRect(610, 25, 80, 80));

	}
}