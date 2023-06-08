#include "Game.h"
Game::Game(double sr)
{
    spawnrate = sr;
	create(sf::VideoMode(800,600), "Space Invaders");
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
    if (timer >= rand()%2+spawnrate) {
        timer = 0;
        int r = rand() % 100+1;
        if (r > 0 && r <= 35)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Normal_Enemy>();
            enemies.emplace_back(std::move(enemy));
        }
        else if (r > 35 && r <= 55)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Small_Enemy>();
            enemies.emplace_back(std::move(enemy));
        }
        else if (r > 55 && r <= 75)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Big_Enemy>();
            enemies.emplace_back(std::move(enemy));
        }
        else if (r > 75 && r <= 85)
        {
            std::unique_ptr<AnimatedSprite> enemy = std::make_unique<Asteroid>();
            enemies.emplace_back(std::move(enemy));
        }
        else if (r > 85 && r <= 100)
        {
            std::unique_ptr<Bonus> bonus = std::make_unique<Bonus>();
            bonuses.emplace_back(std::move(bonus));
        }
    }
}
void Game::remove_enemy()
{
    for (auto it = enemies.begin(); it != enemies.end(); it++)
    {
        auto& e = *it;
        double max_distance = (player.getGlobalBounds().width + e->getGlobalBounds().width) / 2;
        double actual_distance = std::sqrt(std::pow(e->getPosition().x + e->getGlobalBounds().width / 2 - player.getPosition().x - player.getGlobalBounds().width / 2, 2) + std::pow(e->getPosition().y + e->getGlobalBounds().height / 2 - player.getPosition().y - player.getGlobalBounds().height / 2, 2));
        if (actual_distance<=max_distance)
        {
            if (player.get_can_move())
            {
                if (player.get_can_get_hit())
                {
                    player.remove_hp();
                }
                e->remove_hp();
            }
            player.back_to_start(elapsed, enemies);
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
    sf::Texture hpTexture;
    if (!hpTexture.loadFromFile("Resources\\life.png")) {
        std::cout << "Could not load texture" << std::endl;
    }
    for (int i = 0; i < hp; i++)
    {
        sf::Sprite hpSprite;
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
                player.back_to_start(elapsed, enemies);
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
                    continue;
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
    menuText.setOrigin(menuText.getLocalBounds().left + menuText.getLocalBounds().width / 2, menuText.getLocalBounds().top + menuText.getLocalBounds().height / 2);

    highscore_text.setFillColor(sf::Color::White);
    highscore_text.setFont(font);
    highscore_text.setCharacterSize(15);
    highscore_text.setOrigin(highscore_text.getLocalBounds().left + highscore_text.getLocalBounds().width / 2, highscore_text.getLocalBounds().top + highscore_text.getLocalBounds().height / 2);

    name.setFillColor(sf::Color::White);
    name.setPosition(sf::Vector2f(getSize().x / 2, 50));
    name.setFont(font);
    name.setCharacterSize(50);
    name.setString("Space Raiders");
    name.setOrigin(name.getLocalBounds().left + name.getLocalBounds().width / 2, name.getLocalBounds().top + name.getLocalBounds().height / 2);

    rect_restart.setOutlineThickness(1);
    rect_restart.setOutlineColor(sf::Color::White);
    rect_restart.setSize(sf::Vector2f(200, 50));
    rect_restart.setPosition(sf::Vector2f(300, 325));

    rect_end.setOutlineThickness(1);
    rect_end.setOutlineColor(sf::Color::White);
    rect_end.setSize(sf::Vector2f(200, 50));
    rect_end.setPosition(sf::Vector2f(300, 400));

    restart.setFillColor(sf::Color::White);
    restart.setFont(font);
    restart.setCharacterSize(25);
    restart.setString("Play");
    restart.setOrigin(restart.getLocalBounds().left + restart.getLocalBounds().width / 2, restart.getLocalBounds().top + restart.getLocalBounds().height / 2);
    restart.setPosition(sf::Vector2f(getSize().x / 2, 350));

    end.setFillColor(sf::Color::White);
    end.setFont(font);
    end.setCharacterSize(25);
    end.setString("Exit");
    end.setOrigin(end.getLocalBounds().left + end.getLocalBounds().width / 2, end.getLocalBounds().top + end.getLocalBounds().height / 2);
    end.setPosition(sf::Vector2f(getSize().x / 2, 425));

    if (!steeringTexture.loadFromFile("Resources\\steering.png")) {
        std::cout << "Could not load texture" << std::endl;
    }
    steeringSprite.setTextureRect(sf::IntRect(0, 0, 512, 512));
    steeringSprite.setTexture(steeringTexture);
    steeringSprite.setScale(0.25, 0.25);
    steeringSprite.setPosition(200-steeringSprite.getGlobalBounds().width/2-restart.getGlobalBounds().width/2, 350);

    steeringinfo.setFillColor(sf::Color::White);
    steeringinfo.setFont(font);
    steeringinfo.setCharacterSize(18);
    steeringinfo.setString("Move with:");
    steeringinfo.setPosition(200 - steeringinfo.getGlobalBounds().width / 2 - restart.getGlobalBounds().width / 2, 330);
}
void Game::draw_menu()
{
    clear(sf::Color::Black);
    draw(background);
    draw(steeringSprite);
    draw(steeringinfo);
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
        player.back_to_start(elapsed, enemies);
        enemies.clear();
        ammo.clear();
        bonuses.clear();
        player.set_hp(3);
        player.setPosition(sf::Vector2f(400 - 28, 450));
        ending_screen = true;
        set_menu();
        if (player.get_points() >= 0)
        {
            final_score.setString("Last score: " + std::to_string(player.get_points()));
        }
        sf::FloatRect finalScoreRect = final_score.getLocalBounds();
        final_score.setOrigin(finalScoreRect.left + finalScoreRect.width / 2, finalScoreRect.top + finalScoreRect.height / 2);
        final_score.setPosition(sf::Vector2f(getSize().x / 2.0f, 150));
        highscore();
        if (std::stoi(highest_score) != -1)
        {
            highscore_text.setString("Highscore: " + highest_score);
        }
        sf::FloatRect highscoreRect = highscore_text.getLocalBounds();
        highscore_text.setOrigin(highscoreRect.left + highscoreRect.width / 2, highscoreRect.top + highscoreRect.height / 2);
        highscore_text.setPosition(sf::Vector2f(getSize().x / 2, 180));
        while (ending_screen)
        {
            while (pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                {
                    close();
                    return;
                }
            }
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
                    player.set_points(0);
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
void Game::bonus_haandling()
{
    for (auto it_b = bonuses.begin(); it_b != bonuses.end(); it_b++)
    {
        auto& b = *it_b;
        if (player.apply_bonus(b->get_bonus_type(), b->getGlobalBounds()) || b->count_time_to_destroy(elapsed))
        {
            it_b = bonuses.erase(it_b);
            it_b--;
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
    timer += elapsed.asSeconds();
    elapsed = clock.restart();
    while (pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            close();
    }
    add_enemy();
    player.continous_animation(elapsed, ammo, enemies);
    for (const auto& e : enemies)
    {
        e->continous_animation(elapsed, ammo);
    }
    for (const auto& a : ammo)
    {
        a->animate(elapsed);
    }
    bonus_haandling();
    remove_enemy();
    hit();
    points.setString("Points: " + std::to_string(player.get_points()));
    draw_everything();
}