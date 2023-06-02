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
	//sterowanie strza³kami na klawiaturze jeœli po ruchu gracz zmieœci siê na ekranie
	void steering(sf::Time elapsed);
private:
	int points = 0;
	double speedx = 200;
};