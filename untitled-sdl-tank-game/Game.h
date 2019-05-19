#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Flame.h"
#include "Bomb.h"
#include "menu.h"
#include "HUD.h"
#include "MyTexture.h"
#include "MyText.h"
#include "PatrollingEnemy.h"

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#include<vector>
#include "game_settings.h"


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
    MyTexture bombInfo;
    MyTexture cannonInfo;
    MyTexture someText;
    MyTexture treeTexture;
    MyTexture treeTexture2;
    MyTexture coinTexture;
    MyTexture sparkTexture;
};

class Game
{
public:
    // SDL fields
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* screenSurface;
    TTF_Font* ttfFont;

    // music
    Mix_Music *music;

    // GUI (menu etc.)
    GameMenu gameMenu;
    HUD hud;    

    // text
    MyText* someText;

    // game objects
    GameObject terrain;
    Player player;	

    // copyable objects
    Bullet bulletTemplate;
    Flame flameTemplate;
    Bomb bombTemplate;
    GameObject coinTemplate;
    GameObject sparkTemplate;

    // groups of objects
    std::vector<Enemy> enemies;
	std::vector<PatrollingEnemy> patrollingEnemies;
    std::vector<Bullet> bullets;
    std::vector<Flame> flames;
    std::vector<GameObject> bricks;
    std::vector<Bomb> bombs;
    std::vector<GameObject> trees;
    std::vector<GameObject> coins;
    std::vector<GameObject> sparks;
    
    // texture struct	
    TextureDataStruct texDataStruct;

    // other

    int screenWidth;
    int screenHeight;

    float scaleX; // screen_dx/world_dx
    float scaleY; // screen_dy/world_dy

    unsigned long int mainLoopCnt = 0;

    // constructors and destructors

    Game();
    ~Game();

    // public methods

    bool initSDL();

    void loadTextures();
    void createGameMenu();
    bool initGame();
    void mainLoop();
    bool runGame();	
    bool endGame();

    void printText(std::string text, int x, int y);
    
    // utils

    /**
     * get X coord in screen axis system
     * \param localPosX - x coord in local axis system
     */
    int getPosXOnScreen(float localPosX);
    /**
     * get Y coord in screen axis system
     * \param localPosX - y coord in local axis system
     */
    int getPosYOnScreen(float localPosY);
};

