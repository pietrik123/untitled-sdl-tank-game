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
	GameMenu gameMenu;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screenSurface;

    MyTexture* tex;

	GameObject terrain;
	Player player;
	
	Bullet bulletTemplate;
	Flame flameTemplate;
    Bomb bombTemplate;

	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	std::vector<Flame> flames;
    std::vector<GameObject> bricks;
    std::vector<Bomb> bombs;
	
    GameObject helpScreen;
	
	Mix_Music *music;
    TextureDataStruct texDataStruct;

	Game();
	~Game();

	bool runGame();

	bool initSDL();
	bool initGame();
	
	bool endGame();
	void mainLoop();

    int getPosXOnScreen(float);
    int getPosYOnScreen(float);

    int screenWidth;
    int screenHeight;

    float scaleX; // screen_dx/world_dx
    float scaleY; // screen_dy/world_dy

};

