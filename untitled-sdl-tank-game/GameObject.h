#pragma once

#include "MyTexture.h"

enum Direction
{
    EAST = 1,
    NORTH = 2,
	WEST = 3,
	SOUTH = 4
};

enum BoundsType
{
    RADIUS,
    POLYGON,
    RECTANGLE
};

class GameObject
{
public:
	float posX;
	float posY;

	MyTexture myTex;

	GameObject();
	GameObject(float x, float y);
    GameObject(float x, float y, float radius);
    GameObject(float x, float y, MyTexture& texture);
    GameObject(float x, float y, float radius, MyTexture& texture);

	~GameObject();

	virtual void moveObj(Direction direction);

    float radius;
};

float getDistance(const GameObject& obj1, const GameObject& obj2);

bool collision(const GameObject &obj1, const GameObject &obj2, BoundsType bounds1, BoundsType bounds2);
