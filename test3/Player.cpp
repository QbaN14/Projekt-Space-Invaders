#include "Player.h"
void Player::add_points(int pts)
{
	points += pts;
}
Player::Player() :AnimatedSprite("Resources\\player.png")
{
	setPosition(348.8,450);
	setScale(0.2, 0.2);
	set_speedy(200);
}
double Player::getspeedx()
{
	return speedx;
}