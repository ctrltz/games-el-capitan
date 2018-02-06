#include <SFML/Graphics.hpp>

#include "player.h"
#include "goal.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    int current_goal = 0, goals_number = 5;
    Player player;
    Goal ** path = new (Goal *)[goals_number];
    // Create goals or load from file.

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        player.update();
        if (path[current_goal]->hit(player))
        {
            path[current_goal].setStyle();
            current_goal++;
            if (current_goal == goals_number)
            {
                // Game over!
            }   
        }
        // Update timer.

        window.clear();
        window.draw(goal.shape);
        window.display();
    }

    return 0;
}
