#include "BigEnemy.h"
Big_Enemy::Big_Enemy() :AnimatedSprite("Resources\\bigenemy.png", sf::IntRect(0, 0, 30, 23))
{
	setScale(3.5, 3.5);
	set_hp(1);
	set_speedy(25);
	set_points_amount(30);
	set_time_to_shoot(4);
	setPosition(rand() % (800 - int(getGlobalBounds().width)), -getGlobalBounds().height);
}
void Big_Enemy::shoot(sf::Time& elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
    set_counter_to_shoot(get_counter_to_shoot()+ elapsed.asSeconds());
    if (get_counter_to_shoot() >= get_time_to_shoot())
    {
		set_counter_to_shoot(0);
        std::unique_ptr<Ammunition> a = std::make_unique<Ammunition>(sf::Vector2f(getGlobalBounds().left + getGlobalBounds().width / 2, getGlobalBounds().top + getGlobalBounds().height));
		ammo.emplace_back(std::move(a));
		std::unique_ptr<Ammunition> b = std::make_unique<Ammunition>(sf::Vector2f(getGlobalBounds().left - 2 * getScale().x , getGlobalBounds().top + getGlobalBounds().height - 4 * getScale().y), false, true, false);
		ammo.emplace_back(std::move(b));
		std::unique_ptr<Ammunition> c = std::make_unique<Ammunition>(sf::Vector2f(getGlobalBounds().left+getGlobalBounds().width+2*getScale().x, getGlobalBounds().top+getGlobalBounds().height-4*getScale().y),false,false,true);
		ammo.emplace_back(std::move(c));
    }
}
void Big_Enemy::continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo)
{
	animate(elapsed);
	shoot(elapsed, ammo);
}