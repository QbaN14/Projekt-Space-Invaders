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
	//odlicza czas do znikniêcia bonusu
	bool count_time_to_destroy(sf::Time elapsed);
private:
	int bonus_type;
	sf::Texture texture;
	double time_to_destroy=20;
};