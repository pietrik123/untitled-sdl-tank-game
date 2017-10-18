#include "Player.h"

Player :: Player(float x, float y) : GameObject(x, y)
{
	posX = x;
	posY = y;
	myTex = NULL;

	bulletReady = true;
	reloadingPhase = 100;
	shotFired = false;
	prevShotFired = false;
	addBullet = false;

	weapon = new BasicCannon();
}

void Player::moveObj(Direction direction)
{
    if (direction == WEST)
    {
        posX -= 5;
    }
    if (direction == EAST)
    {
        posX += 5;
    }
    if (direction == NORTH)
    {
        posY += 5;
    }
    if (direction == SOUTH)
    {
        posY -= 5;
    }
}