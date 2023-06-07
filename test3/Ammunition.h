#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
 #include <iostream>
class Ammunition :public sf::Sprite
{
public:
	//nadaje bazowe wartoœci
	Ammunition(sf::Vector2f pos, bool is_player=false, bool is_l = false, bool is_r = false);
	//odpowiada za poruszanie sie
	void animate(sf::Time elapsed);
	//zwraca is_player
	bool get_is_players();
private:
	bool is_right = false;
	bool is_left = false;
	sf::Texture texture;
	bool is_players = false;
	int velocity = 250;
};