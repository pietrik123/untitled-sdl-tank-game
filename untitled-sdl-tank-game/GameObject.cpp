
#include "GameObject.h"
#include "Game.h"
#include "MyTexture.h"
#include <iostream>
#include <math.h>

GameObject::GameObject()
{
}

GameObject::GameObject(float x, float y)
{   
	posX = x;
	posY = y;
	radius = 1.0;
}

GameObject::GameObject(float x, float y, float parRadius)
{   
	posX = x;
	posY = y;
	radius = parRadius;
}

GameObject::GameObject(float x, float y, MyTexture* texture)
{
	posX = x;
	posY = y;
	radius = 1.0;
	myTex = texture;
}

GameObject::GameObject(float x, float y, float parRadius, MyTexture* texture)
{
	posX = x;
	posY = y;
	radius = parRadius;
	myTex = texture;
	direction = EAST;
}

GameObject::GameObject(float x, float y, float parRadius, MyTexture* texture,
					   Direction dir)
{
	posX = x;
	posY = y;
	radius = parRadius;
	myTex = texture;
	direction = dir;
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
	return
		powf(powf(obj1.posX - obj2.posX, 2.0) + powf(obj1.posY - obj2.posY, 2.0), 0.5);
}

float getDistance(const GameObject& obj1, float pointX, float pointY)
{
	return
		powf(powf(obj1.posX - pointX, 2.0) + powf(obj1.posY - pointY, 2.0), 0.5);
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
