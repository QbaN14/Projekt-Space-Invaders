#include "Game.h"
int main()
{
    Game game(1.25);
    srand(static_cast<unsigned>(time(0)));
    while (game.isOpen()) {
        game.menu();
        game.game_body();
    }
    return 0;
}