#include <SFML/Graphics.hpp>

#include "game.hpp"


Game::Game() : mWindow (sf::VideoMode(640, 480), "SFML Application"),
               mPlayer ()
{
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(sf::Color::Cyan);
}


void Game::run()
{
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        elapsed += clock.restart();
        
        while (elapsed > update_time)
        {
            processEvents();
            update();
            elapsed -= update_time;
        }
        
        render();
    }
}


void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}


void Game::update()
{
    while (true) {
        // Kinect  1 person
        // Player() <- person like
        // game.run();
    }
}


void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}
