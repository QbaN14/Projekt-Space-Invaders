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
void Game::add_enemy()
{
    if (timer >= rand()%2+1.5) {
        timer = 0;
        int r = rand() % 5+1;
        switch (r)
        {
        case 1:
        case 2:
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Normal_Enemy>();
            enemy->setPosition(rand() % (800-int(enemy->getGlobalBounds().width)) + 1, -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
            break;
        }
        case 3:
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Small_Enemy>();
            enemy->setPosition(rand() % (800 - int(enemy->getGlobalBounds().width)) + 1, -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
            break;
        }
        case 4:
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Big_Enemy>();
            enemy->setPosition(rand() % (800 - int(enemy->getGlobalBounds().width)) + 1, -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
            break;
        }
        case 5:
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Asteroid>();
            enemy->setPosition(rand() % (800 - int(enemy->getGlobalBounds().width)) + 1, -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
            break;
        }
        }
    }
}
void Game::remove_enemy()
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
            if (player.get_can_move())
            {
                player.remove_hp();
                e->remove_hp();
            }
            player.back_to_start(elapsed);
            if (e->get_hp() == 0)
            {
                player.add_points(e->get_points_amount());
                it = enemies.erase(it);
                --it;
            }
        }
        else if (e->getGlobalBounds().top > 600)
        {
            it = enemies.erase(it);
            --it;
        }
        else if (e->getGlobalBounds().left + e->getGlobalBounds().width < 0 || e->getGlobalBounds().left>800)
        {
            it = enemies.erase(it);
            --it;
        }
    }
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
            if (player.get_can_move())
            {
                player.remove_hp();
            }
            player.back_to_start(elapsed);
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
                    if (player.get_can_move())
                    {
                        e->remove_hp();
                    }
                    if (e->get_hp() == 0)
                    {
                        if (a->get_is_players())
                        {
                            player.add_points(e->get_points_amount());
                        }
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
void Game::end_game()
{
    if (player.get_hp() == 0)
    {
        ending_screen = true;
        while (ending_screen)
        {
            clear(sf::Color::Black);
            draw(background);
            while (pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    close();
            }

            final_score.setFillColor(sf::Color::White);
            final_score.setPosition(100, 100);
            final_score.setFont(font);
            final_score.setCharacterSize(25);
            final_score.setString("Final score: " + std::to_string(player.get_points()));
            sf::FloatRect textRect = final_score.getLocalBounds();
            final_score.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            final_score.setPosition(sf::Vector2f(400, 200));
            draw(final_score);

            rect_restart.setOutlineThickness(1);
            rect_end.setOutlineThickness(1);
            rect_restart.setOutlineColor(sf::Color::White);
            rect_end.setOutlineColor(sf::Color::White);
            rect_restart.setSize(sf::Vector2f(200, 50));
            rect_end.setSize(sf::Vector2f(200, 50));
            rect_restart.setPosition(300, 300);
            rect_end.setPosition(300, 400);
            rect_restart.setFillColor(sf::Color::Transparent);
            rect_end.setFillColor(sf::Color::Transparent);
            draw(rect_restart);
            draw(rect_end);

            restart.setFillColor(sf::Color::White);
            restart.setPosition(300, 300);
            restart.setFont(font);
            restart.setCharacterSize(25);
            restart.setString("Play");
            sf::FloatRect restartRect = restart.getLocalBounds();
            restart.setOrigin(restartRect.left + restartRect.width / 2.0f, restartRect.top + restartRect.height / 2.0f);
            restart.setPosition(sf::Vector2f(400, 325));
            draw(restart);

            end.setFillColor(sf::Color::White);
            end.setPosition(300, 400);
            end.setFont(font);
            end.setCharacterSize(25);
            end.setString("Exit");
            sf::FloatRect endRect = end.getLocalBounds();
            end.setOrigin(endRect.left + endRect.width / 2.0f, endRect.top + endRect.height / 2.0f);
            end.setPosition(sf::Vector2f(400, 425));
            draw(end);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rect_restart.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this))))
            {
                enemies.clear();
                ammo.clear();
                player.set_hp(3);
                player.set_points(0);
                player.setPosition(sf::Vector2f(400 - 28, 450));
                ending_screen = false;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rect_end.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this))))
            {
                close();
            }

            display();
        }
    }
}
void Game::draw_everything()
{
    clear(sf::Color::Black);
    draw(background);
    draw(player);
    for (const auto& e : enemies)
    {
        draw(*e);
    }
    for (const auto& a : ammo)
    {
        draw(*a);
    }
    draw_hp(player.get_hp());
    draw(points);
    display();
}
void Game::game_body()
{
    srand(time(NULL));
    timer += elapsed.asSeconds();
    elapsed = clock.restart();
    while (pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            close();
    }
    add_enemy();
    player.continous_animation(elapsed, ammo);
    remove_enemy();
    hit();
    for (const auto& e : enemies)
    {
        e->continous_animation(elapsed, ammo);
    }
    points.setString("Points: " + std::to_string(player.get_points()));
    for (const auto& a : ammo)
    {
        a->animate(elapsed);
    }
}
