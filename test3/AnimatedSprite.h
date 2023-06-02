#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#pragma once
class AnimatedSprite :public sf::Sprite
{
public:
	//odpowiada za wczytanie tekstury i ustawienie pozycji
	AnimatedSprite(std::string path, sf::IntRect rect);
	//odpowiada za poruszanie siê
	void animate(sf::Time elapsed);
	//odpowiada za usuniêcie 1 ¿ycia
	void remove_hp();
	//odpowiada za przywrócenie 1 ¿ycia
	void add_hp();
	//ustawia liczbê ¿yæ
	void set_hp(int x);
	//ustawia speedy
	void set_speedy(int x);
	//zwraca speedy
	double get_speedy();
	//sprawdza czy tekstura miesci sie na ekranie w x
	bool check_x();
	//sprawdza czy tekstura miesci sie na ekranie w y
	bool check_y();
	virtual void post_mortem();
private:
	double speedy = 0;
	int hp;
	int point_amount;
	double time_to_shoot;
	sf::Texture texture;
};