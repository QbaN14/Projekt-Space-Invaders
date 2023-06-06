#include "AnimatedSprite.h"
class Normal_Enemy :public AnimatedSprite
{
public:
	//ustawia poczatkowe wartosci
	Normal_Enemy();
	//odpowiada za strzelanie
	void shoot(sf::Time& elapsed, std::vector<std::unique_ptr<Ammunition>>& ammo);
};