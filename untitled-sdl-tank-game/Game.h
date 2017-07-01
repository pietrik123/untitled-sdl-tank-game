#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Flame.h"

#include<SDL.h>
#include<SDL_image.h>
#include<vector>

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT  480

#define BULLET_LIFE 50
#define FLAME_LIFE 15

class Game {
public:
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

	Game();
	~Game();

	bool initSDL();
	bool initGame();
	bool endGame();
	void mainLoop();
};