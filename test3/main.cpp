#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include "Game.h"
#include "AnimatedSprite.h"
#include "NormalEnemy.h"
#include "BigEnemy.h"
#include "SmallEnemy.h"
#include "Asteroid.h"
#include "Player.h"
#include "Bonus.h"
int main()
{
    Game game;
    Player player;
    Normal_Enemy enemy;
    srand(time(NULL));
    // run the program as long as the window is open
    while (game.isOpen()) {
        game.Setelapsed(game.GetClock().restart());
        // check all the window's events that were triggered since the last iteration of the loop
        while (game.pollEvent(game.GetEvent())) {
            // "close requested" event: we close the window
            if (game.GetEvent().type == sf::Event::Closed)
                game.close();
        }
        enemy.animate(game.Getelapsed());
        // clear the window with black color
        game.clear(sf::Color::Black);
        // draw everything here...
        game.draw(player);
        game.draw(enemy);
        // end the current frame
        game.display();
    }
    return 0;
}
