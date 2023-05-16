#include "headers/GameEngine.h"

int main(void)
{
    GameEngine* newGame = new GameEngine();
    newGame->Gameloop();
    return (0);
}

