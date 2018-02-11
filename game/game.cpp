#include <iostream>
#include <SFML/Graphics.hpp>

#include "game.hpp"

using namespace std;


float len2 (sf::Vector2f const v)
{
    return v.x * v.x + v.y * v.y;
}


float dot (sf::Vector2f const v1, sf::Vector2f const v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}


float dist2 (sf::Vector2f const & p1, sf::Vector2f const & p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}


Game::Game(int width, int height) 
    : width_ (width), height_ (height)
    , mWindow (sf::VideoMode(width, height), "SFML Application")
    , puck (10.f, sf::Color::Cyan, sf::Vector2f(width / 2, height / 2), sf::Vector2f(150.f, 200.f))
{ 
    mWindow.setFramerateLimit(60);
    balls = (Puck **) new Puck *[56];
    for (int i = 0; i < 56; i++)
    {
        balls[i] = new Puck(10.f, sf::Color::White, 
                            sf::Vector2f(100.f + 50.f * (i % 8), 100.f + 50.f * (i / 8)),
                            sf::Vector2f(150.f * (1 - 2 * (i % 2)), 200.f * (2 * (i % 2) - 1)));
    }
}


void Game::run()
{
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        elapsed += clock.restart();
        // cout << elapsed.asSeconds() << endl;
        
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
        {
            mWindow.close();
        }
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        {
            mWindow.close();
        }    
    }
}


void Game::update()
{
    // puck.update(width_, height_, update_time.asSeconds());
    for (int i = 0; i < 56; i++)
    {
        balls[i]->update(width_, height_, update_time.asSeconds());
        for (int j = i + 1; j < 56; j++)
        {
            collide_objects(balls[i], balls[j]);
        }
    }
}


void Game::collide_objects(Puck * first, Puck * second)
{
    float threshold = (first->radius() + second->radius()) * (first->radius() + second->radius());
    if (dist2(first->position(), second->position()) <= threshold)
    {
        sf::Vector2f v1 = first->velocity(), v2 = second->velocity();
        sf::Vector2f x1 = first->position(), x2 = second->position();
        
        first->velocity() = v1 - (x1 - x2) * dot(v1 - v2, x1 - x2) / len2(x1 - x2);
        second->velocity() = v2 - (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);
    }
}

void Game::render()
{
    mWindow.clear();
    // mWindow.draw(puck.shape());
    for (int i = 0; i < 56; i++)
    {
        mWindow.draw(balls[i]->shape());
    }
    mWindow.display();
}
