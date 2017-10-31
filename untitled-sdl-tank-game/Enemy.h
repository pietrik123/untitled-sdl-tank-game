#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Enemy : public GameObject
{
public:
    int energy;

	Enemy();
	Enemy(float x, float y);
    Enemy(float x, float y, float collisionRadius, MyTexture& texture);

	bool checkHit(Bullet &b);
};