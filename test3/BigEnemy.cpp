#include "BigEnemy.h"
Big_Enemy::Big_Enemy() :AnimatedSprite("Resources\\bigenemy.png", sf::IntRect(0, 0, 30, 23))
{
	setPosition(rand() % (800 - 105), -23*3.5);
	setScale(3.5, 3.5);
	set_hp(1);
	set_speedy(25);
	set_points_amount(15);
	set_is_big(true);
}