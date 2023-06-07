#include "NormalEnemy.h"
Normal_Enemy::Normal_Enemy() :AnimatedSprite("Resources\\normalenemy.png",sf::IntRect(0,0,8,8))
{
	setPosition(rand()%(800-7*8), -7*8);
	setScale(7, 7);
	set_hp(1);
	set_speedy(60);
	set_points_amount(10);
	add_animation_frame(sf::IntRect(0, 0, 8, 8));
	add_animation_frame(sf::IntRect(0, 8, 8, 8));
	set_ani_fps(2);
	set_time_to_shoot(2);
}
void Normal_Enemy::shoot(sf::Time& elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    set_counter_to_shoot(get_counter_to_shoot() + elapsed.asSeconds());
    if (get_counter_to_shoot() >= get_time_to_shoot())
    {
        set_counter_to_shoot(0);
        std::unique_ptr<Ammunition> a = std::make_unique<Ammunition>(sf::Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2, getGlobalBounds().top + getGlobalBounds().height));
        ammo.emplace_back(std::move(a));
    }
}