#include "Player.h"
void Player::add_points(int pts)
{
	points += pts;
}
Player::Player() :AnimatedSprite("Resources\\player.png",sf::IntRect(0,0,8,15))
{
    add_animation_frame(sf::IntRect(9, 0, 7, 15));
    add_animation_frame(sf::IntRect(17, 0, 7, 15));
	setPosition(400-28,450);
	setScale(7, 7);
	set_speedy(150);
    set_speedx(150);
    set_ani_fps(2);
    set_time_to_shoot(1.5);
}
void Player::steering(sf::Time elapsed)
{
    auto bounds = getGlobalBounds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && bounds.left + bounds.width + get_speedx() * elapsed.asSeconds() < 800) {
        move(get_speedx() * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bounds.left - get_speedx() * elapsed.asSeconds() > 0) {
        move(-get_speedx() * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && bounds.top - get_speedy() * elapsed.asSeconds() > 0) {
        move(0, -get_speedy() * elapsed.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && bounds.top + bounds.height + get_speedy() * elapsed.asSeconds() < 600+8*7) {
        move(0, get_speedy() * elapsed.asSeconds());
    }
}
int Player::get_points()
{
    return points;
}
void Player::back_to_start(sf::Time elapsed)
{
    can_move = false;
        if (getPosition().x < 400 - 28)
        {
            move(100 * elapsed.asSeconds(), 0);
        }
        else if (getPosition().x > 400 - 28)
        {
            move(-100 * elapsed.asSeconds(), 0);
        }
        if (getPosition().y < 450)
        {
            move(0, 100 * elapsed.asSeconds());
        }
        else if (getPosition().y > 450)
        {
            move(0, -100 * elapsed.asSeconds());
        }
        sf::RectangleShape rect(sf::Vector2f(5, 5));
        rect.setPosition(400 - 28, 450);
        if (rect.getGlobalBounds().contains(getPosition()))
        {
            can_move = true;
        }
}
void Player::set_points(int x)
{
    points = x;
}
void Player::shoot(sf::Time& elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    set_counter_to_shoot(get_counter_to_shoot() + elapsed.asSeconds());
    if (get_counter_to_shoot() >= get_time_to_shoot())
    {
        set_counter_to_shoot(0);
        std::unique_ptr<Ammunition> a = std::make_unique<Ammunition>(sf::Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2, getGlobalBounds().top-90),true);
        ammo.emplace_back(std::move(a));
    }
}
void Player::continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    if (can_move)
    {
        steering(elapsed);
        shoot(elapsed, ammo);
        step(elapsed.asSeconds());
    }
    else
    {
        back_to_start(elapsed);
    }
}
bool Player::get_can_move()
{
    return can_move;
}