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
	//ustawia odpowiednie speed
	void set_speedy(int x);
	void set_speedx(int x);
	//zwraca odpowiedni speed
	double get_speedy();
	double get_speedx();
	//zwraca wartoœæ liczby punktów
	int get_points_amount();
	//ustawia wartosc punktow
	void set_points_amount(int pts);
	//zwraca ilosc hp
	int get_hp();
	//dodaje klatkê do animacji
	void add_animation_frame(sf::IntRect rect);
	//przywoluje kolejn¹ klatkê animacji
	void step(double time);
	//ustawia liczbe klatek w animacji
	void set_ani_fps(int x);
	//ustawia wartoœæ cant_animation
	void set_cant_animation(bool x);
	//zwraca cant_animation
	bool get_cant_animation();
	//ustawia is_asteroid
	void set_is_asteroid(bool x);
	//zwraca is_asteroid
	bool get_is_asteroid();
	//ustawia is_small
	void set_is_small(bool x);
	//zwraca is_small
	bool get_is_small();
	//ustawia time_to_shoot
	void set_time_to_shoot(double x);
	//zwraca time_to_shoot
	double get_time_to_shoot();
	//odpowiada za strzelanie
	void shoot(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>> &ammo);
private:
	double speedy = 0;
	int points_amount = 0;
	int hp=0;
	double counter_to_shoot=0;
	double time_to_shoot=0;
	sf::Texture texture;
	int ani_fps = 0;
	std::vector<sf::IntRect> ani_frames;
	double elapsed_time=0;
	int current_frame = 0;
	bool cant_animation = false;
	bool is_asteroid = false;
	bool is_small = false;
	int speedx=0;
};