#include "game/logic.h"
#include "game/board.h"
#include "game/AI.h"
#include "ui/display.h"
#include "ui/console.h"
#include <cstdlib>
#include <ctime>
using namespace Game2048;
Game::Game game;
int main()
{
    while (game.run())
        ;
    return 0;
}