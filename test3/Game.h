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
	//usuwa z wektora przeciwnika
	//void remove_enemy(Normal_Enemy enemy);
	//usuwa przeciwnika jesli jest po za plansz¹
	//void delete_if_pos();
	void check_collisions();
private:
	Player player;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Event event;
	double timer;
	std::vector<std::unique_ptr<AnimatedSprite>> enemies;
};