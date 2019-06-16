
#include "PlayerHealthBar.h"
#include "Player.h"

PlayerHealthBar::PlayerHealthBar(const Player& p) : playerRef(p)
{

}

PlayerHealthBar::~PlayerHealthBar()
{

}

void PlayerHealthBar::display(int screenPosX, int screenPosY, SDL_Renderer* r, float scale)
{
    // green - remaining energy
    SDL_Rect rectRemEnergy;
    rectRemEnergy.x = screenPosX;
    rectRemEnergy.y = screenPosY;
    rectRemEnergy.w = static_cast<int>(playerRef.energy * 100 / playerRef.maxEnergy * scale);
    rectRemEnergy.h = static_cast < int>(10 * scale);

    // red - lost energy
    SDL_Rect rectLostEnergy;
    rectLostEnergy.x = rectRemEnergy.x + rectRemEnergy.w;
    rectLostEnergy.y = screenPosY;
    rectLostEnergy.w = static_cast<int>((playerRef.maxEnergy - playerRef.energy) * 100 / playerRef.maxEnergy * scale);
    rectLostEnergy.h = static_cast<int>(10 * scale);

    SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
    SDL_RenderFillRect(r, &rectRemEnergy);
   
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r, &rectLostEnergy);    
}