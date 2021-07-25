#include "PatrollingEnemy.h"

PatrollingEnemy::PatrollingEnemy(float x, float y, float collisionRadius, MyTexture * texture, Point destinationPoint, Point patrolPointA, Point patrolPointB, double minDinstanceForChase)
	: Enemy(std::move(x), std::move(y), std::move(collisionRadius), std::move(texture)),
	m_patrolPointA{ patrolPointA },
	m_patrolPointB{ patrolPointB },
	m_minDinstanceForChase{ minDinstanceForChase },
	m_destinationPoint{ destinationPoint }
{
}

void PatrollingEnemy::follow(const GameObject& objectToFollow)
{
	if (distanceFromPointToPoint({ objectToFollow.posX, objectToFollow.posY }, { posX, posY }) <= m_minDinstanceForChase)
	{
		m_iAmChasing = true;
		GoToObject(objectToFollow);
	}
	else
	{
		patrolArea();
	}
}

void PatrollingEnemy::patrolArea()
{
	// chose point only if stoping chasing or one of point already reached
	if(m_iAmChasing == true 
		|| (posX == m_patrolPointA.PosX && posY == m_patrolPointA.PosY)
		|| (posX == m_patrolPointB.PosX && posY == m_patrolPointB.PosY))
	{ 
		m_iAmChasing = false;
		m_destinationPoint = choosePointToGoTo();
	}
	GoToPoint(m_destinationPoint);
}

void PatrollingEnemy::GoToObject(const GameObject& object)
{
	GoToPoint({ object.posX, object.posY });
}

void PatrollingEnemy::GoToPoint(const Point& point)
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
	posX += dirX * speed;
	posY += dirY * speed;
}

Point PatrollingEnemy::choosePointToGoTo()
{
	// between patrolPointA and patrolPointB go to further one if you have to pick
	return distanceFromPointToPoint({ posX, posY }, m_patrolPointA) > distanceFromPointToPoint({ posX, posY }, m_patrolPointB) ? m_patrolPointA : m_patrolPointB;
}
