#include "Game.h"

#include <iostream>

Game :: Game()
{
	std::cout << "Game started!" << std::endl;

	window = NULL;
	renderer = NULL;
	screenSurface = NULL;

    tex = NULL;

    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;

    scaleX = 1.0;
    scaleY = 1.0;
}

Game :: ~Game() 
{
	std::cout << "Game finished!" << std::endl;
}

bool Game :: initSDL()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
		success = false;
		std::cout << "Error: " << SDL_GetError() << std::endl;
	}
	else
    {
		window = SDL_CreateWindow("Ziemniak", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
        {
			success = false;
			std::cout << "Error: " << SDL_GetError() << std::endl;
		}
		else
        {
			int imgFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imgFlags) & imgFlags))
            {
				success = false;
				std::cout << "Error: " << SDL_GetError() << std::endl;
			}
			else
            {
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				if (renderer == NULL)
                {
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

bool Game :: initGame()
{
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
        std::cout << "Error in game menu validation!" << "\n";
		exit(EXIT_FAILURE);
	}

    // load textures

    texDataStruct.terrainTex = MyTexture(renderer, "data\\gfx\\terrain.png");

    tex = new MyTexture(renderer, "data\\gfx\\terrain.png");

    texDataStruct.playerTexture = MyTexture(renderer, "data\\gfx\\player.png");
    texDataStruct.enemyTexture = MyTexture(renderer, "data\\gfx\\enemy.png");
    texDataStruct.brickTexture = MyTexture(renderer, "data\\gfx\\brick.png");
    texDataStruct.bulletTexture = MyTexture(renderer, "data\\gfx\\bullet.png");
    texDataStruct.flameTexture = MyTexture(renderer, "data\\gfx\\flame.png");
    texDataStruct.helpScreenTexture = MyTexture(renderer, "data\\gfx\\help.png");

	//game init
	terrain = GameObject(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, texDataStruct.terrainTex);
	player = Player(100.0, 100.0, 25.0, texDataStruct.playerTexture);

    enemies.push_back(Enemy(0.0, 0.0, 25.0, texDataStruct.enemyTexture));
    enemies.push_back(Enemy(50.0, 50.0, 25.0, texDataStruct.enemyTexture));

    bricks.push_back(GameObject(-100.0, -100.0, 25.0, texDataStruct.brickTexture));
    bricks.push_back(GameObject(-100.0, -50.0, 25.0, texDataStruct.brickTexture));

    bulletTemplate = Bullet(-10, -10, 10.0, texDataStruct.bulletTexture);
    flameTemplate = Flame(-10.0, -10.0, texDataStruct.flameTexture);

	helpScreen = GameObject(320, 450);
    helpScreen.myTex = texDataStruct.helpScreenTexture;

	music = Mix_LoadMUS("data\\bandit_radio.wav");

	std::cout << "Game init done!" << std::endl;
	return true;
}

bool Game :: endGame()
{
	SDL_FreeSurface(screenSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_FreeMusic(music);

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

void Game :: mainLoop()
{
	bool exit = false;

	bool addBulletFlag = false;
	while (exit != true) {
        float prevPosX = player.posX;
        float prevPosY = player.posY;
		//game logic cycle

        //handle keyboard
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
        {

			const Uint8* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_UP])
            {
				player.moveObj(NORTH);
			}
			if (state[SDL_SCANCODE_DOWN])
            {
				player.moveObj(SOUTH);
			}
			if (state[SDL_SCANCODE_LEFT])
            {
				player.moveObj(WEST);
			}
			if (state[SDL_SCANCODE_RIGHT])
            {
				player.moveObj(EAST);
			}
			if (state[SDL_SCANCODE_SPACE])
            {
				if (!addBulletFlag)
				{
					addBulletFlag = player.weapon->trigger();
				}		
			}
			
			if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
				if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    exit = true;
                }
			}
		}

		player.weapon->act();

		if (addBulletFlag == true)
        {
			Bullet b = bulletTemplate;
			b.posX = player.posX;
			b.posY = player.posY;
			bullets.push_back(b);
			std::cout << "bullet added!";
			addBulletFlag = false;
		}

        std::vector<Enemy>::iterator enemyIt;
		std::vector<Bullet>::iterator bulletIt;
		std::vector<Flame>::iterator flameIt;
        std::vector<GameObject>::iterator bricksIt;
        
        // write previous positions of enemies
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).writePrevPositions();
        }

        //check collision with the wall
        for (bricksIt = bricks.begin(); bricksIt != bricks.end(); ++bricksIt)
        {
            if (collision(player, *bricksIt, RADIUS, RADIUS))
            {
                player.posX = prevPosX;
                player.posY = prevPosY;
            }
        }

        //handle bullets' actions
		unsigned int n;
		unsigned int i;
		n = bullets.size();

        for (bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++)
        {
            (*bulletIt).move();
            if ((*bulletIt).lifeCycle > BULLET_LIFE)
            {
                (*bulletIt).destroyed = true;
               
            }
        }

        //handle enemies' actions
		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {         
			for (bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
            {
                if ((*bulletIt).destroyed == true) continue;
                if (collision(*enemyIt, *bulletIt, RADIUS, RADIUS))
                {
					//add flame
					Flame f = flameTemplate;

					f.posX = (*enemyIt).posX + 10;
					f.posY = (*enemyIt).posY + 10;

					flames.push_back(f);

					f = flameTemplate;

					f.posX = (*enemyIt).posX - 15;
					f.posY = (*enemyIt).posY + 3;

					flames.push_back(f);

					f = flameTemplate;

					f.posX = (*enemyIt).posX;
					f.posY = (*enemyIt).posY - 7;

					flames.push_back(f);

                    (*enemyIt).energy -= 50;
                    (*bulletIt).destroyed = true;
				}             
			}
		}

        //handle flames' actions
		for (flameIt = flames.begin(); flameIt != flames.end(); ++flameIt)
        {
			(*flameIt).act();

			if ((*flameIt).lifeCycle > 15)
            {
				flames.erase(flameIt);
                
                if (flames.size() != 0)
                {
                    flameIt = flames.begin();
                }
                else
                {
                    break;
                }
			}
		}

        //handle enemies
        //erase enemies, who have energy below or equal 0
        //move enemies
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            if ((*enemyIt).energy <= 0)
            {
                enemies.erase(enemyIt);
                if (enemies.size() != 0)
                {
                    enemyIt = enemies.begin();  
                }
                else
                {
                    break;
                }
            }
            (*enemyIt).follow(player);
        }

        // handle enemies' collisions
        unsigned int j;
        for (i = 0; i < enemies.size(); i++)
        {
            for (j = 0; j < enemies.size(); j++)
            {
                if (i == j) continue;

                bool res = collision(enemies[i], enemies[j],
                    BoundsType::RADIUS, BoundsType::RADIUS);

                if (res == true)
                {
                    enemies[i].posX = enemies[i].prevPosX;
                    enemies[i].posY = enemies[i].prevPosY;
                }
            }
        }

        // delete bullets which have been destroyed
        for (bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
        {
            if ((*bulletIt).destroyed == true)
            {
                bullets.erase(bulletIt);
                if (bullets.size() != 0)
                {
                    bulletIt = bullets.begin();
                }
                else
                {
                    break;
                }
                std::cout << "Deleted bullet" << std::endl;
            }
            
        }

		//display
		SDL_RenderClear(renderer);

        tex->render(renderer, 0, 0, RENDER_IN_CENTER);
        
		terrain.myTex.render(renderer,
            (int)terrain.posX,
            (int)terrain.posY,
            RENDER_IN_CENTER);
     
		player.myTex.render(renderer,
            getPosXOnScreen(player.posX),
            getPosYOnScreen(player.posY),
            RENDER_IN_CENTER);

		for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
			(*enemyIt).myTex.render(renderer,
                getPosXOnScreen((*enemyIt).posX),
                getPosYOnScreen((*enemyIt).posY),
                RENDER_IN_CENTER);
		}

		for (bulletIt = bullets.begin();bulletIt != bullets.end(); ++bulletIt) {
			(*bulletIt).myTex.render(renderer,
                getPosXOnScreen((*bulletIt).posX),
                getPosYOnScreen((*bulletIt).posY),
                RENDER_IN_CENTER);
		}

		for (flameIt = flames.begin(); flameIt != flames.end(); ++flameIt) {
			Flame &flame = (*flameIt);
			flame.myTex.renderAnim(renderer,
                getPosXOnScreen(flame.posX),
                getPosYOnScreen(flame.posY),
                RENDER_IN_CENTER, 5, flame.texFrame);
		}

        for (bricksIt = bricks.begin(); bricksIt != bricks.end(); ++bricksIt) {
            (*bricksIt).myTex.render(renderer,
                getPosXOnScreen((*bricksIt).posX),
                getPosYOnScreen((*bricksIt).posY),
                RENDER_IN_CENTER);
        }
 
		helpScreen.myTex.render(renderer,
            (int)helpScreen.posX, 
            (int)helpScreen.posY,
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
