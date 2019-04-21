#include "Enemy.h"
#include "utils/utils.h"

class PatrollingEnemy : public Enemy
{
	bool m_iAmChasing;
	Point m_destinationPoint;
	Point m_patrolPointA;
	Point m_patrolPointB;
	double m_minDinstanceForChase;
public:
	PatrollingEnemy(float x, float y, float collisionRadius, MyTexture* texture, Point destinationPoint, Point patrolPointA, Point patrolPointB, double minDinstanceForChase);
	virtual void follow(const GameObject& objectToFollow);
	void patrolArea();
	void GoToObject(const GameObject& objectToFollow);
	Point chosePointToGoTo();
	void GoToPoint(const Point& point);
};