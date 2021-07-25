#define _USE_MATH_DEFINES

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
    isFourDirMovementOnly = true;
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

    if (isFourDirMovementOnly)
    {
        switch (direction)
        {
        case SOUTH:
            setDirectionAngle(270.0f);
            break;
        case WEST:
            setDirectionAngle(180.0f);
            break;
        case NORTH:
            setDirectionAngle(90.0f);
            break;
        case EAST:
        default:
            setDirectionAngle(0.0f);
        }
    }

    posX += coefX * displcmnt;
    posY += coefY * displcmnt;
}

float Bullet::getDirectionAngleForView()
{
    float viewAngle = 0.0;
    switch (direction)
    {
        case NORTH:
            viewAngle = 270.0;
            break;
        case SOUTH:
            viewAngle = 90.0;
            break;
        case WEST:
            viewAngle = 180.0;
            break;
        case EAST:
        default:
            break;
    }
    return viewAngle;
}

bool Bullet::isBulletDestroyed(const Bullet& b)
{
    return b.destroyed;
}
