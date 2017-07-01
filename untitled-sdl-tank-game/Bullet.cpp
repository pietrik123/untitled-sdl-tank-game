#include "Bullet.h"

#include <iostream>

Bullet :: Bullet() {}

Bullet :: Bullet(int x, int y) :GameObject(x, y) {
	posX = x;
	posY = y;
	lifeCycle = 0;
	destroyed = false;
	std::cout << "Bullet created!" << std::endl;
}

Bullet :: ~Bullet() {
	std::cout << "Bullet destroyed!" << std::endl;
}

void Bullet :: move() {
	lifeCycle += 1;
	if (lifeCycle > 20) {
		destroyed = true;
	}
	posX += 4;
	//cout<<"bullet pos x: "<<posX<<endl;
}
