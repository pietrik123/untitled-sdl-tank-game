#include "Player.h"

void Player::basicInit()
{
    energy = 100u;
    maxEnergy = 100u;
    bulletReady = true;
    reloadingPhase = 100;
    shotFired = false;
    prevShotFired = false;
    addBullet = false;
    displcmt = 5.0;
    coinsCollected = 0;
    afterHitCounter = 0;

    weaponIndex = WeaponId::BASIC_CANNON;
    weapons.push_back(new BasicCannon());
    weapons.push_back(new BombDrop());
}

Player::Player()
{
    basicInit();
}

Player::Player(float x, float y) : GameObject(x, y)
{
    basicInit();
}

Player::Player(float x, float y, float collisionRadius, MyTexture* texture)
    : GameObject(x, y, collisionRadius, texture)
{
    basicInit();
}

Player::~Player()
{
    
}

void Player::moveObj(Direction direction)
{
    if (direction == WEST)
    {
        posX -= displcmt;
    }
    if (direction == EAST)
    {
        posX += displcmt;
    }
    if (direction == NORTH)
    {
        posY += displcmt;
    }
    if (direction == SOUTH)
    {
        posY -= displcmt;
    }
}

void Player::act()
{
    // handle hits by enemies - player loses energy
    // lose energy only on the 1st tick
    if (afterHitCounter == 1)
    {
        if (static_cast<int>(energy - 10) < 0)
        {
            energy = 0;
        }
        else
        {
            energy -= 10;
        }
    }
    // inc. counter
    if (afterHitCounter > 0 && afterHitCounter < 100)
    {
        afterHitCounter += 1;
    }
    // overflow - reset counter
    if (afterHitCounter >= 100)
    {
        afterHitCounter = 0;
    }
}

Weapon* Player::getCurrentWeapon()
{
    return weapons[weaponIndex];
}