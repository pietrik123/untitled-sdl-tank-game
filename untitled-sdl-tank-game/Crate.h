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

class Crate : public GameObject
{
public:
    GoodsId packageContent;
    
    Crate();

    Crate(float x, float y, float parRadius, MyTexture* texture);

    bool giveABonusToAPlayer(Player& p, std::string& information);
};