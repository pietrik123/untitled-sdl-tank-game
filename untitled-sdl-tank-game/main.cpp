#include "Game.h"

#include<iostream>
#include<time.h>

int main(int argc,char* args[])
{
    Game game;
    Level level(game);
    game.setLevel(&level);
    game.runGame();
    game.endGame();
    return 0;
}
