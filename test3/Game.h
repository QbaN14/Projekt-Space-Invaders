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
	//dodaje do wektora przeciwnika
	void add_enemy();
	//usuwa przeciwnika z wektora gdy jest po za plansz¹ i obs³uguje zderzenie z graczem
	void remove_enemy();
	//rysuje odpowiedni¹ liczbê ¿yæ gracza
	void draw_hp(int hp);
	//obs³uguje zderzenie z pociskiem
	void hit();
	//odpowiada za g³ówny przebieg gry
	void game_body();
	//odpowiada za pokazanie wszystkiego na ekranie
	void draw_everything();
	//odpowiada za pokazanie ekranu koñcowego gry
	void end_game();
private:
	sf::Text points;
	sf::Text final_score;
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
	bool ending_screen = false;
};