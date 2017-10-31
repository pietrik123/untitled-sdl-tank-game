
#include "Enemy.h"

Enemy :: Enemy()
{
    energy = 100;
}

Enemy :: Enemy(float x, float y) : GameObject(x, y)
{
    energy = 100;
}

Enemy::Enemy(float x, float y, float collisionRadius, MyTexture& texture) : GameObject(x, y)
{
    energy = 100;
    radius = collisionRadius;
    myTex = texture;
}

bool Enemy:: checkHit(Bullet &b)
{
	double distance = pow(pow(b.posX - this->posX, 2) + pow(b.posY - this->posY, 2), 0.5);
	bool hit = false;
	if (distance < 25.0)
    {
		hit = true;
	}
	return hit;
}