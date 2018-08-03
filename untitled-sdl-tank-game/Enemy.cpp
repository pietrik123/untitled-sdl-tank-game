
#include "Enemy.h"

Enemy::Enemy()
{
    energy = 100;
}

Enemy::Enemy(float x, float y) : GameObject(x, y)
{
    displcmnt = 2.5;
    energy = 100;
}

Enemy::Enemy(float x, float y, float collisionRadius, MyTexture& texture) : GameObject(x, y)
{
    displcmnt = 2.5;
    energy = 100;
    radius = collisionRadius;
    myTex = texture;
}

bool Enemy::isHit(Bullet &b)
{
	double distance = pow(pow(b.posX - this->posX, 2) + pow(b.posY - this->posY, 2), 0.5);
	bool hit = false;
	if (distance < 25.0)
    {
		hit = true;
	}
	return hit;
}

void Enemy::follow(const GameObject& objectToFollow)
{   
    short int dirX = 0;
    short int dirY = 0;

    if (objectToFollow.posX - posX > 0)
    {
        dirX = 1;
    }
    else if (objectToFollow.posX - posX < 0)
    {
        dirX = -1;
    }
    else
    {
        dirX = 0;
    }

    if (objectToFollow.posY - posY > 0)
    {
        dirY = 1;
    }
    else if (objectToFollow.posY - posY < 0)
    {
        dirY = -1;
    }
    else
    {
        dirY = 0;
    }

    posX += dirX * displcmnt;
    posY += dirY * displcmnt;
}