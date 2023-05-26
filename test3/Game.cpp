#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
Game::Game()
{
	sf::Vector2u windowSize(800, 600);
	create(sf::VideoMode(windowSize.x, windowSize.y), "Space Invaders");
	setFramerateLimit(120);
}
sf::Clock& Game::GetClock()
{
	return clock;
}
void Game::Setelapsed(sf::Time e)
{
	elapsed = e;
}
sf::Event& Game::GetEvent()
{
	return event;
}
sf::Time Game::Getelapsed()
{
	return elapsed;
}