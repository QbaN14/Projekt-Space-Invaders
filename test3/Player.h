#pragma once
#include "AnimatedSprite.h"
class Player :public AnimatedSprite
{
public:
	//ustawia bazowe parametry dla gracza
	Player();
	//dodaje okreslona liczbe punktow
	void add_points(int pts);
	//zwraca speedx
	double getspeedx();
	//sterowanie strza³kami na klawiaturze
	void steering(sf::Time elapsed);
	void check_collision();
private:
	int points = 0;
	double speedx = 200;
};