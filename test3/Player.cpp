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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && getGlobalBounds().left + getGlobalBounds().width + get_speedx() * elapsed.asSeconds() < 800) {
        move(get_speedx() * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && getGlobalBounds().left - get_speedx() * elapsed.asSeconds() > 0) {
        move(-get_speedx() * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && getGlobalBounds().top - get_speedy() * elapsed.asSeconds() > 0) {
        move(0, -get_speedy() * elapsed.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && getGlobalBounds().top + getGlobalBounds().height + get_speedy() * elapsed.asSeconds() < 600+8*7) {
        move(0, get_speedy() * elapsed.asSeconds());
    }
}
int Player::get_points()
{
    return points;
}
void Player::back_to_start(sf::Time elapsed, bool end)
{
    can_move = false;
    bonus_applied = false;
    bonus_timer = 0;
    set_time_to_shoot(1.5);
    set_speedx(150);
    set_speedy(150);
    can_get_hit = true;
        if (getPosition().x < 400 - 28)
        {
            move(get_speedx() * elapsed.asSeconds(), 0);
        }
        else if (getPosition().x > 400 - 28)
        {
            move(-get_speedx() * elapsed.asSeconds(), 0);
        }
        if (getPosition().y < 450)
        {
            move(0, get_speedy() * elapsed.asSeconds());
        }
        else if (getPosition().y > 450)
        {
            move(0, -get_speedy() * elapsed.asSeconds());
        }
        sf::RectangleShape rect(sf::Vector2f(10, 10));
        rect.setPosition(400 - 28-5, 450-5);
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
void Player::remove_bonus(sf::Time elapsed)
{
    if (bonus_applied)
    {
        bonus_timer -= elapsed.asSeconds();
        if (bonus_timer <= 0)
        {
            bonus_timer = 0;
            set_time_to_shoot(1.5);
            set_speedx(150);
            set_speedy(150);
            can_get_hit = true;
            bonus_applied = false;
        }
    }
}
void Player::continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    remove_bonus(elapsed);
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
bool Player::get_can_get_hit()
{
    return can_get_hit;
}
bool Player::apply_bonus(int type, sf::FloatRect bonusrect)
{
    if (getGlobalBounds().intersects(bonusrect) && !bonus_applied)
    {
        bonus_applied = true;
        switch (type)
        {
        case 5:
        {
            if (get_hp() < 3)
            {
                set_hp(get_hp() + 1);
                return true;
            }
        }
        case 3:
        {
            bonus_timer = 10;
            set_time_to_shoot(0.75);
            return true;
        }
        case 4:
        {
            bonus_timer = 10;
            can_get_hit = false;
            return true;
        }
        case 1:
        {
            bonus_timer = 10;
            set_speedx(get_speedx() * 2);
            set_speedy(get_speedy() * 2);
            return true;
        }
        case 2:
        {
            bonus_timer = 10;
            set_speedx(get_speedx() / 2);
            set_speedy(get_speedy() / 2);
            return true;
        }
        }
    }
    return false;
}