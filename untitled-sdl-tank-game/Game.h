#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Flame.h"
#include "Bomb.h"
#include "menu.h"

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<vector>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480

#define BULLET_LIFE 15
#define FLAME_LIFE 15

struct TextureDataStruct
{
    MyTexture terrainTex;
    MyTexture playerTexture;
    MyTexture enemyTexture;
    MyTexture brickTexture;
    MyTexture bulletTexture;
    MyTexture flameTexture;
    MyTexture helpScreenTexture;
    MyTexture bombTexture;
};

class Game
{
public:
    // SDL fields
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screenSurface;

    // music
    Mix_Music *music;

    // GUI (menu etc.)
    GameMenu gameMenu;
    GameObject helpScreen;
    	
    // game objects
    GameObject terrain;
	Player player;	

    // copyable objects
	Bullet bulletTemplate;
	Flame flameTemplate;
    Bomb bombTemplate;

    // groups of objects
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	std::vector<Flame> flames;
    std::vector<GameObject> bricks;
    std::vector<Bomb> bombs;
	
    // texture struct	
    TextureDataStruct texDataStruct;

    // other

    int screenWidth;
    int screenHeight;

    float scaleX; // screen_dx/world_dx
    float scaleY; // screen_dy/world_dy

    // constructors and destructors

	Game();
	~Game();

    // public methods

    bool initSDL();

    bool initGame();
    void mainLoop();
	bool runGame();	
	bool endGame();
	
    // utils

    int getPosXOnScreen(float);
    int getPosYOnScreen(float);
};

