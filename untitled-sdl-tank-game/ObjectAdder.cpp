
#include <stdlib.h>

#include "ObjectAdder.h"
#include "GameObject.h"
#include "MyTexture.h"

CoinAdder::CoinAdder(int minNumberOfCoins)
{
    minNumberOfCoinsInScene = minNumberOfCoins;
}

void CoinAdder::act(std::vector<GameObject>& coins, const GameObject& coinTemplate)
{
    if (coins.size() < minNumberOfCoinsInScene)
    {
        GameObject newCoin = coinTemplate;

        // temporary hardcoded range of x and y positions' generation
        newCoin.posX = static_cast<float>(rand() % 400 - 200);
        newCoin.posY = static_cast<float>(rand() % 400 - 200);

        coins.push_back(newCoin);
    }
}