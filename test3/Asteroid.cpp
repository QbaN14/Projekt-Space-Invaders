#include "Asteroid.h"
Asteroid::Asteroid() :AnimatedSprite("Resources\\asteroid.png", sf::IntRect(0, 0, 11, 9))
{
	setPosition(rand() % (800 - 44*2), -2*36);
	setScale(8, 8);
	set_speedy(rand()%26+25);
	set_speedx(rand() % 101 - 50);
}
void Asteroid::continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    animate(elapsed);
}