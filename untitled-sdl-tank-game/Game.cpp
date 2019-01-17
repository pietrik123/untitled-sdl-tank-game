#include "Game.h"

#include <iostream>
#include <algorithm>

Game::Game() : window(NULL), renderer(NULL), screenSurface(NULL),
    music(NULL)
{
    std::cout << "Game started!" << std::endl;

    renderer = NULL;
    screenSurface = NULL;

    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;

    scaleX = 1.0;
    scaleY = 1.0;
}

bool isEnemyDestroyed(const Enemy &e)
{
    return e.energy <= 0;
}

bool isFlameCycleOver(const Flame &f)
{

    return f.lifeCycle > f.maxLifeCycle;
}

bool isBulletDestroyed(const Bullet &b)
{
    return b.destroyed;
}

bool isBombExploded(const Bomb &b)
{
    return b.exploded;
}

Game::~Game() 
{
    std::cout << "Game finished!" << "\n";
}

bool Game::initSDL()
{
    bool result = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
        result = false;
        std::cout << "Error: " << SDL_GetError() << "\n";
    }
    else
    {
        window = SDL_CreateWindow("Ziemniak", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            result = false;
            std::cout << "Error in window creation: " << SDL_GetError() << "\n";
        }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                result = false;
                std::cout << "Error in IMG init creation: " << SDL_GetError() << "\n";
            }
            
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);             
            if (renderer == NULL)
            {
                result = false;
                std::cout << "Error in SDL renderer creation: " << SDL_GetError() << "\n";
            }
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            if (TTF_Init() == -1)
            {
                result = false;
                std::cout << "Error in SDL font creation: " << SDL_GetError() << "\n";
            }
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Error in audio setup\n";
        return result;
    }

    return result;
}

void Game::loadTextures()
{
    // load textures

    texDataStruct.terrainTex = MyTexture(renderer, "data\\gfx\\terrain.png");

    //tex = new MyTexture(renderer, "data\\gfx\\terrain.png");

    texDataStruct.playerTexture = MyTexture(renderer, "data\\gfx\\player.png");
    texDataStruct.enemyTexture = MyTexture(renderer, "data\\gfx\\enemy.png");
    texDataStruct.brickTexture = MyTexture(renderer, "data\\gfx\\brick.png");
    texDataStruct.bulletTexture = MyTexture(renderer, "data\\gfx\\bullet.png");
    texDataStruct.flameTexture = MyTexture(renderer, "data\\gfx\\flame.png");
    texDataStruct.helpScreenTexture = MyTexture(renderer, "data\\gfx\\help.png");
    texDataStruct.bombTexture = MyTexture(renderer, "data\\gfx\\bomb.png");
    texDataStruct.cannonInfo = MyTexture(renderer, "data\\gfx\\hud\\basic_cannon_hud.png");
    texDataStruct.bombInfo = MyTexture(renderer, "data\\gfx\\hud\\bomb_hud.png");
    texDataStruct.someText = MyTexture();
    texDataStruct.treeTexture = MyTexture(renderer, "data\\gfx\\tree1.png");
    texDataStruct.treeTexture2 = MyTexture(renderer, "data\\gfx\\tree2.png");
}

void Game::createGameMenu()
{
    MenuItem newGameItem;
    MenuItem quitGameItem;

    MenuWindow mainMenuWindow;

    newGameItem.setItem(renderer, "new_game", "data\\gfx\\menu\\new_game_item.png");
    quitGameItem.setItem(renderer, "quit_game", "data\\gfx\\menu\\quit_item.png");

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
}

bool Game::initGame()
{
    // creating menu
    createGameMenu();

    // loading textures
    loadTextures();

    //game init
    //terrain = GameObject(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, texDataStruct.terrainTex);
    terrain = GameObject(0, 0, &texDataStruct.terrainTex);
    player = Player(100.0, 100.0, 25.0, &texDataStruct.playerTexture);
    hud = HUD(&texDataStruct.helpScreenTexture, &texDataStruct.bombInfo, &texDataStruct.cannonInfo);

    enemies.push_back(Enemy(-50.0, -100.0, 25.0, &texDataStruct.enemyTexture));
    enemies.push_back(Enemy(50.0, 50.0, 25.0, &texDataStruct.enemyTexture));

    bricks.push_back(GameObject(-100.0, -100.0, 25.0, &texDataStruct.brickTexture));
    bricks.push_back(GameObject(-100.0, -50.0, 25.0, &texDataStruct.brickTexture));

    trees.push_back(GameObject(35.0, 75.0, 25.0, &texDataStruct.treeTexture));
    trees.push_back(GameObject(-75.0, 0.0, 25.0, &texDataStruct.treeTexture2));

    bulletTemplate = Bullet(-10, -10, 10.0, &texDataStruct.bulletTexture);
    flameTemplate = Flame(-10.0, -10.0, &texDataStruct.flameTexture);
    bombTemplate = Bomb(-10.0, -10.0, &texDataStruct.bombTexture);

    music = Mix_LoadMUS("data\\bandit_radio.wav");

    ttfFont = TTF_OpenFont("data\\cour.ttf", 28);
    if (ttfFont == NULL)
    {
        std::cout << "Error in opening *.ttf file.\n";
    }

    SDL_Color color = { 200, 200, 200, 255 };
    texDataStruct.someText.loadTextTexture("Hello Mr Ziemniak", color, renderer, ttfFont);

    std::cout << "Game init done!" << std::endl;
    return true;
}

