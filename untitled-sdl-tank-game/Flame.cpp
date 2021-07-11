#include "Flame.h"
#include "game_settings.h"

#include <iostream>

Flame::Flame() {}

Flame::Flame(float x, float y) : GameObject(x, y)
{
    std::cout << "Flame created!" << std::endl;
    maxLifeCycle = FLAME_MAX_LIFE_CYCLE;
    lifeCycle = 0;
}

Flame::Flame(float x, float y, MyTexture* texture) : GameObject(x, y)
{
    std::cout << "Flame created!" << std::endl;
    maxLifeCycle = FLAME_MAX_LIFE_CYCLE;
    lifeCycle = 0;
    myTex = texture;
}

Flame::Flame(float x, float y, MyTexture* texture, int aNumOfFramesInTexture) : GameObject(x, y)
{
    std::cout << "Flame created!" << std::endl;
    maxLifeCycle = FLAME_MAX_LIFE_CYCLE;
    lifeCycle = 0;
    myTex = texture;
    numOfFramesInTexture = aNumOfFramesInTexture;
}

void Flame::act()
{
    lifeCycle += 1;
}

bool Flame::isFlameCycleOver(const Flame &f)
{
    return f.lifeCycle > f.maxLifeCycle;
}
