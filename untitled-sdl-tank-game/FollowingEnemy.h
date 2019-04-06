#include "Enemy.h"
#include "utils/utils.h"

class FollowingEnemy : public Enemy
{
	bool m_iAmChasing;
	Point m_destinationPoint;
	Point m_patrolPointA;
	Point m_patrolPointB;
	double m_minDinstanceForChase;
public:
	FollowingEnemy(float x, float y, float collisionRadius, MyTexture* texture, Point destinationPoint, Point patrolPointA, Point patrolPointB, double minDinstanceForChase);
	virtual void follow(const GameObject& objectToFollow);
	void patrolArea();
	void GoToObject(const GameObject& objectToFollow);
	Point chosePointToGoTo();
	void GoToPoint(Point point);
	//std::tuple<int, int> directionTuple
};