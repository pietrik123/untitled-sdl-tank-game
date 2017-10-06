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

    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;

    scaleX = 1.0;
    scaleY = 1.0;
}

Game :: ~Game() {
	std::cout << "Game finished!" << std::endl;
}

bool Game :: initSDL(){
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		success = false;
	}

	return success;
}

bool Game :: initGame() {
	//menu init
	
	MenuItem newGameItem;
	MenuItem quitGameItem;

	MenuWindow mainMenuWindow;
	
	newGameItem.setItem(renderer, "new_game",  "data\\gfx\\menu\\new_game_item.png");
	quitGameItem.setItem(renderer, "quit_game",  "data\\gfx\\menu\\quit_item.png");

	newGameItem.setLocation(250, 250);
	quitGameItem.setLocation(250, 370);

	std::vector<MenuItem> itemsVect;
	itemsVect.push_back(newGameItem);
	itemsVect.push_back(quitGameItem);

	mainMenuWindow.setMenuWindow(renderer, itemsVect, "data\\gfx\\menu\\menu_bg.png", "data\\gfx\\menu\\indicator.png");

	gameMenu.addMenuWindow(mainMenuWindow);
	
	if (gameMenu.validate() == false)
	{
		exit(EXIT_FAILURE);
	}

	//game init
	terrain = new GameObject(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	terrain->myTex = new MyTexture(renderer, "data\\gfx\\terrain.png");

	player = new Player(100, 100);
	player->myTex = new MyTexture(renderer, "data\\gfx\\player.png");


	enemyTemplate.myTex = new MyTexture(renderer, "data\\gfx\\enemy.png");

	bulletTemplate.myTex = new MyTexture(renderer, "data\\gfx\\bullet.png");

	flameTemplate.myTex = new MyTexture(renderer, "data\\gfx\\flame.png");


	helpScreen = new GameObject(320, 450);
	helpScreen->myTex = new MyTexture(renderer, "data\\gfx\\help.png");

	music = Mix_LoadMUS("data\\bandit_radio.wav");

	Enemy e = enemyTemplate;

	e.posX = 0.0;
	e.posY = 0.0;

	enemies.push_back(e);

	e = enemyTemplate;

	e.posX = 50.0;
	e.posY = 50.0;

	enemies.push_back(e);

	std::cout << "Game init done!" << std::endl;
	return true;
}

bool Game :: endGame() {
	SDL_FreeSurface(screenSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_FreeMusic(music);

	delete terrain;
	delete player;

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	return true;
}

bool Game::runGame()
{
	if (initSDL() != true)
	{
		exit(EXIT_FAILURE);
	}
	initGame();


	//put all functions here
	int res = gameMenu.gameMenuLoop(renderer);

	//play music
	if (Mix_PlayingMusic() == 0)
	{ 
		Mix_PlayMusic( music, -1 );
	}

	if (res == START_GAME)
	{
		mainLoop();
	}
	else if (res == QUIT_GAME)
	{
		//quit game
	}
	return true;
}

void Game :: mainLoop() {
	bool exit = false;

	bool addBulletFlag = false;
	while (exit != true) {
		//game logic cycle
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {

			const Uint8* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_UP]) {
				player->moveObj(NORTH);
			}
			if (state[SDL_SCANCODE_DOWN]) {
				player->moveObj(SOUTH);
			}
			if (state[SDL_SCANCODE_LEFT]) {
				player->moveObj(WEST);
			}
			if (state[SDL_SCANCODE_RIGHT]) {
				player->moveObj(EAST);
			}
			if (state[SDL_SCANCODE_SPACE]) {
				if (!addBulletFlag)
				{
					addBulletFlag = player->weapon->trigger();
				}		
			}
			
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_ESCAPE) { exit = true; }

			}
		}

		//player->handleGun();
		player->weapon->act();

		if (addBulletFlag == true) {
			Bullet b = bulletTemplate;
			b.posX = player->posX;
			b.posY = player->posY;
			bullets.push_back(b);
			std::cout << "bullet added!";
			addBulletFlag = false;
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

		terrain->myTex->render(renderer,
            (int)terrain->posX,
            (int)terrain->posY,
            RENDER_IN_CENTER);
     
		player->myTex->render(renderer,
            getPosXOnScreen(player->posX),
            getPosYOnScreen(player->posY),
            RENDER_IN_CENTER);

		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			(*enemyIt).myTex->render(renderer,
                getPosXOnScreen((*enemyIt).posX),
                getPosYOnScreen((*enemyIt).posY),
                RENDER_IN_CENTER);
		}

		for (bulletIt = bullets.begin();bulletIt != bullets.end(); ++bulletIt) {
			(*bulletIt).myTex->render(renderer,
                getPosXOnScreen((*bulletIt).posX),
                getPosYOnScreen((*bulletIt).posY),
                RENDER_IN_CENTER);
		}

		for (flameIt = flames.begin();flameIt != flames.end(); ++flameIt) {
			Flame &flame = (*flameIt);
			flame.myTex->renderAnim(renderer,
                getPosXOnScreen(flame.posX),
                getPosYOnScreen(flame.posY),
                RENDER_IN_CENTER, 5, flame.texFrame);
		}

		helpScreen->myTex->render(renderer,
            (int)helpScreen->posX, 
            (int)helpScreen->posY,
            RENDER_IN_CENTER);

		SDL_RenderPresent(renderer);
		//wait
		SDL_Delay(50);
	}
}

int Game::getPosXOnScreen(float worldX)
{
    return (int)(scaleX * worldX + Game::screenWidth / 2.0);
}

int Game::getPosYOnScreen(float worldY)
{
    return (int)(-scaleY * worldY + Game::screenHeight / 2.0);
}
