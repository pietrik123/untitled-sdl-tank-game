#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(float x, float y);

	bool checkHit(Bullet &b);
};