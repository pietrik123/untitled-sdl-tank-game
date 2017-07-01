#pragma once

#include "GameObject.h"
#include "Bullet.h"

class Enemy : public GameObject {
public:
	Enemy();
	Enemy(int x, int y);

	bool checkHit(Bullet &b);
};