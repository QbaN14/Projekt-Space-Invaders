#include "NormalEnemy.h"
Normal_Enemy::Normal_Enemy() :AnimatedSprite("Resources\\normalenemy.png",sf::IntRect(0,0,348,324))
{
	setPosition(rand()%729+1, -64.8);
	setScale(0.2, 0.2);
	set_hp(1);
	set_speedy(50);
}