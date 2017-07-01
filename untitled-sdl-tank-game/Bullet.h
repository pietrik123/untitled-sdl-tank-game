#pragma once

#include "GameObject.h"

class Bullet : public GameObject {
public:
	bool destroyed;
	int lifeCycle;
	
	Bullet();
	Bullet(int x, int y);

	~Bullet();

	void move();
};