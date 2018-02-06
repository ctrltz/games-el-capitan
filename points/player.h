#include <SFML/Graphics.hpp>

#ifndef PLAYER
#define PLAYER

struct Player
{
public:
    Player();
    bool update();

    sf::Vector2f leftHand, rightHand, leftLeg, rightLeg;    
};

#endif
