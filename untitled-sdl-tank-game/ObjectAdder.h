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
     * \param coinTemplate object, from which a new coin is created and later added to coins' vector
     * When called in game loop, it adds a coin to \c coins. It cares for that number of
     * coins is not smaller than \c minNumberOfCoinsInScene.
     */
    void act(std::vector<GameObject>& coins, const GameObject& coinTemplate);

private:
    int minNumberOfCoinsInScene;

};
