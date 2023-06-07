#include "Asteroid.h"
Asteroid::Asteroid() :AnimatedSprite("Resources\\asteroid.png", sf::IntRect(0, 0, 11, 9))
{
	setScale(8, 8);
	set_speedy(rand()%26+25);
	set_speedx(rand() % 101 - 50);
	setPosition(rand() % (800 - int(getGlobalBounds().width)), -getGlobalBounds().height);
}
void Asteroid::continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    animate(elapsed);
}