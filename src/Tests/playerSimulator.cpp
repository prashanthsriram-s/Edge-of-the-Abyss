#include <math.h>
 #include "../Game.h"
void runGame()
{
    Game& game = Game::getGameInstance();
    game.run();
}