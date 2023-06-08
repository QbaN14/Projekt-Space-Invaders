#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Ammunition.h"
#pragma once
class AnimatedSprite :public sf::Sprite
{
public:
	//ustawia odpowiedni¹ teksturê
	AnimatedSprite(std::string path, sf::IntRect rect);
	//odpowiada za poruszanie siê obiektu
	void animate(sf::Time elapsed);
	//odpowiada za usuniêcie 1 ¿ycia
	void remove_hp();
	//ustawia liczbê ¿yæ
	void set_hp(int x);
	//ustawia speedy
	void set_speedy(int x);
	//ustawia speedx
	void set_speedx(int x);
	//zwraca speedy
	double get_speedy();
	//zwraca speedx
	double get_speedx();
	//zwraca wartoœæ liczby punktów przeciwnika
	int get_points_amount();
	//ustawia wartosc liczby punktow przeciwnika
	void set_points_amount(int pts);
	//zwraca ilosc hp
	int get_hp();
	//dodaje klatkê do animacji
	void add_animation_frame(sf::IntRect rect);
	//przywoluje kolejn¹ klatkê animacji
	void step(double time);
	//ustawia liczbe klatek w animacji
	void set_ani_fps(int x);
	//ustawia time_to_shoot
	void set_time_to_shoot(double x);
	//zwraca time_to_shoot
	double get_time_to_shoot();
	//odpowiada za strzelanie
	virtual void shoot(sf::Time& elapsed, std::vector<std::unique_ptr<Ammunition>> &ammo);
	//zwraca couter_to_shoot
	double get_counter_to_shoot();
	//ustawia counter_to_shoot
	void set_counter_to_shoot(double x);
	//odpowiada za ci¹g³¹ animacjê obiektów
	virtual void continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
private:
	double speedy = 0;
	int points_amount = 0;
	int hp=0;
	double time_to_shoot = 0;
	double counter_to_shoot=1.5;
	sf::Texture texture;
	int ani_fps = 0;
	std::vector<sf::IntRect> ani_frames;
	double elapsed_time=0;
	int current_frame = 0;
	bool cant_animation = false;
	int speedx=0;
};