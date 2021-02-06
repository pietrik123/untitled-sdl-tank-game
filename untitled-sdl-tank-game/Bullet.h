#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
public:
    /**
     * delta displacement
     */
    float displcmnt;
    /**
     * maximum life cycle of a bullet
     */
    int maxLifeCycle;

    bool destroyed;
    /**
     * current lifeCycle
     */
    int lifeCycle;
    
    Bullet();
    Bullet(float x, float y, float collisionRadius, MyTexture* texture);

    ~Bullet();

    float getDirectionAngle();

    void move();
    static bool isBulletDestroyed(const Bullet& b);
};