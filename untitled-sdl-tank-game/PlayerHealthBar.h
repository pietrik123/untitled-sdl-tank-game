#pragma once
#include <SDL.h>

class Player;

/*
 * Basic component for showing player's energy 
 */
class PlayerHealthBar
{
public:
    const Player& playerRef;

    PlayerHealthBar(const Player& p);
    virtual ~PlayerHealthBar();

    void display(int screenPosX, int screenPosY, SDL_Renderer* r, float scale);
};
