#pragma once
#include <vector>
#include "utils/utils.h"

class Game;
class MyTexture;
struct SDL_Renderer;

enum Direction
{
    EAST = 1,
    NORTH = 2,
    WEST = 3,
    SOUTH = 4
};

enum BoundsType
{
    RADIUS,
    POLYGON,
    RECTANGLE
};

class GameObject
{
public:
    float posX;
    float posY;
    float prevPosX;
    float prevPosY;
    float radius;

    MyTexture* myTex;
    std::vector<MyTexture> additionalTextures;

    Direction direction;

    GameObject();
    GameObject(float x, float y);
    GameObject(float x, float y, float radius);
    GameObject(float x, float y, MyTexture* texture);
    GameObject(float x, float y, float radius, MyTexture* texture);
    GameObject(float x, float y, float radius, MyTexture* texture, Direction dir);

    virtual ~GameObject();

    virtual void writePrevPositions();
    virtual void moveObj(Direction direction);
 
    void display(SDL_Renderer* renderer, Game* game);
};

float getDistance(const GameObject& obj1, const GameObject& obj2);

float getDistance(const GameObject& obj, float pointX, float pointY);

bool collision(const GameObject &obj1, const GameObject &obj2, BoundsType bounds1, BoundsType bounds2);

