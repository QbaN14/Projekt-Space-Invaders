#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#pragma once
class AnimatedSprite :public sf::Sprite
{
public:
	//odpowiada za wczytanie tekstury i ustawienie pozycji
	AnimatedSprite(std::string path);
	//odpowiada za poruszanie si�
	void animate(sf::Time elapsed);
	//odpowiada za usuni�cie 1 �ycia
	void remove_hp();
	//odpowiada za przywr�cenie 1 �ycia
	void add_hp();
	//ustawia liczb� �y�
	void set_hp(int x);
	void set_speedy(int x);
private:
	double speedy = 0;
	int hp;
	int point_amount;
	double time_to_shoot;
	sf::Texture texture;
};