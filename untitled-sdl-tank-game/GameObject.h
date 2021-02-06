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
    RECTANGLE,
    MULTI_CIRCLE
};

class GameObject
{
public:
    /** 
     * equals (-1) be default, has to be set manually. Can be used for (parent/child) handling
     */
    int id;
    /**
     * equals (-10) be default, has to be set manually. Can be used for (parent/child) handling
     */
    int childId;

    float posX;
    float posY;
    float prevPosX;
    float prevPosY;
    float radius;
    float boundsRectWidth;
    float boundsRectHeight;

    int texFrame;
    int numOfFramesInTexture;
    
    bool isToRemove;

    MyTexture* myTex;
    std::vector<MyTexture> additionalTextures;

    std::vector<Circle> collisionCircles;

    Direction direction;

    GameObject();
    GameObject(float x, float y);
    GameObject(float x, float y, float radius);
    GameObject(float x, float y, MyTexture* texture, int aNumOfFramesInTexture);
    GameObject(float x, float y, float radius, MyTexture* texture);
    GameObject(float x, float y, float boundsRectWidth, float boundsRectHeight, MyTexture* texture);
    GameObject(float x, float y, float radius, MyTexture* texture, Direction dir);
    GameObject(float x, float y, MyTexture* texture, std::vector<Circle>& collisionCircles);

    virtual ~GameObject();

    virtual void writePrevPositions();
    virtual void moveObj(Direction direction);
 
    void display(SDL_Renderer* renderer, Game* game);
    void displayAnimated(SDL_Renderer * renderer, Game * game, int gameFramePerTexFrame = 1);

    static bool isObjectToRemove(const GameObject &o);
};

float getDistance(const GameObject& obj1, const GameObject& obj2);

float getDistance(const GameObject& obj, float pointX, float pointY);

bool collision(const GameObject &obj1, const GameObject &obj2, BoundsType bounds1, BoundsType bounds2);

Point getObjectPositionInTextureAxisSystem(const GameObject& object1, const GameObject& object2, float scaleFactor = 1.0);

