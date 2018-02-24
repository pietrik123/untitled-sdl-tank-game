
#include "Bomb.h"

Bomb::Bomb() {}

Bomb::Bomb(float x, float y, MyTexture &tex)
{
    posX = x;
    posY = y;
    myTex = tex;
    exploded = false;
    explosionRadius = 25.0;
    lifeCycle = 0;
}

Bomb::~Bomb() {}

void Bomb::act()
{
    lifeCycle += 1;
    if (lifeCycle > maxLife)
    {
        exploded = true;
    }
}

const int Bomb::maxLife = 50;