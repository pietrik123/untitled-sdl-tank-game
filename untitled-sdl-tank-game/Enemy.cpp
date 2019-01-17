
#include "Enemy.h"
#include "Bullet.h"

#include <iostream>

Enemy::Enemy()
{
    energy = 100;
    isStuck = false;
    cnt = 0;
}

Enemy::Enemy(float x, float y) : GameObject(x, y)
{
    displcmnt = 2.5;
    energy = 100;
    isStuck = false;
    cnt = 0;
}

Enemy::Enemy(float x, float y, float collisionRadius, MyTexture* texture) : GameObject(x, y)
{
    displcmnt = 2.5;
    energy = 100;
    radius = collisionRadius;
    myTex = texture;
    isStuck = false;
    cnt = 0;
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
    // reset cnt after fixed number of steps
    if ( (isStuck == true) && (cnt > 30) )
    {
        isStuck = false;
        cnt = 0;
    }
    
    if (isStuck == true)
    {
        // at first choose a random direction to take, when stuck
        if (cnt == 9)
        {
            dirX = (rand() % 3) - 1;
            dirY = (rand() % 3) - 1;
        }
        cnt++;
    }
    else
    {
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
    }

    posX += dirX * displcmnt;
    posY += dirY * displcmnt;

    // check if enemy is far from object to follow and does not move 
    if ((getDistance(*this, objectToFollow) > radius)
        && collided == true && isStuck == false)
    {
        cnt++;

        if (cnt > 7)
        {
            isStuck = true;
        }
    }
}