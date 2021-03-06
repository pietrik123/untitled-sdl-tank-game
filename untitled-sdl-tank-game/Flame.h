#pragma once

#include "GameObject.h"

class Flame : public GameObject
{
public:
    int maxLifeCycle;
    int lifeCycle;

    Flame();
    Flame(float x, float y);
    Flame(float x, float y, MyTexture* texture);
    Flame(float x, float y, MyTexture* texture, int aNumOfFramesInTexture);

    static bool isFlameCycleOver(const Flame& f);

    void act();
};