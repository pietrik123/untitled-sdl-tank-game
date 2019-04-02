#include "Enemy.h"
#include "utils/utils.h"

class FollowingEnemy : public Enemy
{
	bool iAmChasing;
	Point destinationPoint;
	Point patrolPointA;
	Point patrolPointB;
	double minDinstanceForChase;
public:
	FollowingEnemy(float x, float y, float collisionRadius, MyTexture* texture, Point dstPoint, Point patPointA, Point patPointB, double minDinstanceForChase);
	virtual void follow(const GameObject& objectToFollow);
	void patrolArea();
	void GoToObject(const GameObject& objectToFollow);
	Point chosePointToGoTo();
	void GoToPoint(Point point);
	//std::tuple<int, int> directionTuple
};