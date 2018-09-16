#include "Game.h"

#include<iostream>
#include<time.h>

int main(int argc,char* args[])
{
    srand(time(NULL));

    Game g;
    g.runGame();
    g.endGame();
    return 0;
}
