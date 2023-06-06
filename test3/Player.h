#include "AnimatedSprite.h"
class Player :public AnimatedSprite
{
public:
	//ustawia bazowe parametry dla gracza
	Player();
	//dodaje okreslona liczbe punktow
	void add_points(int pts);
	//sterowanie strza³kami na klawiaturze jeœli po ruchu gracz zmieœci siê na ekranie
	void steering(sf::Time elapsed);
	//zwraca liczbe zdobytych punktow
	int get_points();
	//obiekt wraca na start
	void back_to_start(sf::Time elapsed);
	//odpowiada za strzelanie
	void shoot(sf::Time& elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
	//odpowiada za ci¹g³¹ animacjê obiektu
	void continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
	//ustawia wynik punktowy
	void set_points(int x);
	//zwraca can_move
	bool get_can_move();
private:
	bool can_move = true;
	int points = 0;
};