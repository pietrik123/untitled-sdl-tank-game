#include "GameObject.h"

#include <iostream>

GameObject :: GameObject() {}

GameObject :: GameObject(int x, int y) {
	posX = x;
	posY = y;
	myTex = NULL;
}

GameObject :: ~GameObject() {
	//delete this->myTex;
	std::cout << "Destroying game object!" << std::endl;
}

void GameObject :: moveObj(int direction) {
	if (direction == LEFT) {
		posX -= 5;
	}
	if (direction == RIGHT) {
		posX += 5;
	}
	if (direction == UP) {
		posY -= 5;
	}
	if (direction == DOWN) {
		posY += 5;
	}
}
