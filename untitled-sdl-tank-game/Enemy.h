#pragma once

#include "GameObject.h"

class Bullet;

class Enemy : public GameObject
{
private:
    void basicInit();
public:
    // enemy speed, unit: [game distance unit]/[1*frame] 
    float speed;
    int energy;

    bool isStuck;
    bool collided;
    unsigned int cnt;

    short int dirX;
    short int dirY;

    Enemy();
    Enemy(float x, float y);
    Enemy(float x, float y, float collisionRadius, MyTexture* texture);


    static bool isEnemyDestroyed(const Enemy &e);
    virtual void follow(const GameObject& objectToFollow);

    bool isHit(Bullet &b);
};