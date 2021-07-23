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

    bool isFourDirMovementOnly;

    bool destroyed;
    /**
     * current lifeCycle
     */
    int lifeCycle;
    
    Bullet();
    Bullet(float x, float y, float collisionRadius, MyTexture* texture);

    ~Bullet();

    float getDirectionAngleForView();

    void move();

    static bool isBulletDestroyed(const Bullet& b);
};