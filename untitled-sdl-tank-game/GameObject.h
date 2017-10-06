#pragma once

#include "MyTexture.h"

enum Direction
{
    EAST = 1,
    NORTH = 2,
	WEST = 3,
	SOUTH = 4
};

class GameObject {
public:
	float posX;
	float posY;

	MyTexture* myTex;

	GameObject();
	GameObject(float x, float y);

	~GameObject();

	void moveObj(int direction);
};
