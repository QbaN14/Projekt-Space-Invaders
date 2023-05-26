#pragma once
#include "AnimatedSprite.h"
class Player :public AnimatedSprite
{
public:
	//ustawia bazowe parametry dla gracza
	Player();
	//dodaje okreslona liczbe punktow
	void add_points(int pts);
private:
	int points = 0;
};