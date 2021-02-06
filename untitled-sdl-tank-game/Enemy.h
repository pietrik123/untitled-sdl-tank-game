#pragma once

#include "GameObject.h"

class Bullet;

class Enemy : public GameObject
{
private:
    void basicInit();
public:
    float displcmnt;
    int energy;

    bool isStuck;
    bool collided;
    unsigned int cnt;

    short int dirX;
    short int dirY;
    
    float prevPosX;
    float prevPosY;

    Enemy();
    Enemy(float x, float y);
    Enemy(float x, float y, float collisionRadius, MyTexture* texture);


    static bool isEnemyDestroyed(const Enemy &e);
    virtual void follow(const GameObject& objectToFollow);

    bool isHit(Bullet &b);
};