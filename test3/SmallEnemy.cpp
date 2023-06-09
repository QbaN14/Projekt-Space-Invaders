#include "SmallEnemy.h"
Small_Enemy::Small_Enemy() :AnimatedSprite("Resources\\smallenemy.png", sf::IntRect(0, 0, 6, 6))
{
	setScale(7, 7);
	set_hp(2);
	set_speedy(120);
	set_points_amount(15);
	add_animation_frame(sf::IntRect(0, 0, 6, 6));
	add_animation_frame(sf::IntRect(0, 7, 6, 6));
	set_ani_fps(2);
	setPosition(rand() % (800 - int(getGlobalBounds().width)), -getGlobalBounds().height);
}