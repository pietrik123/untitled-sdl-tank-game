#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Enemy : public GameObject
{
public:
    float displcmnt;
    int energy;
    bool isStuck;
    bool collided;
    unsigned int cnt;

    short int dirX = 0;
    short int dirY = 0;

    Enemy();
    Enemy(float x, float y);
    Enemy(float x, float y, float collisionRadius, MyTexture& texture);

    void follow(const GameObject& objectToFollow);

    bool isHit(Bullet &b);
};