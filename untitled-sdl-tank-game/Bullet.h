#pragma once

#include "GameObject.h"

class Bullet : public GameObject
{
public:
	bool destroyed;
	int lifeCycle;
	
	Bullet();
	Bullet(float x, float y);
    Bullet(float x, float y, float collisionRadius, MyTexture& texture);

	~Bullet();

    float getDirectionAngle();

	void move();
};