#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "NormalEnemy.h"
class Game :public sf::RenderWindow
{
public:
	//ustawia poczatkowe wartosci okna
	Game();
	//rozpoczyna grê
	void Play();
	//zwraca clock
	sf::Clock& GetClock();
	//ustawia elapsed
	void Setelapsed(sf::Time e);
	//zwraca elapsed
	sf::Time Getelapsed();
	//zwraca event
	sf::Event& GetEvent();
private:
	sf::Clock clock;
	sf::Time elapsed;
	sf::Event event;
};