#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#pragma once
class Bonus :public sf::Sprite
{
public:
	void Apply_Bonus();
private:
	int bonus_type;
};