#include "Player.h"
#include "NormalEnemy.h"
#include "SmallEnemy.h"
#include "BigEnemy.h"
#include "Asteroid.h"
#include "Bonus.h"
class Game :public sf::RenderWindow
{
public:
	//ustawia poczatkowe wartosci okna
	Game();
	//rozpoczyna gr�
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
	//usuwa przeciwnika z wektora gdy jest po za plansz� i obs�uguje zderzenie z graczem
	void remove_enemy(Player& player);
	//rysuje odpowiedni� liczb� �y� gracza
	void draw_hp(int hp);
	//obs�uguje zderzenie z pociskiem
	void hit();
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
	std::vector<std::unique_ptr<Ammunition>> ammo;
	sf::Font font;
};