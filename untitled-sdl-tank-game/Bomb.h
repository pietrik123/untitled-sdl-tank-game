#pragma once

#include "GameObject.h"

class Bomb : public GameObject
{
public:

    float explosionRadius;
    int lifeCycle;
    bool exploded;

    Bomb();
    Bomb(float x, float y, MyTexture &tex);
    void act();

    ~Bomb();

    static const int maxLife;
};