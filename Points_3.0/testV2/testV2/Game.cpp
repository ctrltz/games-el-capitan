#include "Game.h"
#include "Target.h"

float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}


int GameProcess::whatNext() {
	return nextState_;
}
void GameProcess::setNext(int next) {
	nextState_ = next;
}
float GameProcess::getTime() {
	return gTime;
}

GameProcess::GameProcess()
{
	gTime = 0;
}

GameProcess::~GameProcess()
{
}

void GameProcess::gameProces(sf::RenderWindow & window, CBodyBasics & skelet) {

	Font font;
	font.loadFromFile("font/11583.ttf");
	Text text("", font, 150);
	//text.setColor(Color::White);
	text.setStyle(Text::Bold);

	Clock gameTimeClock;
	Time t1;
	gameTimeClock.restart();
	Target target1(800, 350, 1);
	Target target2(450, 150, 2);
	Target target3(120, 120, 3);

	Clock cl;

	while (isGameProcess_) {
		target2.sprite.setPosition(target2.getTargetcoordinateX() - 65, target2.getTargetcoordinateY() - 65);
		target1.sprite.setPosition(target1.getTargetcoordinateX() - 65, target1.getTargetcoordinateY() - 65);
		target3.sprite.setPosition(target3.getTargetcoordinateX() - 65, target3.getTargetcoordinateY() - 65);
		sf::Vector2f vec1, vec2;
		vec1 = (Vector2f)Mouse::getPosition(window);
		window.clear();
		vec2.x = target3.getTargetcoordinateX();
		vec2.y = target3.getTargetcoordinateY();
		if (dist2(vec1, vec2) <= 4000) {
			if (!target2.isActive) target3.isActive = false;
		}
		vec2.x = target2.getTargetcoordinateX();
		vec2.y = target2.getTargetcoordinateY();
		if (dist2(vec1, vec2) <= 4000) {
			if (!target1.isActive) target2.isActive = false;
		}
		vec2.x = target1.getTargetcoordinateX();
		vec2.y = target1.getTargetcoordinateY();
		if (dist2(vec1, vec2) <= 4000) {
			target1.isActive = false;
		}
		if (!target3.isActive)
		{
			t1 = gameTimeClock.getElapsedTime();
			gTime = t1.asMilliseconds();
			isGameProcess_ = false; nextState_ = 3;
		}

		float gameTime = gameTimeClock.getElapsedTime().asMilliseconds() / 1000.0;
		std::ostringstream gameTimeString;
		gameTimeString << gameTime;
		text.setString(gameTimeString.str());
		text.setPosition(50, 400);
		window.draw(text);

		target1.targetDraw(window);
		target2.targetDraw(window);
		target3.targetDraw(window);
		window.display();

/*
		if (cl.getElapsedTime().asMilliseconds() > 500) {
			std::cout << skelet.skeletonPoints(7).X << " " << skelet.skeletonPoints(7).Y << " " << skelet.skeletonPoints(7).Z << "\n";
			cl.restart();
		}*/

		
	}

}
