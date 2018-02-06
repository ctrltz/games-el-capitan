#include <SFML/Graphics.hpp>

#ifndef GAME
#define GAME

struct Game
{
public: 
    Game();
    void run();
    
private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    const sf::Time update_time = sf::seconds(1.f / 60.f);
};

#endif
