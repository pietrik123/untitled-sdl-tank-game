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

Weapon* Player::getCurrentWeapon()
{
    return weapons[weaponIndex];
}