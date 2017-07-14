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
	int posX;
	int posY;

	MyTexture* myTex;

	GameObject();
	GameObject(int x, int y);

	~GameObject();

	void moveObj(int direction);
};
