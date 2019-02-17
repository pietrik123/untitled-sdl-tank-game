#include "EnemyAdder.h"
#include "Enemy.h"
#include "MyTexture.h"
#include "utils/utils.h"
#include "Player.h"

Uint32 timerCallback(Uint32 interval, void *param)
{
    bool* p = static_cast<bool*>(param);
    *p = true;
    return 0;
}

EnemyAdder::EnemyAdder(const Enemy& paramEnemyTemplate, int parammaxNumOfEnemies, const Player& paramPlayer)
    : enemyTemplate(paramEnemyTemplate), player(paramPlayer), maxNumOfEnemies(parammaxNumOfEnemies), timerElapsed(false)
{

    timerId = static_cast<int>(SDL_AddTimer(5000, timerCallback, &timerElapsed));
    if (timerId == 0)
    {
        std::cout << __FUNCTION__ << " : Error in adding a timer!\n";
    }
}

void EnemyAdder::run(std::vector<Enemy>& enemies)
{
    if ((static_cast<float>(enemies.size()) < maxNumOfEnemies) && (cnt >= 100))
    {
        Enemy e = enemyTemplate;

        Point playerPos;
        playerPos.PosX = player.posX;
        playerPos.PosY = player.posY;
        //std::cout << __FUNCTION__ << " : player : " << player.posX << " " << player.posY << "\n";

        Point newEnemyPosCandidate;
        newEnemyPosCandidate.PosX = 0.0;
        newEnemyPosCandidate.PosY = 0.0;

        // try to add an enemy, which is not colliding with the player
        bool isEnemyPositionSelected = false;
        for (int i = 0; i < 5; i++)
        {
            newEnemyPosCandidate.PosX = static_cast<float>(rand() % 300 - 150);
            newEnemyPosCandidate.PosY = static_cast<float>(rand() % 300 - 150);
            double dist = distanceFromPointToPoint(playerPos, newEnemyPosCandidate);
            //std::cout << __FUNCTION__ << " : dist : " << dist << "\n";
            if ( dist > 50.0)
            {               
                isEnemyPositionSelected = true;
                break;
            }
        }

        if (isEnemyPositionSelected)
        {
            e.posX = newEnemyPosCandidate.PosX;
            e.posY = newEnemyPosCandidate.PosY;
            enemies.push_back(e);
            cnt = 0;
        }
        else
        {
            std::cout << __FUNCTION__ << " : Could not add an enemy, not colliding with the player!\n";
        }       
    }

    if (cnt < 100)
    {
        cnt++;
    }

    if (timerElapsed)
    {

        std::cout << __FUNCTION__ << " : timer elapsed!\n";
        SDL_RemoveTimer(timerId);
        timerElapsed = false;
        timerId = SDL_AddTimer(2000, timerCallback, &timerElapsed);
        if (timerId == 0)
        {
            std::cout << __FUNCTION__ << " : Error in adding a timer!\n";
        }
    }
}