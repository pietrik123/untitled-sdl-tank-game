#include "Player.h"

Player::Player()
{

}

Player :: Player(float x, float y) : GameObject(x, y)
{
	posX = x;
	posY = y;

	bulletReady = true;
	reloadingPhase = 100;
	shotFired = false;
	prevShotFired = false;
	addBullet = false;

	weapon = new BasicCannon();
}

Player::Player(float x, float y, float collisionRadius, MyTexture& texture)
    : GameObject(x, y, collisionRadius, texture)
{
    posX = x;
    posY = y;

    bulletReady = true;
    reloadingPhase = 100;
    shotFired = false;
    prevShotFired = false;
    addBullet = false;

    weaponIndex = WeaponIndex::BASIC_CANNON;

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
        posX -= ds;
    }
    if (direction == EAST)
    {
        posX += ds;
    }
    if (direction == NORTH)
    {
        posY += ds;
    }
    if (direction == SOUTH)
    {
        posY -= ds;
    }
}

Weapon* Player::getCurrentWeapon()
{
    return weapons[weaponIndex];
}

const float Player::ds = 5.0;