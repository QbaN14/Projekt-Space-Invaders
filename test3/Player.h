#include "AnimatedSprite.h"
class Player :public AnimatedSprite
{
public:
	//ustawia bazowe parametry dla gracza, dodaje klatki animacji
	Player();
	//dodaje okreslona liczbe zdobytych punktow
	void add_points(int pts);
	//sterowanie strza�kami na klawiaturze je�li po ruchu gracz zmie�ci si� na ekranie
	void steering(sf::Time elapsed);
	//zwraca liczbe zdobytych punktow
	int get_points();
	//obiekt wraca na start, nie mo�e wtedy straci� �ycia, usuwa przeciwnik�w kt�rzy s� blisko miejsca odrodzenia
	void back_to_start(sf::Time elapsed, std::vector<std::unique_ptr<AnimatedSprite>>& enemies);
	//odpowiada za strzelanie
	void shoot(sf::Time& elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
	//odpowiada za ci�g�� animacj� obiektu
	void continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo, std::vector<std::unique_ptr<AnimatedSprite>> &enemies);
	//ustawia wynik punktowy gracza
	void set_points(int x);
	//sprawdza czy mo�e si� porusza�
	bool get_can_move();
	//nadaje bonus po wleceniu w niego: 1 +1hp, 2 2x szybsze strzelanie, 3 niesmiertelny, 4 2x v, 5 1/2v
	bool apply_bonus(int type, sf::FloatRect bonusrect);
	//sprawdza czy gracz mo�e straci� �ycie
	bool get_can_get_hit();
	//odpowiada za usuniecie bonusu po odpowiednim czasie
	void remove_bonus(sf::Time elapsed);
private:
	double bonus_timer = 0;
	bool can_move = true;
	bool can_get_hit = true;
	bool bonus_applied = false;
	int points = -1;
};