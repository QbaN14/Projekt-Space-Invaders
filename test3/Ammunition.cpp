#include "Ammunition.h"
Ammunition::Ammunition(sf::Vector2f pos, bool is_p, bool is_l, bool is_r)
{
	is_players = is_p;
	if (!texture.loadFromFile("Resources\\ammunition.png")) {
		std::cout << "Could not load texture" << std::endl;
	}
	if (is_players)
	{
		setTextureRect(sf::IntRect(0,0,1,4));
		velocity *= -1;
	}
	else
	{
		setTextureRect(sf::IntRect(9, 0, 1, 4));
	}
	setTexture(texture);
	setPosition(pos);
	setScale(10, 10);
	is_left = is_l;
	is_right = is_r;
}
void Ammunition::animate(sf::Time elapsed)
{
	move(0, velocity * elapsed.asSeconds());
	if (is_left)
	{
		setRotation(45);
		move(-velocity/sqrt(2) * elapsed.asSeconds(),0);
	}
	if (is_right)
	{
		setRotation(-45);
		move(velocity/sqrt(2) * elapsed.asSeconds(), 0);
	}
}
bool Ammunition::get_is_players()
{
	return is_players;
}