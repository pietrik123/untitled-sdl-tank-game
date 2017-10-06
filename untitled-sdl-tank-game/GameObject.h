#pragma once

#include "MyTexture.h"

enum Direction
{
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
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
