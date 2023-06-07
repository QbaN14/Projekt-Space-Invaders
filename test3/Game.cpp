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
    if (timer >= rand()%2+1.25) {
        timer = 0;
        int r = rand() % 100+1;
        if (r > 0 && r <= 35)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Normal_Enemy>();
            enemy->setPosition(rand() % (800 - int(enemy->getGlobalBounds().width)), -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
        }
        else if (r > 35 && r <= 55)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Small_Enemy>();
            enemy->setPosition(rand() % (800 - int(enemy->getGlobalBounds().width)), -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
        }
        else if (r > 55 && r <= 75)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Big_Enemy>();
            enemy->setPosition(rand() % (800 - int(enemy->getGlobalBounds().width)), -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
        }
        else if (r > 75 && r <= 85)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Asteroid>();
            enemy->setPosition(rand() % (800 - int(enemy->getGlobalBounds().width)), -enemy->getGlobalBounds().height);
            enemies.emplace_back(std::move(enemy));
        }
        else if (r > 85 && r <= 100)
        {
            std::unique_ptr<Bonus> bonus = std::make_unique<Bonus>();
            bonus->setPosition(rand() % (800 - int(bonus->getGlobalBounds().width)), rand()%(600-int(bonus->getGlobalBounds().height)));
            bonuses.emplace_back(std::move(bonus));
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
                if (player.get_can_get_hit())
                {
                    player.remove_hp();
                }
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
        hpSprite.setScale(6, 6);
        hpSprite.setPosition(10 + i * 58, 10);
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
            if (player.get_can_get_hit())
            {
                if (player.get_can_move())
                {
                    player.remove_hp();
                }
                player.back_to_start(elapsed);
            }
            it_a = ammo.erase(it_a);
            it_a--;
            continue;
        }
        else if (a->getGlobalBounds().top > 600 || a->getGlobalBounds().left<0 ||a->getGlobalBounds().left+a->getGlobalBounds().width>800)
        {
            it_a = ammo.erase(it_a);
            it_a--;
            continue;
        }
        else
        {
            for (auto it_e = enemies.begin(); it_e != enemies.end(); it_e++)
            {
                auto& e = *it_e;
                if (a->getGlobalBounds().intersects(e->getGlobalBounds()))
                {
                    e->remove_hp();
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
void Game::highscore()
{
    std::ifstream file_read("Resources\\highscore.txt");
    if (file_read) {
        if (std::getline(file_read, highest_score))
        {
            if (std::stoi(highest_score) < player.get_points())
            {
                highest_score = std::to_string(player.get_points());
                std::ofstream file_write("Resources\\highscore.txt", std::ios::trunc);
                file_write << highest_score;
                file_write.close();
            }
        }
        file_read.close();
    }
    else 
    {
        std::ofstream file_write("Resources\\highscore.txt", std::ios::trunc);
        if (file_write)
        {
            highest_score = std::to_string(player.get_points());
            file_write << player.get_points();
            file_write.close();
        }
        else
        {
            std::cout << "Can't create highscore.txt!" << std::endl;
        }
    }
}
void Game::set_menu()
{
    final_score.setFillColor(sf::Color::White);
    final_score.setFont(font);
    final_score.setCharacterSize(25);

    menuText.setFillColor(sf::Color::White);
    menuText.setPosition(sf::Vector2f(getSize().x / 2, 275));
    menuText.setFont(font);
    menuText.setCharacterSize(40);
    menuText.setString("MENU");
    sf::FloatRect menuRect = menuText.getLocalBounds();
    menuText.setOrigin(menuRect.left + menuRect.width / 2, menuRect.top + menuRect.height / 2);

    highscore_text.setFillColor(sf::Color::White);
    highscore_text.setFont(font);
    highscore_text.setCharacterSize(15);
    sf::FloatRect highscoreRect = highscore_text.getLocalBounds();
    highscore_text.setOrigin(highscoreRect.left + highscoreRect.width / 2, highscoreRect.top + highscoreRect.height / 2);

    name.setFillColor(sf::Color::White);
    name.setPosition(sf::Vector2f(getSize().x / 2, 50));
    name.setFont(font);
    name.setCharacterSize(50);
    name.setString("Space Raiders");
    sf::FloatRect nameRect = name.getLocalBounds();
    name.setOrigin(nameRect.left + nameRect.width / 2, nameRect.top + nameRect.height / 2);

    rect_restart.setOutlineThickness(1);
    rect_end.setOutlineThickness(1);
    rect_restart.setOutlineColor(sf::Color::White);
    rect_end.setOutlineColor(sf::Color::White);
    rect_restart.setSize(sf::Vector2f(200, 50));
    rect_end.setSize(sf::Vector2f(200, 50));
    rect_restart.setPosition(sf::Vector2f(300, 325));
    rect_end.setPosition(sf::Vector2f(300, 400));

    restart.setFillColor(sf::Color::White);
    restart.setFont(font);
    restart.setCharacterSize(25);
    restart.setString("Play");
    sf::FloatRect restartRect = restart.getLocalBounds();
    restart.setOrigin(restartRect.left + restartRect.width / 2, restartRect.top + restartRect.height / 2);
    restart.setPosition(sf::Vector2f(getSize().x / 2, 350));

    end.setFillColor(sf::Color::White);
    end.setFont(font);
    end.setCharacterSize(25);
    end.setString("Exit");
    sf::FloatRect endRect = end.getLocalBounds();
    end.setOrigin(endRect.left + endRect.width / 2, endRect.top + endRect.height / 2);
    end.setPosition(sf::Vector2f(getSize().x / 2, 425));
}
void Game::draw_menu()
{
    draw(final_score);
    draw(menuText);
    draw(highscore_text);
    draw(name);
    draw(rect_restart);
    draw(rect_end);
    draw(restart);
    draw(end);
}
void Game::menu()
{
    if (player.get_hp() == 0)
    {
        player.back_to_start(elapsed, true);
        ending_screen = true;
        set_menu();
        while (ending_screen)
        {
            clear(sf::Color::Black);
            draw(background);
            while (pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                {
                    close();
                    return;
                }
            }
            highscore();
            if (player.get_points() >= 0)
            {
                final_score.setString("Last score: " + std::to_string(player.get_points()));
            }
            sf::FloatRect finalScoreRect = final_score.getLocalBounds();
            final_score.setOrigin(finalScoreRect.left + finalScoreRect.width / 2, finalScoreRect.top + finalScoreRect.height / 2);
            final_score.setPosition(sf::Vector2f(getSize().x / 2.0f, 150));
            if (std::stoi(highest_score) != -1)
            {
                highscore_text.setString("Highscore: " + highest_score);
            }
            sf::FloatRect highscoreRect = highscore_text.getLocalBounds();
            highscore_text.setOrigin(highscoreRect.left + highscoreRect.width / 2, highscoreRect.top + highscoreRect.height / 2);
            highscore_text.setPosition(sf::Vector2f(getSize().x / 2, 180));
            rect_restart.setFillColor(sf::Color::Transparent);
            rect_end.setFillColor(sf::Color::Transparent);
            draw_menu();
            if (rect_restart.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this))))
            {
                rect_restart.setFillColor(sf::Color::Color(64, 64, 64));
                draw(rect_restart);
                draw(restart);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    enemies.clear();
                    ammo.clear();
                    bonuses.clear();
                    player.set_hp(3);
                    player.set_points(0);
                    player.setPosition(sf::Vector2f(400 - 28, 450));
                    ending_screen = false;
                }
            }
            else if (rect_end.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this))))
            {
                rect_end.setFillColor(sf::Color::Color(64, 64, 64));
                draw(rect_end);
                draw(end);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    close();
                    return;
                }
            }
            display();
        }
    }
}
void Game::draw_everything()
{
    clear(sf::Color::Black);
    draw(background);
    for (const auto& b : bonuses)
    {
        draw(*b);
    }
    for (const auto& e : enemies)
    {
        draw(*e);
    }
    for (const auto& a : ammo)
    {
        draw(*a);
    }
    draw(player);
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
    for (auto it_b = bonuses.begin(); it_b != bonuses.end(); it_b++)
    {
        auto& b = *it_b;
        if (player.apply_bonus(b->get_bonus_type(), b->getGlobalBounds()))
        {
            it_b = bonuses.erase(it_b);
            it_b--;
        }
    }
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
