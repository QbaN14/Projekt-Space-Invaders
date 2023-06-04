#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
 #include <iostream>
class Ammunition :public sf::Sprite
{
public:
	Ammunition(sf::Vector2f pos, bool is_player=false, bool is_l = false, bool is_r = false);
	void animate(sf::Time elapsed);
private:
	bool is_right = false;
	bool is_left = false;
	sf::Texture texture;
};