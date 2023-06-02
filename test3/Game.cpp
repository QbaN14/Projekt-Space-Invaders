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
        int r = rand() % 2+1;
        if (r == 1)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Normal_Enemy>();
            enemy->setPosition(rand() % 729 + 1, -64.8);
            enemies.emplace_back(std::move(enemy));
        }
        else if (r == 2)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Small_Enemy>();
            enemy->setPosition(rand() % 729 + 1, -64.8);
            enemy->set_hp(2);
            enemies.emplace_back(std::move(enemy));
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
        if (distance < player_radius + enemy_radius)
        {
            player.back_to_start(Getelapsed());
            player.remove_hp();
            e->remove_hp();
            if (e->get_hp() == 0)
            {
                player.add_points(e->get_points_amount());
                it = enemies.erase(it);
            }
        }
        else if (e->getGlobalBounds().top > 600)
        {
            it = enemies.erase(it);
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
            e->step(Getelapsed().asSeconds());
            draw(*e);
        }
        draw_hp(player.get_hp());
        draw(points);
        display();
    }
}
