#include "Ammunition.h"
Ammunition::Ammunition(sf::Vector2f pos, bool is_player, bool is_l, bool is_r)
{
	if (!texture.loadFromFile("Resources\\ammunition.png")) {
		std::cout << "Could not load texture" << std::endl;
	}
	if (is_player)
	{
		setTextureRect(sf::IntRect(9,0,9,4));
	}
	else
	{
		setTextureRect(sf::IntRect(0, 0, 0, 4));
	}
	setTexture(texture);
	setPosition(pos);
	setScale(10, 10);
	is_left = is_l;
	is_right = is_r;
}
void Ammunition::animate(sf::Time elapsed)
{
	move(0, 100 * elapsed.asSeconds());
	if (is_left)
	{
		move(-100 * elapsed.asSeconds(),0);
	}
	if (is_right)
	{
		move(100 * elapsed.asSeconds(), 0);
	}
}