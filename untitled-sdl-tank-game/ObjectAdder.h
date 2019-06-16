#pragma once

#include <vector>

class GameObject;

/**
 * Adds coins to the game scene. 
 */
class CoinAdder
{
public:
    /**
     * \param minNumberOfCoins minimal number of coins, which should be present in game scene
     */
    CoinAdder(int minNumOfCoins);

    /**
     * \param coins vector of coins
     * \param sparks vector of sparks - small animation of glowing shown on a coin
     * \param coinTemplate object, from which a new coin is created and later added to coins' vector
     * When called in game loop, it adds a coin to \c coins. It cares for that number of
     * coins is not smaller than \c minNumberOfCoinsInScene.
     * \param sparkTemplate object, from which a new spark is created
     */
    void act(std::vector<GameObject>& coins, std::vector<GameObject>& sparks, const GameObject& coinTemplate, const GameObject& sparkTemplate);

private:
    int minNumberOfCoinsInScene;

};

class CrateAdder
{

};
