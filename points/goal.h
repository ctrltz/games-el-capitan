#include <SFML/Graphics.hpp>

#include "player.h"

#ifndef GOAL
#define GOAL

struct Goal
{
public:
    sf::CircleShape shape;             // или sf::Sprite sprite;
    bool hit(Player player);
};

#endif
