#pragma once

#include "MyTexture.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

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
