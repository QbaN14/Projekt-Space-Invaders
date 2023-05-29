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
    game.Play();
    return 0;
}
