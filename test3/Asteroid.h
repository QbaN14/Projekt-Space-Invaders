#include "AnimatedSprite.h"
class Asteroid :public AnimatedSprite
{
public:
	//ustawia poczatkowe wartosci
	Asteroid();
	//odpowiada za ci�g�� animacj� obiekt�w
	void continous_animation(sf::Time elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
};