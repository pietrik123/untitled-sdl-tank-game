#include "FollowingEnemy.h"

FollowingEnemy::FollowingEnemy(float x, float y, float collisionRadius, MyTexture* texture, Point dstPoint, Point patPointA, Point patPointB, double minDist)
{
	Enemy(x, y, collisionRadius, texture);
	patrolPointA = patPointA;
	patrolPointB = patPointB;
	minDinstanceForChase = minDist;
	destinationPoint = dstPoint;
}

void FollowingEnemy::follow(const GameObject & objectToFollow)
{
	
	if (distanceFromPointToPoint({ objectToFollow.posX, objectToFollow.posY }, { posX, posY }) <= minDinstanceForChase)
	{
		iAmChasing = true;
		GoToObject(objectToFollow);
	}
	else
	{
		patrolArea();
	}
}

void FollowingEnemy::patrolArea()
{
	// chose point only if stoping chasing or one of point already reached
	if(iAmChasing = true 
		|| (posX == patrolPointA.PosX && posY == patrolPointA.PosY)
		|| (posX == patrolPointB.PosX && posY == patrolPointB.PosY))
	{ 
		iAmChasing = false;
		destinationPoint = chosePointToGoTo();
	}
	GoToPoint(destinationPoint);
}

void FollowingEnemy::GoToObject(const GameObject& object)
{
	if (object.posX - posX > 0)
		{
			dirX = 1;
		}
		else if (object.posX - posX < 0)
		{
			dirX = -1;
		}
		else
		{
			dirX = 0;
		}

		if (object.posY - posY > 0)
		{
			dirY = 1;
		}
		else if (object.posY - posY < 0)
		{
			dirY = -1;
		}
		else
		{
			dirY = 0;
		}
		posX += dirX * displcmnt;
		posY += dirY * displcmnt;
}

void FollowingEnemy::GoToPoint(Point point)
{
	if (point.PosX - posX > 0)
	{
		dirX = 1;
	}
	else if (point.PosX - posX < 0)
	{
		dirX = -1;
	}
	else
	{
		dirX = 0;
	}

	if (point.PosY - posY > 0)
	{
		dirY = 1;
	}
	else if (point.PosY - posY < 0)
	{
		dirY = -1;
	}
	else
	{
		dirY = 0;
	}
	posX += dirX * displcmnt;
	posY += dirY * displcmnt;
}

Point FollowingEnemy::chosePointToGoTo()
{
	// between patrolPointA and patrolPointB go to further one if you have to pick
	return distanceFromPointToPoint({ posX, posY }, patrolPointA) > distanceFromPointToPoint({ posX, posY }, patrolPointB) ? patrolPointA : patrolPointB;
}
