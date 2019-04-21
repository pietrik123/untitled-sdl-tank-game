
#include "PlayerHealthBar.h"
#include "Player.h"

PlayerHealthBar::PlayerHealthBar(const Player& p) : playerRef(p)
{

}

PlayerHealthBar::~PlayerHealthBar()
{

}

void PlayerHealthBar::display(int screenPosX, int screenPosY, SDL_Renderer* r)
{
    // green - remaining energy
    SDL_Rect rectRemEnergy;
    rectRemEnergy.x = screenPosX;
    rectRemEnergy.y = screenPosY;
    rectRemEnergy.w = playerRef.energy * 100 / playerRef.maxEnergy;
    rectRemEnergy.h = screenPosY + 10;

    // red - lost energy
    SDL_Rect rectLostEnergy;
    rectLostEnergy.x = rectRemEnergy.x + rectRemEnergy.w;
    rectLostEnergy.y = screenPosY;
    rectLostEnergy.w = (playerRef.maxEnergy - playerRef.energy) * 100 / playerRef.maxEnergy;
    rectLostEnergy.h = screenPosY + 10;

    //SDL_SetRenderDrawColor(r, 34, 177, 76, 255);
    SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
    SDL_RenderFillRect(r, &rectRemEnergy);
   
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r, &rectLostEnergy);    
}