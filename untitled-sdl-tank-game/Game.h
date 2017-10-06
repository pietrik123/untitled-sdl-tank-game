#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Flame.h"
#include "menu.h"

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<vector>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480

#define BULLET_LIFE 50
#define FLAME_LIFE 15

class Game {
public:
	GameMenu gameMenu;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* screenSurface;

	GameObject* terrain;
	Player* player;
	Enemy enemyTemplate;
	Bullet bulletTemplate;
	Flame flameTemplate;
	std::vector<Enemy> enemies;
	std::vector<Bullet> bullets;
	std::vector<Flame> flames;
	GameObject* helpScreen;
	
	Mix_Music *music;

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