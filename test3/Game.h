#include <fstream>
#include "Player.h"
#include "NormalEnemy.h"
#include "SmallEnemy.h"
#include "BigEnemy.h"
#include "Asteroid.h"
#include "Bonus.h"
class Game :public sf::RenderWindow
{
public:
	//ustawia poczatkowe wartosci okna, jego element�w oraz t�o
	Game(double spawnrate);
	//dodaje losowo utworzonego przeciwnika do wektora
	void add_enemy();
	//usuwa przeciwnika z wektora gdy jest po za plansz� i obs�uguje zderzenie z graczem (metoda okr�g�w)
	void remove_enemy();
	//rysuje odpowiedni� liczb� �y� gracza na ekranie
	void draw_hp(int hp);
	//obs�uguje zderzenia z pociskiem
	void hit();
	//odpowiada za g��wny przebieg gry
	void game_body();
	//odpowiada za pokazanie wszystkiego na ekranie
	void draw_everything();
	//odpowiada za pokazanie ekranu ko�cowego gry oraz nadanie mu odpowiednich warto�ci i interakcj� z nim
	void menu();
	//tworzy obiekty w menu i nadaje im warto�ci
	void set_menu();
	//rysuje obiekty w menu
	void draw_menu();
	//w zale�no�ci od wyniku gracza, zapisuje najwyzszy wynik do pliku/odczytuje go i decyduje o aktualnym highscore
	void highscore();
	//obs�uguje zderzenia z bonusami oraz ich �ycie
	void bonus_haandling();
private:
	sf::Text points;
	sf::Text final_score;
	Player player;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Event event;
	double timer;
	double spawnrate;
	sf::Texture background_texture;
	sf::Sprite background;
	std::vector<std::unique_ptr<AnimatedSprite>> enemies;
	std::vector<std::unique_ptr<Ammunition>> ammo;
	std::vector<std::unique_ptr<Bonus>> bonuses;
	sf::Font font;
	bool ending_screen = false;
	sf::RectangleShape rect_restart;
	sf::RectangleShape rect_end;
	sf::Text restart;
	sf::Text end;
	std::string highest_score="";
	sf::Text menuText;
	sf::Text highscore_text;
	sf::Text name;
};