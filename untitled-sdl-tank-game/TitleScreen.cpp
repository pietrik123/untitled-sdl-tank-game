
#include "TitleScreen.h"

TitleScreen::TitleScreen(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    titleTextX = 0.5 * screenWidth;
    heroX = 1.2 * screenWidth;
    heroFrame = 0;
    cnt = 0;
}

void TitleScreen::loop(SDL_Renderer* renderer)
{
    init(renderer);

    bool exit = false;
    while (exit == false)
    {
        if (cnt > 100)
        {
            exit = true;
        }

        // break on key event
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                exit = true;
                break;
            }
        }

        cnt++;

        // move hero
        heroX -= 0.02 * screenWidth;

        // change hero animation frame
        if (cnt % 10 == 0)
        {
            heroFrame += 1;
            if (heroFrame > 3) {
                heroFrame = 0;
            }
        }

        // display all
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 128, 192, 255);

        hero->renderAnim(renderer, heroX, 0.7 * screenHeight, MyTexture::RENDER_IN_CENTER, 4, heroFrame);
        titleTex->render(renderer, titleTextX, 0.3 * screenHeight, MyTexture::RENDER_IN_CENTER, 0.0);

        SDL_RenderPresent(renderer);

        // sleep 50ms
        SDL_Delay(50);
    }

    cleanup();
}

void TitleScreen::init(SDL_Renderer* renderer)
{
    titleTex = new MyTexture(renderer, "data\\gfx\\title\\title.png");
    hero = new MyTexture(renderer, "data\\gfx\\title\\mr_ziemniak.png");
}

void TitleScreen::cleanup()
{
    delete hero;
    delete titleTex;
}