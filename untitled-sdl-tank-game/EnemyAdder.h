#pragma once

#include <vector>

class Player;
class Enemy;

class EnemyAdder
{
public:
    int maxNumOfEnemies;
    unsigned int cnt;
    const Player& player;
    const Enemy& enemyTemplate;
    bool timerElapsed;
    int timerId;

    EnemyAdder(const Enemy& paramEnemyTemplate, int paramMaxNumOfEnemies, const Player& paramPlayer);

    void run(std::vector<Enemy>& enemies);
};
