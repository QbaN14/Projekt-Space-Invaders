#include "Bonus.h"
Bonus::Bonus()
{
	bonus_type = rand()%5+1;
	if (!texture.loadFromFile("Resources\\bonuses.png")) {
		std::cout << "Could not load texture" << std::endl;
	}
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
	setPosition(rand() % (800 - int(getGlobalBounds().width)), rand() % (600 - int(getGlobalBounds().height)));
}
int Bonus::get_bonus_type()
{
	return bonus_type;
}
bool Bonus::count_time_to_destroy(sf::Time elapsed)
{
	time_to_destroy -= elapsed.asSeconds();
	if (time_to_destroy <= 0)
	{
		return true;
	}
	return false;
}