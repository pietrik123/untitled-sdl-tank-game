
#include "GameObject.h"
#include "Game.h"
#include "MyTexture.h"
#include <iostream>
#include <math.h>

GameObject::GameObject()
{
    radius = 1.0;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y)
{   
	posX = x;
	posY = y;
	radius = 1.0;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y, float parRadius)
{   
	posX = x;
	posY = y;
	radius = parRadius;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y, MyTexture* texture, std::vector<Circle>& circles)
{
	posX = x;
	posY = y;
	radius = 1.0;
	myTex = texture;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
    collisionCircles = circles;
}

GameObject::GameObject(float x, float y, MyTexture* texture, int aNumOfFramesInTexture)
{
    posX = x;
    posY = y;
    radius = 1.0;
    myTex = texture;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
numOfFramesInTexture = aNumOfFramesInTexture;
}

GameObject::GameObject(float x, float y, float parRadius, MyTexture* texture)
{
    posX = x;
    posY = y;
    radius = parRadius;
    myTex = texture;
    direction = EAST;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y, float parRadius, MyTexture* texture,
    Direction dir)
{
    posX = x;
    posY = y;
    radius = parRadius;
    myTex = texture;
    direction = dir;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
}

GameObject::GameObject(float x, float y, float width, float height, MyTexture* texture)
{
    posX = x;
    posY = y;
    myTex = texture;
    texFrame = 0;
    id = -1;
    childId = -1;
    isToRemove = false;
    boundsRectWidth = width;
    boundsRectHeight = height;
}

GameObject::~GameObject()
{
    //delete this->myTex;
    std::cout << __FUNCTION__ << " : Destroying game object!" << std::endl;
}

void GameObject::moveObj(Direction direction)
{
}

void GameObject::writePrevPositions()
{
    prevPosX = posX;
    prevPosY = posY;
}

void GameObject::display(SDL_Renderer* renderer, Game* game)
{
    myTex->render(renderer,
        game->getPosXOnScreen(posX),
        game->getPosYOnScreen(posY),
        MyTexture::RENDER_IN_CENTER);
}

void GameObject::displayAnimated(SDL_Renderer* renderer, Game* game, int par)
{
    myTex->renderAnim(renderer, game->getPosXOnScreen(posX), game->getPosYOnScreen(posY),
        MyTexture::RENDER_IN_CENTER, numOfFramesInTexture, texFrame/par);
    texFrame++;
    if (texFrame > par*numOfFramesInTexture)
    {
        texFrame = 0;
    }
}

float getDistance(const GameObject& obj1, const GameObject& obj2)
{
    return distanceFromPointToPoint({ obj1.posX, obj1.posY }, { obj2.posX, obj2.posY });
}

float getDistance(const GameObject& obj1, float pointX, float pointY)
{
    return distanceFromPointToPoint({ obj1.posX, obj1.posY }, { pointX, pointY });
}

bool collision(const GameObject& obj1, const GameObject& obj2,
    BoundsType bounds1, BoundsType bounds2)
{
    if (bounds1 == RADIUS && bounds2 == RADIUS)
    {
        if (getDistance(obj1, obj2) < (obj1.radius + obj2.radius))
        {
            return true;
        }
    }

    if (bounds1 == RADIUS && bounds2 == MULTI_CIRCLE)
    {
        Circle obj1Circle;
        obj1Circle.radius = obj1.radius;
        obj1Circle.center = getObjectPositionInTextureAxisSystem(obj1, obj2, 1.0);

        // calculation is done in 2nd object's texture axis system 
        for (std::vector<Circle>::const_iterator it = obj2.collisionCircles.begin(); it != obj2.collisionCircles.end(); ++it)
        {
            if (areCirclesIntersecting(obj1Circle, *it))
            {
                return true;
            }
        }
    }

    if (bounds1 == RADIUS && bounds2 == RECTANGLE)
    {
        if ( (abs(obj1.posX - obj2.posX) <= obj1.radius + obj2.boundsRectWidth/2.0)
            && (abs(obj1.posY - obj2.posY) <= obj1.radius + obj2.boundsRectHeight/2.0) )
        {
            return true;
        }
    }

	return false;
}

Point getObjectPositionInTextureAxisSystem(const GameObject& object1, const GameObject& object2, float scaleFactor)
{
    // object1 - game object, of which coordinates we would like to get
    // object2 - game object with the texture with axis system, in which we want to get coordinates 
    Point pos;
    std::pair<int, int> widthAndHeightOfTheTex = object2.myTex->getTextureWidthAndHeight();
    float texWidth = static_cast<float> (widthAndHeightOfTheTex.first);
    float texHeight = static_cast<float> (widthAndHeightOfTheTex.second);
    pos.PosX = (object1.posX - object2.posX) / scaleFactor + texWidth / 2.0;
    pos.PosY = (object1.posY - object2.posY) / scaleFactor + texHeight / 2.0;
    return pos;
}
