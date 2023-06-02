#include "Player.h"
#include "NormalEnemy.h"
class Game :public sf::RenderWindow
{
public:
	//ustawia poczatkowe wartosci okna
	Game();
	//rozpoczyna grê
	void Play();
	//zwraca clock
	sf::Clock& GetClock();
	//ustawia elapsed
	void Setelapsed(sf::Time e);
	//zwraca elapsed
	sf::Time Getelapsed();
	//zwraca event
	sf::Event& GetEvent();
	//dodaje do wektora przeciwnika
	void add_enemy();
	//usuwa przeciwnika z wektora gdy jest po za plansz¹ i obs³uguje zderzenie z graczem
	void remove_enemy(Player& player);
private:
	sf::Text points;
	Player player;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Event event;
	double timer;
	sf::Texture background_texture;
	sf::Sprite background;
	std::vector<std::unique_ptr<AnimatedSprite>> enemies;
	sf::Font font;
};