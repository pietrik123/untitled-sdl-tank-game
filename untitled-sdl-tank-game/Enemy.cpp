
#include "Enemy.h"

Enemy :: Enemy() {

}

Enemy :: Enemy(int x, int y) : GameObject(x, y) {
	posX = x;
	posY = y;
}

bool Enemy:: checkHit(Bullet &b) {
	double distance = pow(pow(b.posX - this->posX, 2) + pow(b.posY - this->posY, 2), 0.5);
	bool hit = false;
	if (distance < 25.0) {
		hit = true;
	}
	return hit;
}