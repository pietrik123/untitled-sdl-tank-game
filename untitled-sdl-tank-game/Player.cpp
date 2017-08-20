#include "Player.h"

Player :: Player(int x, int y) : GameObject(x, y) {
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
