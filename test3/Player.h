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
	//sterowanie strza�kami na klawiaturze je�li po ruchu gracz zmie�ci si� na ekranie
	void steering(sf::Time elapsed);
private:
	int points = 0;
	double speedx = 200;
};