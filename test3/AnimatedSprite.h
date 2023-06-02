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
	//sprawdza kolizje z innymi obiektami
	void check_collisions();
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
private:
	double speedy = 0;
	int points_amount = 0;
	int hp;
	double time_to_shoot;
	sf::Texture texture;
	int ani_fps = 0;
	std::vector<sf::IntRect> ani_frames;
	double elapsed_time=0;
	int current_frame = 0;
};