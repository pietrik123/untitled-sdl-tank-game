#include "Level.h"
#include "EnemyAdder.h"
#include "ObjectAdder.h"
#include "PlayerHealthbar.h"
#include "PatrollingEnemy.h"
#include "Game.h"

#include <algorithm>

void addFlame(const Flame& f, std::vector<Flame>& flames, float x, float y)
{
    Flame newFlame = f;
    newFlame.posX = x;
    newFlame.posY = y;
    flames.push_back(newFlame);
}

Level::Level(Game & g) : game(g)
{
    std::cout << __FUNCTION__ << " : creating level ...\n";
}

bool Level::initLevel()
{
    std::cout << "Init level\n";

    TextureDataStruct& texturesStruct = game.texDataStruct;
    SDL_Renderer* renderer = game.renderer;

    //game init
    terrain = GameObject(0, 0, &texturesStruct.terrainTex, {});

    std::vector<Circle> collisionCirclesOfLakeObject = {
        {50.0,  120.0, 32.0},
        {55.0,  73.0,  32.0},
        {47.0,  50.0,  32.0},
        {87.0,  55.0,  32.0},
        {120.0, 67.0,  32.0},
        {118.0, 122.0, 32.0},
        {131.0, 132.0, 32.0},
        {75.0,  150.0, 32.0},
        {96.0,  144.0, 32.0} };
    lake = GameObject(250.0, 250.0, &texturesStruct.lakeTexture, collisionCirclesOfLakeObject);
    woodenHouse = GameObject(-100.0, -400.0, 200.0, 200.0, &texturesStruct.woodenHouseTexture);
    player = Player(100.0, 100.0, 25.0, &texturesStruct.playerTexture);
    hud = HUD(&texturesStruct.helpScreenTexture, &texturesStruct.bombInfo, &texturesStruct.cannonInfo);

    enemies.push_back(Enemy(-50.0, -100.0, 25.0, &texturesStruct.enemyTexture));
    enemies.push_back(Enemy(50.0, 50.0, 25.0, &texturesStruct.enemyTexture));

    patrollingEnemies.push_back(PatrollingEnemy(0.0, 200.0, 0.0, & texturesStruct   .enemyTexture, { -100, 200.0 }, { -100, 200.0 }, { 100, 200.0 }, 100.0));

    bricks.push_back(GameObject(-100.0, -100.0, 25.0, &texturesStruct.brickTexture));
    bricks.push_back(GameObject(-100.0, -50.0, 25.0, &texturesStruct.brickTexture));

    trees.push_back(GameObject(35.0, 75.0, 25.0, &texturesStruct.treeTexture));
    trees.push_back(GameObject(-75.0, 0.0, 25.0, &texturesStruct.treeTexture2));

    initGrass();

    // create copyable objects

    bulletTemplate = Bullet(-10, -10, 10.0, & texturesStruct.bulletTexture);
    bulletTemplate.bulletDamage = 50;

    machineGunBulletTemplate = Bullet(-10, -10, 10.0, & texturesStruct.machineGunBulletTexture);
    machineGunBulletTemplate.bulletDamage = 10;

    flameTemplate = Flame(-10.0, -10.0, & texturesStruct.flameTexture, 5);
    bombTemplate = Bomb(-10.0, -10.0, & texturesStruct.bombTexture);
    coinTemplate = GameObject(-10.0, -10.0, & texturesStruct.coinTexture, {});
    sparkTemplate = GameObject(-10.0, -10.0, & texturesStruct.sparkTexture, 5);
    grassTemplate = GameObject(-10.0, -10.0, & texturesStruct.grassTexture, {});
    crateTemplate = Crate(-10.0, -10.0, 25.0, & texturesStruct.crateTexture);
    coinTemplate.radius = 12.0;

    // add some coins
    GameObject c = coinTemplate;
    c.posX = 80.0;
    c.posY = -50.0;

    game.music = Mix_LoadMUS("data\\bandit_radio.wav");

    game.ttfFont = TTF_OpenFont("data\\cour.ttf", 28);
    if (game.ttfFont == NULL)
    {
        std::cout << __FUNCTION__ << " : Error in opening *.ttf file.\n";
    }

    SDL_Color color = { 200, 200, 200, 255 };
    texturesStruct.someText.loadTextTexture("Hello Mr Ziemniak", color, renderer, game.ttfFont);

    someText = new MyText(renderer, game.ttfFont, { 127, 127, 127, 255 });

    std::cout << __FUNCTION__ << " : Game init done!" << std::endl;
    return true;
}


