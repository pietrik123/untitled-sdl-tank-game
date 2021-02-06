#pragma once

#include "GameObject.h"

class Bomb : public GameObject
{
public:
    /**
     * Maximum lifeCycle
     */
    int maxLifeCycle;

    float explosionRadius;
    /**
     * Current lifecycle.
     */
    int lifeCycle;
    bool exploded;

    /**
     * Creates empty bomb object.
     */
    Bomb();

    /**
     * Creates a concrete bomb object.
     */
    Bomb(float x, float y, MyTexture *tex);

    void act();
    static bool isBombExploded(const Bomb &b);

    ~Bomb();
};