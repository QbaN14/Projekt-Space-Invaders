#include "SmallEnemy.h"
Small_Enemy::Small_Enemy() :AnimatedSprite("Resources\\smallenemy.png", sf::IntRect(0, 0, 6, 6))
{
	setPosition(rand()%(800-7*6), -7 * 6);
	setScale(7, 7);
	set_hp(2);
	set_speedy(100);
	set_points_amount(10);
	add_animation_frame(sf::IntRect(0, 0, 6, 6));
	add_animation_frame(sf::IntRect(0, 7, 6, 6));
	set_ani_fps(2);
	set_is_small(true);
}