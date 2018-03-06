#include "ScoreBoard.h"


ScoreBoard::ScoreBoard() {
	isScoreBoard_ = false;
}

int ScoreBoard::whatNext() {
	return nextState_;
}
void ScoreBoard::setNext(int next) {
	nextState_ = next;
}

void ScoreBoard::scoreBoardProcess(sf::RenderWindow & window, CBodyBasics & skelet, float timeRes) {
	Font font;
	font.loadFromFile("font/11583.ttf");
	Text text("", font, 150);
	text.setStyle(Text::Bold);

	float gameTime = timeRes / 1000.0;
	std::ostringstream gameTimeString;
	gameTimeString << gameTime;


	while (isScoreBoard_) {
		window.clear();
		//std::cout << skelet.skeletonPoints(7).X << " " << skelet.skeletonPoints(7).Y << " " << skelet.skeletonPoints(7).Z << "\n";

		text.setString(gameTimeString.str());
		text.setPosition(450, 150);
		window.draw(text);

		text.setPosition(450, 50);
		text.setString("Time:");
		window.draw(text);

		text.setPosition(150, 350);
		text.setString("Menu");
		window.draw(text);

		text.setPosition(750, 350);
		text.setString("Restart");
		window.draw(text);

		int menuNum = 0;
		if (IntRect(145, 400, 342, 510).contains(Mouse::getPosition(window)))
		{
			rectEmpty(window, 145, 400, 342, 510);
			menuNum = 1;
		}
		if (IntRect(745, 400, 1020, 510).contains(Mouse::getPosition(window)))
		{
			rectEmpty(window, 745, 400, 1020, 510);
			menuNum = 2;
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { nextState_ = 1; isScoreBoard_ = false; }
			if (menuNum == 2) { nextState_ = 2; isScoreBoard_ = false; }

		}

		window.display();
	}

}

void ScoreBoard::rectEmpty(sf::RenderWindow & window, int x1, int y1, int x2, int y2)
{
	sf::Vector2f vec1;
	vec1 = (Vector2f)Mouse::getPosition(window);
	sf::Vertex line1[] =
	{
		sf::Vertex(sf::Vector2f(x1, y1)),
		sf::Vertex(sf::Vector2f(x1, y2))
	};
	window.draw(line1, 2, sf::Lines);

	sf::Vertex line2[] =
	{
		sf::Vertex(sf::Vector2f(x1, y2)),
		sf::Vertex(sf::Vector2f(x2, y2))
	};
	window.draw(line2, 2, sf::Lines);

	sf::Vertex line3[] =
	{
		sf::Vertex(sf::Vector2f(x2, y2)),
		sf::Vertex(sf::Vector2f(x2, y1))
	};
	window.draw(line3, 2, sf::Lines);
	sf::Vertex line4[] =
	{
		sf::Vertex(sf::Vector2f(x2, y1)),
		sf::Vertex(sf::Vector2f(x1, y1))
	};
	window.draw(line4, 2, sf::Lines);
}
