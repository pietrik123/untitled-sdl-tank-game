
#include "Game.h"

#include <iostream>

Game :: Game() {
	std::cout << "Game started!" << std::endl;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screenSurface = NULL;

	Enemy enemyTemplate(-10, -10);
	Bullet bulletTemplate(-10, -10);
	Flame flameTemplate(-10, -10);
}

Game :: ~Game() {
	std::cout << "Game finished!" << std::endl;
}

bool Game :: initSDL(){
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		success = false;
		std::cout << "Error: " << SDL_GetError() << std::endl;
	}
	else {
		window = SDL_CreateWindow("Ziemniak", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL) {
			success = false;
			std::cout << "Error: " << SDL_GetError() << std::endl;
		}
		else {
			int imgFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imgFlags) & imgFlags)) {
				success = false;
				std::cout << "Error: " << SDL_GetError() << std::endl;
			}
			else {
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				if (renderer == NULL) {
					success = false;
					std::cout << "Error: " << SDL_GetError() << std::endl;
				}
			}

			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;
}

bool Game :: initGame() {
	terrain = new GameObject(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	terrain->myTex = new MyTexture(renderer, "data\\\gfx\\terrain.png");

	player = new Player(100, 100);
	player->myTex = new MyTexture(renderer, "data\\gfx\\player.png");


	enemyTemplate.myTex = new MyTexture(renderer, "data\\gfx\\enemy.png");

	bulletTemplate.myTex = new MyTexture(renderer, "data\\gfx\\bullet.png");

	flameTemplate.myTex = new MyTexture(renderer, "data\\gfx\\flame.png");


	helpScreen = new GameObject(320, 450);
	helpScreen->myTex = new MyTexture(renderer, "data\\gfx\\help.png");

	Enemy e = enemyTemplate;

	e.posX = 250;
	e.posY = 400;

	enemies.push_back(e);

	e = enemyTemplate;

	e.posX = 450;
	e.posY = 100;

	enemies.push_back(e);

	//std::cout<<player->myTex.texture<<std::endl;
	std::cout << "Game init done!" << std::endl;
	return true;
}

bool Game :: endGame() {
	SDL_FreeSurface(screenSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	delete terrain;
	delete player;
	return true;
}

void Game :: mainLoop() {
	bool exit = false;


	while (exit != true) {
		//game logic cycle
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {

			const Uint8* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_UP]) {
				player->moveObj(UP);
			}
			if (state[SDL_SCANCODE_DOWN]) {
				player->moveObj(DOWN);
			}
			if (state[SDL_SCANCODE_LEFT]) {
				player->moveObj(LEFT);
			}
			if (state[SDL_SCANCODE_RIGHT]) {
				player->moveObj(RIGHT);
			}
			if (state[SDL_SCANCODE_SPACE]) {
				player->shotFired = true;
			}
			else {
				player->shotFired = false;
			}
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_ESCAPE) { exit = true; }


			}
		}

		player->handleGun();

		if (player->addBullet == true) {
			Bullet b = bulletTemplate;
			b.posX = player->posX;
			b.posY = player->posY;
			bullets.push_back(b);
			std::cout << "bullet added!";
		}


		std::vector<Enemy>::iterator enemyIt;
		std::vector<Bullet>::iterator bulletIt;
		std::vector<Flame>::iterator flameIt;


		int n;
		int i;
		n = bullets.size();

		for (i = 0; i<n; i++) {
			//cout<<"Entering loop..."<<"No. of elements: "<<bullets.size()<<endl;
			bullets[i].move();

			if (bullets[i].lifeCycle > BULLET_LIFE) {
				bullets.erase(bullets.begin() + i);
				std::cout << "Deleted" << std::endl;
			}
		}

		n = enemies.size();

		for (i = 0; i<n; i++) {
			for (bulletIt = bullets.begin();bulletIt != bullets.end(); ++bulletIt) {
				if (enemies[i].checkHit(*bulletIt) == true) {
					//add flame

					Flame f = flameTemplate;

					f.posX = enemies[i].posX + 10;
					f.posY = enemies[i].posY + 10;

					flames.push_back(f);

					f = flameTemplate;

					f.posX = enemies[i].posX - 15;
					f.posY = enemies[i].posY + 3;

					flames.push_back(f);

					f = flameTemplate;

					f.posX = enemies[i].posX;
					f.posY = enemies[i].posY - 7;

					flames.push_back(f);

					enemies.erase(enemies.begin() + i);


				}
			}
		}

		n = flames.size();

		for (i = 0;i<n;i++) {
			flames[i].act();

			if (flames[i].lifeCycle > 14) {
				flames.erase(flames.begin() + i);
			}
		}


		//display
		SDL_RenderClear(renderer);


		terrain->myTex->render(renderer, terrain->posX, terrain->posY, RENDER_IN_CENTER);
		player->myTex->render(renderer, player->posX, player->posY, RENDER_IN_CENTER);


		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			(*enemyIt).myTex->render(renderer, (*enemyIt).posX, (*enemyIt).posY, RENDER_IN_CENTER);
		}



		for (bulletIt = bullets.begin();bulletIt != bullets.end(); ++bulletIt) {
			(*bulletIt).myTex->render(renderer, (*bulletIt).posX, (*bulletIt).posY, RENDER_IN_CENTER);
		}

		for (flameIt = flames.begin();flameIt != flames.end(); ++flameIt) {
			Flame &flame = (*flameIt);
			flame.myTex->renderAnim(renderer, flame.posX, flame.posY, RENDER_IN_CENTER, 5, flame.texFrame);
		}

		helpScreen->myTex->render(renderer, helpScreen->posX, helpScreen->posY, RENDER_IN_CENTER);

		SDL_RenderPresent(renderer);
		//wait
		SDL_Delay(50);
	}
}