bool Game::endGame()
{
    SDL_FreeSurface(screenSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyTexture(texDataStruct.terrainTex.texture);
    SDL_DestroyTexture(texDataStruct.playerTexture.texture);
    SDL_DestroyTexture(texDataStruct.enemyTexture.texture);
    SDL_DestroyTexture(texDataStruct.brickTexture.texture);
    SDL_DestroyTexture(texDataStruct.bulletTexture.texture);
    SDL_DestroyTexture(texDataStruct.flameTexture.texture);
    SDL_DestroyTexture(texDataStruct.helpScreenTexture.texture);
    SDL_DestroyTexture(texDataStruct.bombTexture.texture);
    SDL_DestroyTexture(texDataStruct.someText.texture);
    SDL_DestroyTexture(texDataStruct.treeTexture.texture);
    SDL_DestroyTexture(texDataStruct.treeTexture2.texture);

    TTF_CloseFont(ttfFont);
    Mix_FreeMusic(music);

    TTF_Quit();
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

void Game::mainLoop()
{
    bool exit = false;

    bool addBulletFlag = false;
    bool addBombFlag = false;
    Direction bulletStartDir = EAST;

    std::vector<Enemy>::iterator enemyIt;
    std::vector<Bullet>::iterator bulletIt;
    std::vector<Bomb>::iterator bombIt;
    std::vector<Flame>::iterator flameIt;
    std::vector<GameObject>::iterator bricksIt;

    while (exit != true) {
        float prevPosX = player.posX;
        float prevPosY = player.posY;

        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).prevPosX = (*enemyIt).posX;
            (*enemyIt).prevPosY = (*enemyIt).posY;
        }
        //game logic cycle

        //handle keyboard
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
                    
            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    exit = true;
                }
            }

            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_n)
                {
                    player.weaponIndex++;
                    if (player.weaponIndex > player.weapons.size() - 1)
                    {
                        player.weaponIndex = 0;
                        //exit = true;
                    }
                    std::cout << "player weapon index : " << player.weaponIndex << "\n";
                }
            }
        }
        
        //std::cout << "event loop ... cycle\n";
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_UP])
        {
            std::cout << "up pressed ... \n";
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
            switch (player.weaponIndex)
            {
            case WeaponId::BASIC_CANNON:

                // this if statement is because of event loop race condition
                if (!addBulletFlag)
                {
                    addBulletFlag = player.getCurrentWeapon()->trigger();
                }
                std::cout << "add bullet flag: " << addBulletFlag << "\n";
                break;
            case WeaponId::BOMB_DROP:
                if (!addBombFlag)
                {
                    addBombFlag = player.getCurrentWeapon()->trigger();
                }
                break;
            default:
                break;
            }
        }

        if (addBulletFlag == true)
        {
            bulletStartDir = EAST;
            if (state[SDL_SCANCODE_LEFT])
            {
                bulletStartDir = WEST;
            }
            else if (state[SDL_SCANCODE_DOWN])
            {
                bulletStartDir = SOUTH;
            }
            else if (state[SDL_SCANCODE_UP])
            {
                bulletStartDir = NORTH;
            }
        }

        player.getCurrentWeapon()->act();
        
        if (addBulletFlag == true)
        {
            std::cout << "add bullet flag: " << addBulletFlag << "\n";
            Bullet b = bulletTemplate;
            b.posX = player.posX;
            b.posY = player.posY;
            b.direction = bulletStartDir;
            bullets.push_back(b);
            std::cout << "bullet added!";
            addBulletFlag = false;
        }

        if (addBombFlag == true)
        {
            Bomb b = bombTemplate;
            b.posX = player.posX;
            b.posY = player.posY;
            bombs.push_back(b);
            std::cout << "bomb added!";
            addBombFlag = false;
        }

        std::vector<Enemy>::iterator enemyIt;
        std::vector<Bullet>::iterator bulletIt;
        std::vector<Bomb>::iterator bombIt;
        std::vector<Flame>::iterator flameIt;
        std::vector<GameObject>::iterator bricksIt;
        std::vector<GameObject>::iterator treesIt;
               
        // write previous positions of enemies
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).writePrevPositions();
        }

        //check player collision with the wall
        for (bricksIt = bricks.begin(); bricksIt != bricks.end(); ++bricksIt)
        {
            if (collision(player, *bricksIt, RADIUS, RADIUS))
            {
                player.posX = prevPosX;
                player.posY = prevPosY;
            }
        }

        //check player collision with trees
        for (treesIt = trees.begin(); treesIt != trees.end(); ++treesIt)
        {
            if (collision(player, *treesIt, RADIUS, RADIUS))
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

        //handle bombs actions
        for (bombIt = bombs.begin(); bombIt != bombs.end(); ++bombIt)
        {
            (*bombIt).act();
        }

        //handle bullet hits
        //add flames
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

            for (bombIt = bombs.begin(); bombIt != bombs.end(); ++bombIt)
            {
                if (isBombExploded(*bombIt))
                {
                    Flame f = flameTemplate;
                    f.posX = (*bombIt).posX + 0;
                    f.posY = (*bombIt).posY + 8;
                    flames.push_back(f);

                    f = flameTemplate;
                    f.posX = (*bombIt).posX + (-5);
                    f.posY = (*bombIt).posY + (-4);
                    flames.push_back(f);

                    f = flameTemplate;
                    f.posX = (*bombIt).posX + 5;
                    f.posY = (*bombIt).posY + (-4);
                    flames.push_back(f);

                    if (getDistance(*enemyIt, *bombIt) <= (*bombIt).explosionRadius)
                    {
                        (*enemyIt).energy -= 200;
                    }
                }
            }
        }

        //handle flames' actions
        for (flameIt = flames.begin(); flameIt != flames.end(); ++flameIt)
        {
            (*flameIt).act();
        }

        flames.erase(
            std::remove_if(flames.begin(), flames.end(), isFlameCycleOver),
            flames.end());

        //handle enemies
        //move enemies
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).follow(player);
        }

        //check enemy collision with the wall
        for (bricksIt = bricks.begin(); bricksIt != bricks.end(); ++bricksIt)
        {
            for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
            {
                if (collision(*enemyIt, *bricksIt, RADIUS, RADIUS))
                {
                    (*enemyIt).posX = (*enemyIt).prevPosX;
                    (*enemyIt).posY = (*enemyIt).prevPosY;
                }
            }
        }

        //erase enemies, who have energy below or equal 0
        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(), isEnemyDestroyed),
            enemies.end());
        

        // handle enemies' collisions
        unsigned int j;
        for (i = 0; i < enemies.size(); i++)
        {
            enemies[i].collided = false;
            for (j = 0; j < enemies.size(); j++)
            {
                if (i == j) continue;

                bool res = collision(enemies[i], enemies[j],
                    BoundsType::RADIUS, BoundsType::RADIUS);

                if (res == true)
                {
                    enemies[i].posX = enemies[i].prevPosX;
                    enemies[i].posY = enemies[i].prevPosY;
                    enemies[i].collided = true;
                }
            }
        }

        // delete bullets which have been destroyed
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), isBulletDestroyed),
            bullets.end());

        // delete bullets which have been destroyed
        bombs.erase(
            std::remove_if(bombs.begin(), bombs.end(), isBombExploded),
            bombs.end());

        // write previous positions of enemies
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).writePrevPositions();
        }


        //display
        SDL_RenderClear(renderer);

        //tex->render(renderer, 0, 0, RENDER_IN_CENTER);
        
        terrain.display(renderer, this);

     
        for (bombIt = bombs.begin(); bombIt != bombs.end(); ++bombIt)
        {
            (*bombIt).display(renderer, this);
        }

        player.display(renderer, this);

        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
            (*enemyIt).display(renderer, this);
        }

        for (bulletIt = bullets.begin();bulletIt != bullets.end(); ++bulletIt) {
            (*bulletIt).myTex->render(renderer,
                getPosXOnScreen((*bulletIt).posX),
                getPosYOnScreen((*bulletIt).posY),
                MyTexture::RENDER_IN_CENTER,
                (*bulletIt).getDirectionAngle());

        }

        for (flameIt = flames.begin(); flameIt != flames.end(); ++flameIt) {
            Flame &flame = (*flameIt);    
			flame.myTex->renderAnim(renderer,
                getPosXOnScreen(flame.posX),
                getPosYOnScreen(flame.posY),
                MyTexture::RENDER_IN_CENTER, 5, flame.texFrame);
        }

        for (bricksIt = bricks.begin(); bricksIt != bricks.end(); ++bricksIt) {
            (*bricksIt).display(renderer, this);
        }

        for (treesIt = trees.begin(); treesIt != trees.end(); ++treesIt) {
            (*treesIt).display(renderer, this);
        }

        hud.display(renderer, player);

        texDataStruct.someText.render(renderer, 200, 75, MyTexture::RENDER_IN_CENTER);

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
