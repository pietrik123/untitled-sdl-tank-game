#include "Bomb.h"
#include "game_settings.h"

Bomb::Bomb() {}

Bomb::Bomb(float x, float y, MyTexture *tex)
{
    maxLifeCycle = BOMB_MAX_LIFE_CYCLE;

    myTex = tex;
    exploded = false;
    explosionRadius = BOMB_EXPLOSION_RADIUS;
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

bool Bomb::isBombExploded(const Bomb &b)
{
    return b.exploded;
}