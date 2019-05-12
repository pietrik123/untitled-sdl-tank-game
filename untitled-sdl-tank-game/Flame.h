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

    void act();
};