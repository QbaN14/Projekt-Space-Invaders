#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
class Bonus :public sf::Sprite
{
public:
	//ustawia poczatkowe wartosci
	Bonus();
	//zwraca typ bonusu
	int get_bonus_type();
private:
	int bonus_type;
	sf::Texture texture;
};