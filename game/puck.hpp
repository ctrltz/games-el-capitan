#include <SFML/Graphics.hpp>

#ifndef PUCK
#define PUCK

struct Puck
{
public:
    Puck(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity);
    void update(int width, int height, float delta);
    sf::CircleShape shape();
    float radius();
    sf::Vector2f & position();
    sf::Vector2f & velocity();    
    
private:
    void walls_collide (int width, int height);

    sf::CircleShape shape_;
    float radius_;
    sf::Color color_;
    sf::Vector2f position_;
    sf::Vector2f velocity_;
};

#endif
