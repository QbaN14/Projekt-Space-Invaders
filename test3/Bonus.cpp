#include "Bonus.h"
Bonus::Bonus()
{
	srand(time(NULL));
	bonus_type = rand()%5+1;
	if (!texture.loadFromFile("Resources\\bonuses.png")) {
		std::cout << "Could not load texture" << std::endl;
	}
	setPosition(rand() % (800 -40 ), rand()%(600-40));
	setScale(5, 5);
	if (bonus_type == 1)
	{
		setTextureRect(sf::IntRect(0, 0, 8, 8));
		setTexture(texture);
	}
	else if (bonus_type == 2)
	{
		setTextureRect(sf::IntRect(0, 0, 8, 8));
		setTexture(texture);
	}
	else if (bonus_type == 3)
	{
		setTextureRect(sf::IntRect(0, 8, 8, 8));
		setTexture(texture);
	}
	else if (bonus_type == 4)
	{
		setTextureRect(sf::IntRect(0, 16, 8, 8));
		setTexture(texture);
	}
	else if (bonus_type == 5)
	{
		setTextureRect(sf::IntRect(8, 16, 8, 8));
		setTexture(texture);
	}
}
int Bonus::get_bonus_type()
{
	return bonus_type;
}