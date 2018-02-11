#include <SFML/Graphics.hpp>
#include "puck.hpp"

#ifndef GAME
#define GAME

struct Game
{
public: 
    Game(int width, int height);
    void run();
    
private:
    void processEvents();
    void update();
    void collide_objects(Puck * first, Puck * second);
    void render();

    int width_, height_;
    sf::RenderWindow mWindow;
    Puck puck;
    Puck ** balls;
    const sf::Time update_time = sf::seconds(1.f / 60.f);
};

#endif
