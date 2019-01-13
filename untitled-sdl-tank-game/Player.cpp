#include "Player.h"

Player::Player()
{

}

Player::Player(float x, float y) : GameObject(x, y)
{
    displcmt = 5.0;

    bulletReady = true;
    reloadingPhase = 100;
    shotFired = false;
    prevShotFired = false;
    addBullet = false;

    weapon = new BasicCannon();
}

Player::Player(float x, float y, float collisionRadius, MyTexture* texture)
    : GameObject(x, y, collisionRadius, texture)
{
    displcmt = 5.0;

    bulletReady = true;
    reloadingPhase = 100;
    shotFired = false;
    prevShotFired = false;
    addBullet = false;

    weaponIndex = WeaponId::BASIC_CANNON;

    weapons.push_back(new BasicCannon());
    weapons.push_back(new BombDrop());
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