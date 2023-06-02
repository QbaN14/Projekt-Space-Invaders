#include "Game.h"
Game::Game()
{
	sf::Vector2u windowSize(800, 600);
	create(sf::VideoMode(windowSize.x, windowSize.y), "Space Invaders");
	setFramerateLimit(120);
    if (!background_texture.loadFromFile("Resources\\background.png")) {
        std::cout << "Could not load background texture" << std::endl;
    }
    background_texture.setRepeated(true);
    background.setTextureRect(sf::IntRect(0,0,800,600));
    background.setTexture(background_texture);
    points.setFillColor(sf::Color::White);
    points.setPosition(475, 10);
    if (!font.loadFromFile("Resources\\PressStart2P-Regular.ttf")) {
        std::cout << "Failed to load font" << std::endl;
    }
    points.setFont(font);
    points.setCharacterSize(25);
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
    if (timer >= rand()%2+2) {
        timer = 0;
        std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Normal_Enemy>();
        enemy->setPosition(rand() % 729 + 1, -64.8);
        enemies.emplace_back(std::move(enemy));
    }
}
void Game::remove_enemy(Player& player)
{
    float player_radius = 21;
    float enemy_radius = 34.8;
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        sf::Vector2f player_position(player.getPosition().x + 24.5, player.getPosition().y + 24.5);
        auto& e = *it;
        sf::Vector2f enemy_position(e->getPosition().x+174*0.2,e->getPosition().y+162*0.2);
        float distance = std::sqrt(std::pow(enemy_position.x - player_position.x, 2) + std::pow(enemy_position.y - player_position.y, 2));
        if (distance < player_radius + enemy_radius)
        {
            player.remove_hp();
            player.add_points(e->get_points_amount());
            e->remove_hp();
            if (e->get_hp() == 0)
            {
                it = enemies.erase(it);
            }
        }
        else if (e->getGlobalBounds().top > 600)
        {
            it = enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
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
        remove_enemy(player);
        player.steering(Getelapsed());
        player.step(Getelapsed().asSeconds());
        points.setString("Points: "+std::to_string(player.get_points()));
        clear(sf::Color::Black);
        draw(background);
        draw(player);
        for (const auto& e : enemies)
        {
            e->animate(Getelapsed());
            draw(*e);
        }
        draw(points);
        display();
    }
}