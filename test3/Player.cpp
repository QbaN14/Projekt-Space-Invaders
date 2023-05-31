#include "Player.h"
void Player::add_points(int pts)
{
	points += pts;
}
Player::Player() :AnimatedSprite("Resources\\player.png",sf::IntRect(0,0,512,538))
{
	setPosition(348.8,450);
	setScale(0.2, 0.2);
	set_speedy(200);
}
double Player::getspeedx()
{
	return speedx;
}
void Player::steering(sf::Time elapsed)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(getspeedx()*elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(-getspeedx() * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move(0, -get_speedy() * elapsed.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        move(0, get_speedy() * elapsed.asSeconds());
    }
}
void Player::check_collision()
{
    //auto e = game.get_enemies();
    //for (auto it = e.begin(); it <= e.end(); it++)
    //{
       //// if()
    //}
}
