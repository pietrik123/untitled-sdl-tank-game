#pragma once

#include <vector>

class Player;
class Enemy;

class EnemyAdder
{
public:
    int maxNumOfEnemies;

    /**
     * enemies' counter
     */
    unsigned int cnt;

    /**
     * \c Player object reference
     */
    const Player& player;

    /**
     * \c Enemy object, which will be copied and added by \c EnemyAdder
     */
    const Enemy& enemyTemplate;
    bool timerElapsed;
    int timerId;

    /**
     * \param paramEnemyTemplate \c Enemy object which should be added
     * \param paramMaxNumOfEnemies
     * \param paramPlayer reference to \c Player object
     */
    EnemyAdder(const Enemy& paramEnemyTemplate, int paramMaxNumOfEnemies, const Player& paramPlayer);

    /**
     * this method should be executed in game main loop
     */
    void run(std::vector<Enemy>& enemies);
};
