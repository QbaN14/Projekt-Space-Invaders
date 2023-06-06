#include "AnimatedSprite.h"
class Big_Enemy :public AnimatedSprite
{
public:
	//ustawia poczatkowe wartosci
	Big_Enemy();
	//odpowiada za strzelanie
	void shoot(sf::Time &elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
	//odpowiada za ci¹g³¹ animacjê obiektów
	void continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
};