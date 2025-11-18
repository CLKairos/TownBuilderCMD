#include <cstdlib>
#include <ctime>
#include "save.h"
#include "game.h"

//Loads game, starts game loop, and then saves the game.
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    loadGame();
    gameLoop();
    saveGame();
    return 0;
}
