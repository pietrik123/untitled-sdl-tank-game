
#include <stdlib.h>

#include "ObjectAdder.h"
#include "GameObject.h"
#include "MyTexture.h"

CoinAdder::CoinAdder(int minNumberOfCoins)
{
    minNumberOfCoinsInScene = minNumberOfCoins;
}

void CoinAdder::act(std::vector<GameObject>& coins, std::vector<GameObject>& sparks, const GameObject& coinTemplate, const GameObject& sparkTemplate)
{
    if (coins.size() < minNumberOfCoinsInScene)
    {
        GameObject newCoin = coinTemplate;
        GameObject newSpark = sparkTemplate;

        // temporary hardcoded range of x and y positions' generation
        newCoin.posX = static_cast<float>(rand() % 400 - 200);
        newCoin.posY = static_cast<float>(rand() % 400 - 200);

        newSpark.posX = newCoin.posX + 5.0;
        newSpark.posY = newCoin.posY + 5.0;

        // get id of last spark in the list
        int lastSparkId = 0;
        if (sparks.size() > 0)
        {
            lastSparkId = sparks.back().id;
        }

        coins.push_back(newCoin);
        sparks.push_back(newSpark);
     
        sparks.back().id = lastSparkId + 1;

        // assign spark's id to coin's childId
        coins.back().childId = sparks.back().id;
    }
}