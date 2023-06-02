#include "AnimatedSprite.h"
class Bonus :public AnimatedSprite
{
public:
	void Apply_Bonus();
private:
	int bonus_type;
};