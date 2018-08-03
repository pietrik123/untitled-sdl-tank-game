
#include "Bomb.h"

Bomb::Bomb() {}

Bomb::Bomb(float x, float y, MyTexture &tex)
{
    maxLifeCycle = 50;

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
    if (lifeCycle > maxLifeCycle)
    {
        exploded = true;
    }
}