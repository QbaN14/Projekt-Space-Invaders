#pragma once
class Asteroid :public AnimatedSprite
{
public:
	Asteroid();
private:
	double speedy = rand() % 25 + 10;
};