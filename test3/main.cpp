#include "Game.h"
int main()
{
    Game game;
    while (game.isOpen()) {
        game.menu();
        game.game_body();
        game.draw_everything();
        game.menu();
    }
    return 0;
}