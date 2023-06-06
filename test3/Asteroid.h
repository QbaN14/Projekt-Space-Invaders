#include "AnimatedSprite.h"
class Asteroid :public AnimatedSprite
{
public:
	//ustawia poczatkowe wartosci
	Asteroid();
	//odpowiada za ci¹g³¹ animacjê obiektów
	void continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
};