void Level::runMainLoop()
{
    SDL_Renderer* renderer = game.renderer;
    TextureDataStruct& texturesStruct = game.texDataStruct;
    TTF_Font* ttfFont = game.ttfFont;

    bool exit = false;

    bool addBulletFlag = false;
    bool addBombFlag = false;
    Direction bulletStartDir = EAST;

    std::vector<Enemy>::iterator enemyIt;
    std::vector<PatrollingEnemy>::iterator patrollingEnemyIt;
    std::vector<Bullet>::iterator bulletIt;
    std::vector<Bomb>::iterator bombIt;
    std::vector<Flame>::iterator flameIt;
    std::vector<GameObject>::iterator bricksIt;
    std::vector<GameObject>::iterator coinsIt;
    std::vector<MyTextGameObject*> textObjects;

    Enemy enemyTemplate(0.0f, 0.0f, 25.0f, &(texturesStruct.enemyTexture));
    EnemyAdder enemyAdder(enemyTemplate, 4, player);
    CoinAdder coinAdder(2);
    CrateAdder crateAdder(50, 3);
    MyText scoreText(renderer, ttfFont, { 127, 127, 127, 255 });
    MyText currentWeaponInfoText(renderer, ttfFont, { 127, 127, 127, 255 });

    int mainLoopCnt = 0;

    PlayerHealthBar healthBar(player);

    while (exit != true) {

        float prevPosX = player.posX;
        float prevPosY = player.posY;

        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            enemyIt->writePrevPositions();
        }

        for (patrollingEnemyIt = patrollingEnemies.begin(); patrollingEnemyIt != patrollingEnemies.end(); ++patrollingEnemyIt)
        {
            patrollingEnemyIt->writePrevPositions();
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
                    }
                }
            }
        }

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
            switch (player.weaponIndex)
            {
            case WeaponId::BASIC_CANNON:

                // this if statement is because of event loop race condition
                if (!addBulletFlag)
                {
                    addBulletFlag = player.getCurrentWeapon()->trigger();
                }
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

        if (state[SDL_SCANCODE_O])
        {
            std::cout << "debug key 'O' pressed\n";
        }

        if (state[SDL_SCANCODE_LEFT])
        {
            player.basicCannonShootingDirection = WEST;
        }
        else if (state[SDL_SCANCODE_RIGHT])
        {
            player.basicCannonShootingDirection = EAST;
        }
        else if (state[SDL_SCANCODE_DOWN])
        {
            player.basicCannonShootingDirection = SOUTH;
        }
        else if (state[SDL_SCANCODE_UP])
        {
            player.basicCannonShootingDirection = NORTH;
        }

        if (addBulletFlag == true)
        {
            bulletStartDir = player.basicCannonShootingDirection;
        }

        player.getCurrentWeapon()->act();

        static int tmpMachineGunAngleParam = 0;
        if (mainLoopCnt % 15 == 0)
        {
            Bullet b = machineGunBulletTemplate;
            b.posX = player.posX;
            b.posY = player.posY;
            b.setDirectionAngle(tmpMachineGunAngleParam * 10.0f);
            b.isFourDirMovementOnly = false;
            b.displcmnt = MACHINE_GUN_BULLET_SPEED;
            bullets.push_back(b);
            tmpMachineGunAngleParam += 1;
        }

        if (addBulletFlag == true)
        {
            Bullet b = bulletTemplate;
            b.posX = player.posX;
            b.posY = player.posY;
            b.direction = bulletStartDir;
            bullets.push_back(b);
            addBulletFlag = false;
        }

        if (addBombFlag == true)
        {
            Bomb b = bombTemplate;
            b.posX = player.posX;
            b.posY = player.posY;
            bombs.push_back(b);
            addBombFlag = false;
        }

        std::vector<Enemy>::iterator enemyIt;
        std::vector<Bullet>::iterator bulletIt;
        std::vector<Bomb>::iterator bombIt;
        std::vector<Flame>::iterator flameIt;
        std::vector<GameObject>::iterator bricksIt;
        std::vector<GameObject>::iterator treesIt;
        std::vector<GameObject>::iterator coinsIt;
        std::vector<GameObject>::iterator sparkIt;
        std::vector<GameObject>::iterator grassIt;
        std::vector<Crate>::iterator crateIt;

        // write previous positions of enemies
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).writePrevPositions();
        }

        // write previous positions of patrolling enemies

        for (patrollingEnemyIt = patrollingEnemies.begin(); patrollingEnemyIt != patrollingEnemies.end(); ++patrollingEnemyIt)
        {
            (*patrollingEnemyIt).writePrevPositions();
        }

        //check player collision with trees
        updatePlayerPositionOnCollision(prevPosX, prevPosY);

        //handle bullets' actions
        unsigned int n;
        unsigned int i;
        n = bullets.size();

        for (bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++)
        {
            (*bulletIt).move();
        }

        //handle bombs actions
        for (bombIt = bombs.begin(); bombIt != bombs.end(); ++bombIt)
        {
            (*bombIt).act();
        }

        // handle crates' actions
        for (crateIt = crates.begin(); crateIt != crates.end(); ++crateIt)
        {
            std::string bonusInfo;
            bool res = (*crateIt).giveABonusToAPlayer(player, bonusInfo);
            if (res == true)
            {
                textObjects.push_back(
                    new MyTextGameObject(new MyText(bonusInfo, renderer, ttfFont, { 255, 242, 0, 255 }), player.posX, player.posY, 20)
                );
            }
        }

        //handle flames' actions
        for (flameIt = flames.begin(); flameIt != flames.end(); ++flameIt)
        {
            (*flameIt).act();
        }

        //player actions
        player.act();

        flames.erase(
            std::remove_if(flames.begin(), flames.end(), Flame::isFlameCycleOver),
            flames.end());

        //handle enemies
        //move enemies
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).follow(player);
        }

        for (patrollingEnemyIt = patrollingEnemies.begin(); patrollingEnemyIt != patrollingEnemies.end(); ++patrollingEnemyIt)
        {
            (*patrollingEnemyIt).follow(player);
        }


        //check enemy collision with the wall and player
        for (bricksIt = bricks.begin(); bricksIt != bricks.end(); ++bricksIt)
        {
            for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
            {
                if (collision(*enemyIt, *bricksIt, RADIUS, RADIUS))
                {
                    (*enemyIt).posX = (*enemyIt).prevPosX;
                    (*enemyIt).posY = (*enemyIt).prevPosY;
                }

                if (collision(*enemyIt, player, RADIUS, RADIUS))
                {
                    if (player.afterHitCounter == 0)
                    {
                        player.afterHitCounter = 1;
                    }
                }
            }

            for (patrollingEnemyIt = patrollingEnemies.begin(); patrollingEnemyIt != patrollingEnemies.end(); ++patrollingEnemyIt)
            {
                if (collision(*patrollingEnemyIt, *bricksIt, RADIUS, RADIUS))
                {
                    (*patrollingEnemyIt).posX = (*patrollingEnemyIt).prevPosX;
                    (*patrollingEnemyIt).posY = (*patrollingEnemyIt).prevPosY;

                }

                if (collision(*patrollingEnemyIt, player, RADIUS, RADIUS))
                {
                    if (player.afterHitCounter == 0)
                    {
                        player.afterHitCounter = 1;
                    }
                }
            }
        }

        coinAdder.act(coins, sparks, coinTemplate, sparkTemplate);
        crateAdder.act(crates, crateTemplate);

        //erase enemies, who have energy below or equal 0
        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(), Enemy::isEnemyDestroyed),
            enemies.end());

        patrollingEnemies.erase(
            std::remove_if(patrollingEnemies.begin(), patrollingEnemies.end(), Enemy::isEnemyDestroyed),
            patrollingEnemies.end());

        for (coinsIt = coins.begin(); coinsIt != coins.end(); ++coinsIt)
        {
            if (collision(player, *coinsIt, RADIUS, RADIUS))
            {
                if ((*coinsIt).childId != 0)
                {
                    for (sparkIt = sparks.begin(); sparkIt != sparks.end(); ++sparkIt)
                    {
                        if ((*sparkIt).id == (*coinsIt).childId)
                        {
                            break;
                        }
                    }
                    (*sparkIt).isToRemove = true;
                }
                coins.erase(coinsIt);
                player.coinsCollected++;
                break;
            }
        }

        // delete sparks if coin is no longer there
        sparks.erase(
            std::remove_if(sparks.begin(), sparks.end(), GameObject::isObjectToRemove),
            sparks.end());

        for (crateIt = crates.begin(); crateIt != crates.end(); crateIt++)
        {
            if ((*crateIt).isToRemove)
            {
                crateAdder.numOfCratesCreated--;
            }
        }

        // delete crates if they had been picked up
        crates.erase(
            std::remove_if(crates.begin(), crates.end(), GameObject::isObjectToRemove),
            crates.end());


        // handle enemies' collisions
        std::vector<Enemy*> extendedEnemies;
        for (int i = 0; i < enemies.size(); ++i)
        {
            extendedEnemies.push_back(&enemies[i]);
        }
        for (int i = 0; i < patrollingEnemies.size(); ++i)
        {
            extendedEnemies.push_back(&patrollingEnemies[i]);
        }
        for (i = 0; i < extendedEnemies.size(); i++)
        {
            extendedEnemies[i]->collided = false;
            for (unsigned int j = 0; j < extendedEnemies.size(); j++)
            {
                if (i == j) continue;

                bool res = collision(*extendedEnemies[i], *extendedEnemies[j],
                    BoundsType::RADIUS, BoundsType::RADIUS);

                if (res == true)
                {
                    extendedEnemies[i]->posX = extendedEnemies[i]->prevPosX;
                    extendedEnemies[i]->posY = extendedEnemies[i]->prevPosY;
                    extendedEnemies[i]->collided = true;
                }
            }
        }

        for (std::vector<Enemy*>::iterator enemyIt = extendedEnemies.begin(); enemyIt != extendedEnemies.end(); ++enemyIt)
        {
            for (bulletIt = bullets.begin(); bulletIt != bullets.end(); ++bulletIt)
            {
                if ((*bulletIt).destroyed == true) continue;
                if (collision(**enemyIt, *bulletIt, RADIUS, RADIUS))
                {
                    //add flame

                    addFlame(flameTemplate, flames, (*enemyIt)->posX + 10, (*enemyIt)->posY + 10);
                    addFlame(flameTemplate, flames, (*enemyIt)->posX - 15, (*enemyIt)->posY + 3);
                    addFlame(flameTemplate, flames, (*enemyIt)->posX, (*enemyIt)->posY - 7);

                    (*enemyIt)->energy -= (*bulletIt).bulletDamage;
                    (*bulletIt).destroyed = true;
                }
            }

            for (bombIt = bombs.begin(); bombIt != bombs.end(); ++bombIt)
            {
                if (Bomb::isBombExploded(*bombIt))
                {

                    addFlame(flameTemplate, flames, bombIt->posX, bombIt->posY + 8);
                    addFlame(flameTemplate, flames, bombIt->posX - 5, bombIt->posY - 4);
                    addFlame(flameTemplate, flames, bombIt->posX + 5, bombIt->posY - 4);

                    if (getDistance(**enemyIt, *bombIt) <= (*bombIt).explosionRadius)
                    {
                        (*enemyIt)->energy -= 200;
                    }
                }
            }
        }


        // delete bullets which have been destroyed
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), Bullet::isBulletDestroyed),
            bullets.end());

        // delete bullets which have been destroyed
        bombs.erase(
            std::remove_if(bombs.begin(), bombs.end(), Bomb::isBombExploded),
            bombs.end());

        // write previous positions of enemies
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).writePrevPositions();
        }

        for (patrollingEnemyIt = patrollingEnemies.begin(); patrollingEnemyIt != patrollingEnemies.end(); ++patrollingEnemyIt)
        {
            (*patrollingEnemyIt).writePrevPositions();
        }

        //display
        SDL_RenderClear(renderer);

        // displaying background terrain
        terrain.myTex->render(renderer, 0, 0, MyTexture::RENDER_IN_CORNER);

        woodenHouse.display(renderer, &game);
        lake.display(renderer, &game);

        for (grassIt = grassTiles.begin(); grassIt != grassTiles.end(); ++grassIt)
        {
            (*grassIt).display(renderer, &game);
        }

        for (bombIt = bombs.begin(); bombIt != bombs.end(); ++bombIt)
        {
            (*bombIt).display(renderer, &game);
        }

        for (crateIt = crates.begin(); crateIt != crates.end(); ++crateIt)
        {
            (*crateIt).display(renderer, &game);
        }

        player.display(renderer, &game);

        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            (*enemyIt).display(renderer, &game);
        }

        for (patrollingEnemyIt = patrollingEnemies.begin(); patrollingEnemyIt != patrollingEnemies.end(); ++patrollingEnemyIt)
        {
            (*patrollingEnemyIt).display(renderer, &game);
        }


        for (bulletIt = bullets.begin();bulletIt != bullets.end(); ++bulletIt) {
            (*bulletIt).myTex->render(renderer,
                game.getPosXOnScreen((*bulletIt).posX),
                game.getPosYOnScreen((*bulletIt).posY),
                MyTexture::RENDER_IN_CENTER,
                (*bulletIt).getDirectionAngleForView());
        }

        for (flameIt = flames.begin(); flameIt != flames.end(); ++flameIt) {
            Flame &flame = (*flameIt);
            flame.displayAnimated(renderer, &game, 3);
        }

        for (sparkIt = sparks.begin(); sparkIt != sparks.end(); ++sparkIt) {
            GameObject &spark = (*sparkIt);
            spark.displayAnimated(renderer, &game, 3);
        }

        enemyAdder.run(enemies);

        for (bricksIt = bricks.begin(); bricksIt != bricks.end(); ++bricksIt) {
            (*bricksIt).display(renderer, &game);
        }

        for (treesIt = trees.begin(); treesIt != trees.end(); ++treesIt) {
            (*treesIt).display(renderer, &game);
        }

        for (coinsIt = coins.begin(); coinsIt != coins.end(); ++coinsIt) {
            (*coinsIt).display(renderer, &game);
        }


        for (std::vector<MyTextGameObject*>::iterator it = textObjects.begin(); it != textObjects.end(); ++it)
        {
            std::cout << "Texts" << " : ";
            (*it)->display(&game, renderer, ttfFont, { 255, 255, 255, 255 });
            std::cout << (*it)->text->text << " " << (*it)->posX << " " << (*it)->posY << "\n";
        }

        textObjects.erase(
            std::remove_if(textObjects.begin(), textObjects.end(), MyTextGameObject::isTextObjectToRemove),
            textObjects.end());

        healthBar.display(0, 0, renderer, 1.5);

        hud.display(renderer, player);

        // display as an example
        someText->printText("Player Energy", 115, 35, renderer, ttfFont, { 255, 255, 255, 255 });

        // display player's score (coins collected)
        scoreText.printText("score: " + std::to_string(player.coinsCollected), 75, 75,
            renderer, ttfFont, { 255, 255, 255, 255 });

        std::string weaponName;
        // TODO display weapon and ammo information
        if (player.weaponIndex == WeaponId::BASIC_CANNON)
        {
            weaponName = "Cannon";
        }
        else if (player.weaponIndex == WeaponId::BOMB_DROP)
        {
            weaponName = "Bomb";
        }

        currentWeaponInfoText.printText(weaponName + ":   " + std::to_string(player.getCurrentWeapon()->getAmmo()),
            280, 50, renderer, ttfFont, { 255, 255, 255 });

        SDL_RenderPresent(renderer);

        mainLoopCnt++;

        //wait
        SDL_Delay(50);
    }
}

