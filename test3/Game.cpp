#include "Game.h"
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
void Game::add_enemy()
{
    if (timer >= rand()%2+1) {
        timer = 0;
        std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Normal_Enemy>();
        enemies.emplace_back(std::move(enemy));
    }
}
/*void Game::remove_enemy(Normal_Enemy enemy)
{
    //enemies.erase(enemy);
}*/
sf::Time Game::Getelapsed()
{
	return elapsed;
}
void Game::Play()
{
    while (isOpen()) {
        srand(time(NULL));
        timer += Getelapsed().asSeconds();
        Setelapsed(GetClock().restart());
        while (pollEvent(GetEvent())) {
            if (GetEvent().type == sf::Event::Closed)
                close();
        }
        add_enemy();
        player.steering(Getelapsed());
        clear(sf::Color::Black);
        draw(player);
        for (const auto& e : enemies)
        {
            e->animate(Getelapsed());
            draw(*e);
        }
        display();
    }
}
/*void Game::delete_if_pos()
{
    for (auto enemy : enemies)
    {
        if(enemy.getposition())
        {
            remove_enemy(enemy);
        }
    }
}
void Game::check_collisions()
{
    for (auto enemy :enemies)
    {
        if (enemy.)
        {
            player.remove_hp();
        }
    }
}*/