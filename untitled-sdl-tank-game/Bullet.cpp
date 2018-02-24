#include "Bullet.h"

#include <iostream>

Bullet :: Bullet() {}

Bullet :: Bullet(float x, float y) :GameObject(x, y)
{
	lifeCycle = 0;
	destroyed = false;
	std::cout << "Bullet created!" << std::endl;
}

Bullet::Bullet(float x, float y, float collisionRadius, MyTexture& texture)
    :GameObject(x, y)
{
    lifeCycle = 0;
    destroyed = false;
    std::cout << "Bullet created!" << std::endl;
    radius = collisionRadius;
    myTex = texture;
}


Bullet :: ~Bullet()
{
	std::cout << "Bullet destroyed!" << std::endl;
}

void Bullet :: move()
{
	lifeCycle += 1;
	if (lifeCycle > 20)
    {
		destroyed = true;
	}

    switch (direction)
    {
        case SOUTH:
            posY -= 4.0;
            break;
        case WEST:
            posX -= 4.0;
            break;
        case NORTH:
            posY += 4.0;
            break;
        case EAST:
        default:
            posX += 4.0;
    }
}

float Bullet::getDirectionAngle()
{
    float angle = 0.0;
    switch (direction)
    {
        case NORTH:
            angle = 270.0;
            break;
        case SOUTH:
            angle = 90.0;
            break;
        case WEST:
            angle = 180.0;
            break;
        case EAST:
        default:
            break;
    }
    return angle;
}

