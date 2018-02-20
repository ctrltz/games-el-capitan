#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace sf;

bool isGame = false;
bool isMenu = false;
bool isScoreBoard = false;
float timeRes;
void rectEmpty(sf::RenderWindow & window, int x1, int y1, int x2, int y2);

class Menu
{
public:
	Menu();
	~Menu();
	//bool isMenu = 0;
	void menuProces(sf::RenderWindow & window);

private:

};

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::menuProces(sf::RenderWindow & window) {
	sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/logo.jpg");
	sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(345, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { isMenu = false; isGame = true;} //если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
	////////////////////////////////////////////////////
}

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
}


void Target::targetDraw(sf::RenderWindow & window) {
	if (isActive) 
	{
		sprite.setTextureRect(IntRect(0, 0, 150, 150));
		window.draw(sprite);
	}
	else
	{
		int animationSpeed = 50;
		if (!animationStart)
		{
			animationClock.restart();
		}
		animationTime = animationClock.getElapsedTime().asMilliseconds();
		animationStart = true;
		if (k == 0) {
			x = x + 50;
			k++;
			y = y + 50;
		}
		sprite.setTextureRect(IntRect(20, 190, 30, 30));
		if ((animationTime >= animationSpeed) && (animationTime < animationSpeed * 2))
		{
			sprite.setTextureRect(IntRect(55, 180, 50, 50));

			if (k == 1){
				x = x - 10;
				k++;
				y = y - 10;
			}
		}
		if ((animationTime >= animationSpeed*2) && (animationTime < animationSpeed*3))
		{
			sprite.setTextureRect(IntRect(100, 170, 70, 70));
			if (k == 2) {
				x = x - 10;
				k++;
				y = y - 10;
			}
		}
		if ((animationTime >= animationSpeed*3) && (animationTime < animationSpeed * 4))
		{
			sprite.setTextureRect(IntRect(180, 150, 110, 110));
			if (k == 3) {
				x = x - 20;
				k++;
				y = y -20;
			}
		}
		if ((animationTime >= animationSpeed * 4) && (animationTime < animationSpeed * 5))
		{
			sprite.setTextureRect(IntRect(360, 185, 65, 65));
			if (k == 4) {
				x = x + 20;
				k++;
				y = y + 20;
			}
		}
		if ((animationTime >= animationSpeed * 5) && (animationTime < animationSpeed * 6))
		{
			sprite.setTextureRect(IntRect(440, 175, 75, 75));
			if (k == 5) {
				x = x - 10;
				k++;
				y = y - 10;
			}
		}
		if ((animationTime >= animationSpeed * 6) && (animationTime < animationSpeed * 7))
		{
			sprite.setTextureRect(IntRect(15, 285, 100, 100));
			if (k == 6) {
				x = x - 10;
				k++;
				y = y - 10;
			}
		}
		if (animationTime >= animationSpeed * 7)
		{
			sprite.setTextureRect(IntRect(385,455, 130, 130));
			if (k == 7) {
				x = x - 10;
				k++;
				y = y - 10;
			}
		}

		//sprite.setTextureRect(IntRect(610, 25, 80, 80));
		window.draw(sprite);
	}
}

float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

void gameProces(sf::RenderWindow & window) {

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
	
	while (isGame) {
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
			timeRes = t1.asMilliseconds();
			isGame = false; isScoreBoard = true;
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
	}
	
}

void scoreBoard(sf::RenderWindow & window) {
	Font font;
	font.loadFromFile("font/11583.ttf");
	Text text("", font, 150);
	text.setStyle(Text::Bold);

	float gameTime = timeRes / 1000.0;
	std::ostringstream gameTimeString;
	gameTimeString << gameTime;

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
		if (menuNum == 1) { isMenu = true; isGame = false; isScoreBoard = false; } //если нажали первую кнопку, то выходим из меню 
		if (menuNum == 2) { isMenu = false; isGame = true; isScoreBoard = false; }

	}
	
	window.display();


}

void rectEmpty(sf::RenderWindow & window, int x1, int y1, int x2, int y2)
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

int main() {
	sf::RenderWindow window(sf::VideoMode(1100, 645), "game");

	Menu menu;
	isMenu = true;
	while (true)
	{
		if (isMenu) {
			menu.menuProces(window);
			window.clear();
		}
		window.clear();
		if (isGame) {
			gameProces(window);
		}
		window.clear();
		if (isScoreBoard) {
			scoreBoard(window);
		}
	}
	
	
}