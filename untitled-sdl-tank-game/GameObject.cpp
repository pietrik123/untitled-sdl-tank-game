#include "GameObject.h"

#include <iostream>

GameObject :: GameObject() {}

GameObject :: GameObject(float x, float y) {
	posX = x;
	posY = y;
	myTex = NULL;
}

GameObject :: ~GameObject() {
	//delete this->myTex;
	std::cout << "Destroying game object!" << std::endl;
}

void GameObject :: moveObj(int direction) {
	if (direction == WEST) {
		posX -= 5;
	}
	if (direction == EAST) {
		posX += 5;
	}
	if (direction == NORTH) {
		posY += 5;
	}
	if (direction == SOUTH) {
		posY -= 5;
	}
}
