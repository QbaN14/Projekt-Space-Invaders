#include "NormalEnemy.h"
Normal_Enemy::Normal_Enemy() :AnimatedSprite("Resources\\normalenemy.png",sf::IntRect(0,0,8,8))
{
	setPosition(rand()%(800-7*8), -7*8);
	setScale(7, 7);
	set_hp(1);
	set_speedy(50);
	set_points_amount(5);
	add_animation_frame(sf::IntRect(0, 0, 8, 8));
	add_animation_frame(sf::IntRect(0, 8, 8, 8));
	set_ani_fps(2);
	set_time_to_shoot(2);
}