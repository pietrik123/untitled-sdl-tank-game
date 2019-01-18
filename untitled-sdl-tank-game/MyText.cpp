#include "MyText.h"
#include "MyTexture.h"

MyText::MyText(SDL_Renderer* renderer, TTF_Font* font, const SDL_Color& color)
{
    texture = new MyTexture;
    text = "-";

    texture->loadTextTexture(text, color, renderer, font);
}

void MyText::printText(std::string newText, int x, int y,
    SDL_Renderer* renderer, TTF_Font* font, const SDL_Color& color)
{
    // When \c text(stored text) is not equal \c newText, then
    // load new texture.Else do not load a new texture, just render old one.
    if (newText != text)
    {
        text = newText;
        SDL_DestroyTexture(texture->sdlTexture);
        texture->loadTextTexture(text, color, renderer, font);
    }

    texture->render(renderer, x, y, MyTexture::RENDER_IN_CENTER);
}

MyText::~MyText()
{
    SDL_DestroyTexture(texture->sdlTexture);
    delete texture;
}

