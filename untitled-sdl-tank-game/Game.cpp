#include "Game.h"
#include "ObjectAdder.h"
#include "EnemyAdder.h"
#include "PlayerHealthBar.h"
#include "MyTexture.h"
#include "TitleScreen.h"
#include "game_settings.h"
#include "TextureDataStruct.h"

#include <iostream>
#include <algorithm>

Game::Game() : window(NULL), renderer(NULL), screenSurface(NULL), lev(NULL)
{
    std::cout << __FUNCTION__ << " : Game started!" << std::endl;

    renderer = NULL;
    screenSurface = NULL;

    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;

    scaleX = 1.0;
    scaleY = 1.0;
}

Game::~Game()
{
    std::cout << __FUNCTION__ << " : Game finished!" << "\n";
}

bool Game::initSDL()
{
    bool result = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 )
    {
        result = false;
        std::cout << __FUNCTION__ << " : Error: " << SDL_GetError() << "\n";
    }
    else
    {
        window = SDL_CreateWindow("Ziemniak", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (window == NULL)
        {
            result = false;
            std::cout << __FUNCTION__ << " : Error in window creation: " << SDL_GetError() << "\n";
        }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                result = false;
                std::cout << __FUNCTION__ << " : Error in IMG init creation: " << SDL_GetError() << "\n";
            }
            
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);             
            if (renderer == NULL)
            {
                result = false;
                std::cout << __FUNCTION__ << " : Error in SDL renderer creation: " << SDL_GetError() << "\n";
            }
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            if (TTF_Init() == -1)
            {
                result = false;
                std::cout << __FUNCTION__ << " : Error in SDL font creation: " << SDL_GetError() << "\n";
            }
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << __FUNCTION__ << " : Error in audio setup\n";
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
    texDataStruct.coinTexture = MyTexture(renderer, "data\\gfx\\coin.png");
    texDataStruct.sparkTexture = MyTexture(renderer, "data\\gfx\\spark.png");
    texDataStruct.grassTexture = MyTexture(renderer, "data\\gfx\\grass2.png");
    texDataStruct.crateTexture = MyTexture(renderer, "data\\gfx\\crate.png");
    texDataStruct.lakeTexture = MyTexture(renderer, "data\\gfx\\lake.png");
    texDataStruct.woodenHouseTexture = MyTexture(renderer, "data\\gfx\\wooden_house.png");
    texDataStruct.machineGunBulletTexture = MyTexture(renderer, "data\\gfx\\tower_bullet.png");
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
        std::cout << __FUNCTION__ << "Error in game menu validation!" << "\n";
        exit(EXIT_FAILURE);
    }
}

bool Game::initGame()
{
    // creating menu
    createGameMenu();

    // loading textures
    loadTextures();

    return lev->initLevel();
}

bool Game::endGame()
{
    SDL_FreeSurface(screenSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyTexture(texDataStruct.terrainTex.sdlTexture);
    SDL_DestroyTexture(texDataStruct.playerTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.enemyTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.brickTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.bulletTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.flameTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.helpScreenTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.bombTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.someText.sdlTexture);
    SDL_DestroyTexture(texDataStruct.treeTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.treeTexture2.sdlTexture);
    SDL_DestroyTexture(texDataStruct.coinTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.sparkTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.grassTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.crateTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.lakeTexture.sdlTexture);
    SDL_DestroyTexture(texDataStruct.woodenHouseTexture.sdlTexture);

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

    TitleScreen t(screenWidth, screenHeight);
    t.loop(renderer);

    //put all functions here
    int res = gameMenu.gameMenuLoop(renderer);

    //play music
    /*if (Mix_PlayingMusic() == 0)
    { 
        Mix_PlayMusic( music, -1 );
    }*/

    if (res == START_GAME)
    {
        lev->runMainLoop();
    }
    else if (res == QUIT_GAME)
    {
        //quit game
    }
    lev->cleanup();
    return true;
}

int Game::getPosXOnScreen(float localPosX)
{
	float posXinPlayerAxisSystem = localPosX - lev->player.posX;
	return static_cast<int>(scaleX * posXinPlayerAxisSystem + Game::screenWidth / 2.0);
}

int Game::getPosYOnScreen(float localPosY)
{
    float posYinPlayerAxisSystem = localPosY - lev->player.posY;
    return static_cast<int>(-scaleY * posYinPlayerAxisSystem + Game::screenHeight / 2.0);
}

void Game::setLevel(Level* l)
{
    lev = l;
}
