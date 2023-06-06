#include "Game.h"
int main()
{
    Game game;
    while (game.isOpen()) {
        game.game_body();
        game.draw_everything();
        game.end_game();
    }
    return 0;
}
