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
void Game::Play()
{
	Player player;
	Normal_Enemy enemy;
	srand(time(NULL));
    while (isOpen()) {
        Setelapsed(GetClock().restart());
        while (pollEvent(GetEvent())) {
            if (GetEvent().type == sf::Event::Closed)
                close();
            if (GetEvent().type == sf::Event::KeyPressed) {
                if (GetEvent().key.code == sf::Keyboard::Down) {
                    player.animate(Getelapsed());
                }
                if (GetEvent().key.code == sf::Keyboard::Up) {
                    player.move(0, -player.get_speedy() * Getelapsed().asSeconds());
                }
                if (GetEvent().key.code == sf::Keyboard::Left) {
                    player.move(-player.getspeedx() * Getelapsed().asSeconds(), 0);
                }
                if (GetEvent().key.code == sf::Keyboard::Right) {
                    player.move(player.getspeedx() * Getelapsed().asSeconds(), 0);
                }
            }
        }
        enemy.animate(Getelapsed());

        clear(sf::Color::Black);

        draw(player);
        draw(enemy);

        display();
    }
}