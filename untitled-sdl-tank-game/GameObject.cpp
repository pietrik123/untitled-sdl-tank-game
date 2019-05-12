
#include "GameObject.h"
#include "Game.h"
#include "MyTexture.h"
#include <iostream>
#include <math.h>

GameObject::GameObject()
{
    radius = 1.0;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
    isToRemove = false;
}

GameObject::GameObject(float x, float y)
{   
	posX = x;
	posY = y;
	radius = 1.0;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y, float parRadius)
{   
	posX = x;
	posY = y;
	radius = parRadius;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y, MyTexture* texture)
{
	posX = x;
	posY = y;
	radius = 1.0;
	myTex = texture;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y, float parRadius, MyTexture* texture)
{
	posX = x;
	posY = y;
	radius = parRadius;
	myTex = texture;
	direction = EAST;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y, float parRadius, MyTexture* texture,
					   Direction dir)
{
	posX = x;
	posY = y;
	radius = parRadius;
	myTex = texture;
	direction = dir;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::~GameObject()
{
	//delete this->myTex;
	std::cout << __FUNCTION__ << " : Destroying game object!" << std::endl;
}

void GameObject::moveObj(Direction direction)
{
}

void GameObject::writePrevPositions()
{
	prevPosX = posX;
	prevPosY = posY;
}

void GameObject::display(SDL_Renderer* renderer, Game* game)
{
	myTex->render(renderer,
		game->getPosXOnScreen(posX),
		game->getPosYOnScreen(posY),
		MyTexture::RENDER_IN_CENTER);
}

float getDistance(const GameObject& obj1, const GameObject& obj2)
{
	return distanceFromPointToPoint({ obj1.posX, obj1.posY }, { obj2.posX, obj2.posY });
}

float getDistance(const GameObject& obj1, float pointX, float pointY)
{
	return distanceFromPointToPoint({ obj1.posX, obj1.posY }, { pointX, pointY });
}

bool collision(const GameObject& obj1, const GameObject& obj2,
			   BoundsType bounds1, BoundsType bounds2)
{
	if (bounds1 == RADIUS && bounds2 == RADIUS)
	{
		if (getDistance(obj1, obj2) < (obj1.radius + obj2.radius))
		{
			return true;
		}
	}
	return false;
}
