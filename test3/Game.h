#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class Game :public sf::RenderWindow
{
public:
	//ustawia poczatkowe wartosci okna
	Game();
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