void Level::cleanup()
{
    delete someText;
}

void Level::initGrass()
{
    TextureDataStruct& texturesStruct = game.texDataStruct;

    for (int i = 0; i < 15; i++)
    {
        float x = static_cast<float>(rand() % 1000 - 500);
        float y = static_cast<float>(rand() % 1000 - 500);
        grassTiles.push_back(GameObject(x, y, &texturesStruct.grassTexture, {}));
    }
}

void Level::updatePlayerPositionOnCollision(float prevPosX, float prevPosY)
{
    //check player collision with the wall
    for (std::vector<GameObject>::iterator bricksIt = bricks.begin(); bricksIt != bricks.end(); ++bricksIt)
    {
        if (collision(player, *bricksIt, RADIUS, RADIUS))
        {
            player.posX = prevPosX;
            player.posY = prevPosY;
        }
    }

    //check player collision with trees
    for (std::vector<GameObject>::iterator treesIt = trees.begin(); treesIt != trees.end(); ++treesIt)
    {
        if (collision(player, *treesIt, RADIUS, RADIUS))
        {
            player.posX = prevPosX;
            player.posY = prevPosY;
        }
    }

    if (collision(player, lake, RADIUS, MULTI_CIRCLE))
    {
        player.posX = prevPosX;
        player.posY = prevPosY;
    }

    if (collision(player, woodenHouse, RADIUS, RECTANGLE))
    {
        player.posX = prevPosX;
        player.posY = prevPosY;
    }
}

