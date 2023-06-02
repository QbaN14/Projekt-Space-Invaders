#include "Player.h"
void Player::add_points(int pts)
{
	points += pts;
}
Player::Player() :AnimatedSprite("Resources\\player.png",sf::IntRect(0,0,8,15))
{
    //add_animation_frame(sf::IntRect(0, 0, 8, 15));
    add_animation_frame(sf::IntRect(9, 0, 7, 15));
    add_animation_frame(sf::IntRect(17, 0, 7, 15));
	setPosition(400-28,450);
	setScale(7, 7);
	set_speedy(200);
    set_ani_fps(2);
    set_hp(3);
}
double Player::getspeedx()
{
	return speedx;
}
void Player::steering(sf::Time elapsed)
{
    auto bounds = getGlobalBounds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && bounds.left + bounds.width + getspeedx() * elapsed.asSeconds() < 800) {
        move(getspeedx() * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bounds.left - getspeedx() * elapsed.asSeconds() > 0) {
        move(-getspeedx() * elapsed.asSeconds(), 0);
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
        if (sf::Vector2i(getPosition()) == sf::Vector2i(400 - 28, 450))
        {
            can_move = true;
        }
}
bool Player::get_can_move()
{
    return can_move;
}