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
	//zwraca liczbe zdobytych punktow
	int get_points();
	//ustawia liczbe zdobytych punktow
	void set_points(int x);
	//wraca na start
	void back_to_start(sf::Time elapsed);
	//sprawdza czy gracz moze sie ruszac
	bool get_can_move();
private:
	bool can_move = true;
	int points = 0;
	double speedx = 200;
};