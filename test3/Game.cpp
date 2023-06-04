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
        int r = rand() % 5+1;
        switch (r)
        {
        case 1:
        case 2:
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Normal_Enemy>();
            enemy->setPosition(rand() % 729 + 1, -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
            break;
        }
        case 3:
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Small_Enemy>();
            enemy->setPosition(rand() % 729 + 1, -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
            break;
        }
        case 4:
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Big_Enemy>();
            enemy->setPosition(rand() % 729 + 1, -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
            break;
        }
        case 5:
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Asteroid>();
            enemy->setPosition(rand() % 729 + 1, -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
            break;
        }
        }
    }
}
void Game::remove_enemy(Player& player)
{
    float player_radius = 7*7/2;
    for (auto it = enemies.begin(); it != enemies.end(); it++)
    {
        sf::Vector2f player_position(player.getPosition().x + player_radius, player.getPosition().y + player_radius);
        auto& e = *it;
        float enemy_radius = e->getGlobalBounds().width/2;
        sf::Vector2f enemy_position(e->getPosition().x+enemy_radius,e->getPosition().y+enemy_radius);
        float distance = std::sqrt(std::pow(enemy_position.x - player_position.x, 2) + std::pow(enemy_position.y - player_position.y, 2));
        if (distance < player_radius + enemy_radius&&!e->get_is_asteroid())
        {
            player.back_to_start(Getelapsed());
            player.remove_hp();
            e->remove_hp();
            if (e->get_hp() == 0)
            {
                player.add_points(e->get_points_amount());
                it = enemies.erase(it);
                --it;
            }
        }
        else if (distance < player_radius + enemy_radius && e->get_is_asteroid())
        {
            player.back_to_start(Getelapsed());
            player.remove_hp();
        }
        else if (e->getGlobalBounds().top > 600)
        {
            it = enemies.erase(it);
            --it;
        }
        else if (e->get_is_asteroid())
        {
            if (e->getGlobalBounds().left + e->getGlobalBounds().width < 0 || e->getGlobalBounds().left>800)
            {
                it = enemies.erase(it);
                --it;
            }
        }
    }
}
sf::Time Game::Getelapsed()
{
	return elapsed;
}
void Game::draw_hp(int hp)
{
    for (int i = 0; i < hp; i++)
    {
        sf::Sprite hpSprite;
        sf::Texture hpTexture;
        if (!hpTexture.loadFromFile("Resources\\life.png")) {
            std::cout << "Could not load texture" << std::endl;
        }
        hpSprite.setTextureRect(sf::IntRect(0, 0, 8, 7));
        hpSprite.setTexture(hpTexture);
        hpSprite.setScale(4, 4);
        hpSprite.setPosition(10 + i * 42, 10);
        draw(hpSprite);
    }
}
void Game::hit()
{
    for (auto it_a = ammo.begin(); it_a != ammo.end(); it_a++)
    {
        auto& a = *it_a;
        if (a->getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            player.back_to_start(Getelapsed());
            player.remove_hp();
            it_a = ammo.erase(it_a);
            it_a--;
        }
        else if (a->getGlobalBounds().top > 600 || a->getGlobalBounds().left<0 ||a->getGlobalBounds().left+a->getGlobalBounds().width>800)
        {
            it_a = ammo.erase(it_a);
            it_a--;
        }
        else
        {
            for (auto it_e = enemies.begin(); it_e != enemies.end(); it_e++)
            {
                auto& e = *it_e;
                if (a->getGlobalBounds().intersects(e->getGlobalBounds()))
                {
                    e->remove_hp();
                    if (e->get_hp() == 0 && !e->get_is_asteroid())
                    {
                        player.add_points(e->get_points_amount());
                        it_e = enemies.erase(it_e);
                        it_e--;
                    }
                    it_a = ammo.erase(it_a);
                    it_a--;
                }
            }
        }
    }
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
        if (player.get_can_move())
        {
            remove_enemy(player);
            player.steering(Getelapsed());
        }
        else
        {
            player.back_to_start(Getelapsed());
        }
        player.step(Getelapsed().asSeconds());
        points.setString("Points: " + std::to_string(player.get_points()));
        clear(sf::Color::Black);
        draw(background);
        draw(player);
        for (const auto& e : enemies)
        {
            e->animate(Getelapsed());
            if (!e->get_cant_animation())
            {
                e->step(Getelapsed().asSeconds());
            }
            draw(*e);
        }
        draw_hp(player.get_hp());
        draw(points);
        display();
    }
}
