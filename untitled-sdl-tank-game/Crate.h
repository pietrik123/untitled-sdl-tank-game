#pragma once
#include "GameObject.h"
#include <map>
class Player;

enum GoodsId
{
    CANNON,
    BOMB,
    FIRST_AID_KIT
};

std::map<GoodsId, std::string> goodsIdWithDescription
{
    {CANNON, "Basic Cannon"},
    {BOMB, "Bombs"},
    {FIRST_AID_KIT, "First Aid Kit"}
};

class Crate : public GameObject
{
public:
    GoodsId packageContent;
    
    Crate();

    void giveABonusToAPlayer(Player& p);
};