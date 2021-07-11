#include "Bullet.h"
#include "game_settings.h"

#include <iostream>


Bullet::Bullet() {}

Bullet::Bullet(float x, float y, float collisionRadius, MyTexture* texture)
    : GameObject(x, y)
{
    displcmnt = BULLET_SPEED;
    maxLifeCycle = BULLET_MAX_LIFE_CYCLE;

    lifeCycle = 0;
    destroyed = false;
    std::cout << __FUNCTION__ << " : Bullet created!" << std::endl;
    radius = collisionRadius;
    myTex = texture;
}


Bullet::~Bullet()
{
    std::cout << __FUNCTION__ << " : Bullet destroyed!" << std::endl;
}

void Bullet::move()
{
    lifeCycle += 1;
    if (lifeCycle > maxLifeCycle)
    {
        destroyed = true;
    }

    switch (direction)
    {
        case SOUTH:
            posY -= displcmnt;
            break;
        case WEST:
            posX -= displcmnt;
            break;
        case NORTH:
            posY += displcmnt;
            break;
        case EAST:
        default:
            posX += displcmnt;
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

bool Bullet::isBulletDestroyed(const Bullet& b)
{
    return b.destroyed;
}
