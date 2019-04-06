#include "FollowingEnemy.h"

FollowingEnemy::FollowingEnemy(float x, float y, float collisionRadius, MyTexture * texture, Point destinationPoint, Point patrolPointA, Point patrolPointB, double minDinstanceForChase)
	: Enemy(x, y, collisionRadius, texture)
{
	std::cout << "CREATED FOLLOWING ENEMY!" << std::endl;
	m_patrolPointA = patrolPointA;
	m_patrolPointB = patrolPointB;
	m_minDinstanceForChase = minDinstanceForChase;
	m_destinationPoint = destinationPoint;
}

void FollowingEnemy::follow(const GameObject & objectToFollow)
{
	if (distanceFromPointToPoint({ objectToFollow.posX, objectToFollow.posY }, { posX, posY }) <= m_minDinstanceForChase)
	{
		m_iAmChasing = true;
		GoToObject(objectToFollow);
	}
	else
	{
		//m_iAmChasing = false;
		patrolArea();
	}
}

void FollowingEnemy::patrolArea()
{
	// chose point only if stoping chasing or one of point already reached
	if(m_iAmChasing == true 
		|| (posX == m_patrolPointA.PosX && posY == m_patrolPointA.PosY)
		|| (posX == m_patrolPointB.PosX && posY == m_patrolPointB.PosY))
	{ 
		m_iAmChasing = false;
		m_destinationPoint = chosePointToGoTo();
	}
	GoToPoint(m_destinationPoint);
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
	return distanceFromPointToPoint({ posX, posY }, m_patrolPointA) > distanceFromPointToPoint({ posX, posY }, m_patrolPointB) ? m_patrolPointA : m_patrolPointB;
}
