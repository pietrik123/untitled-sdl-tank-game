#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Enemy : public GameObject
{
public:
    static const float ds;
    int energy;

	Enemy();
	Enemy(float x, float y);
    Enemy(float x, float y, float collisionRadius, MyTexture& texture);

    void follow(const GameObject& objectToFollow);

	bool checkHit(Bullet &b);
};