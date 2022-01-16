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
#include "Crate.h"
#include "ObjectAdder.h"
#include "game_settings.h"

class Level
{
public:
    // game
    Game& game;
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
    GameObject grassTemplate;
    Crate crateTemplate;
    GameObject lake;
    GameObject woodenHouse;
    Bullet machineGunBulletTemplate;

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
    std::vector<GameObject> groundTiles;
    std::vector<Crate> crates;
    std::vector<MyTextGameObject*> textObjects;

    Level(Game& g);

    bool initLevel();
    void runMainLoop();
    void handleEnemyCollision();
    void handleCrateAdderActions(CrateAdder &crateAdder);
    void handleCoinAdderActions(CoinAdder &coinAdder);
    void handlePlayerInput(bool &exit, bool &addBulletFlag, bool &addBombFlag);
    void cleanup();

private:
    void updatePlayerPositionOnCollision(float prevX, float prevY);
    void cleanupLevelObjects();
    void updateLevelDisplay();
    void initGroundTiles(MyTexture* texture);
};
