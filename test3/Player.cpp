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
    auto bounds = getGlobalBounds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&bounds.left+bounds.width+getspeedx()*elapsed.asSeconds()<800) {
        move(getspeedx()*elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bounds.left - getspeedx() * elapsed.asSeconds() > 0) {
        move(-getspeedx() * elapsed.asSeconds(), 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && bounds.top-get_speedy() * elapsed.asSeconds() > 0) {
        move(0, -get_speedy() * elapsed.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && bounds.top + bounds.height + get_speedy() * elapsed.asSeconds() < 600) {
        move(0, get_speedy() * elapsed.asSeconds());
    }
}
void AnimatedSprite::post_mortem()
{
    
}