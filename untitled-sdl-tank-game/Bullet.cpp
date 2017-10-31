#include "Bullet.h"

#include <iostream>

Bullet :: Bullet() {}

Bullet :: Bullet(float x, float y) :GameObject(x, y)
{
	lifeCycle = 0;
	destroyed = false;
	std::cout << "Bullet created!" << std::endl;
}

Bullet::Bullet(float x, float y, float collisionRadius, MyTexture& texture) :GameObject(x, y)
{
    lifeCycle = 0;
    destroyed = false;
    std::cout << "Bullet created!" << std::endl;
    radius = collisionRadius;
    myTex = texture;
}


Bullet :: ~Bullet()
{
	std::cout << "Bullet destroyed!" << std::endl;
}

void Bullet :: move()
{
	lifeCycle += 1;
	if (lifeCycle > 20)
    {
		destroyed = true;
	}
	posX += 4;
	//cout<<"bullet pos x: "<<posX<<endl;
}
