#include "MyText.h"
#include "MyTexture.h"
#include "Game.h"

MyText::MyText(SDL_Renderer* renderer, TTF_Font* font, const SDL_Color& color)
{
    texture = new MyTexture;
    text = "-";

    texture->loadTextTexture(text, color, renderer, font);
}

MyText::MyText(std::string aTextString, SDL_Renderer * renderer, TTF_Font* font, const SDL_Color& color)
{
    texture = new MyTexture;
    text = aTextString;

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

MyTextGameObject::MyTextGameObject(MyText* aText, float x, float y, unsigned int aMaxLifeCycle) : text(aText)
{
    currentLifeCycle = 0;
    posX = x;
    posY = y;
    maxLifeCycle = aMaxLifeCycle;
    isToRemove = false;
}

MyTextGameObject::~MyTextGameObject()
{
    std::cout << __FUNCTION__ << " : removing text\n";
    delete text;
}

void MyTextGameObject::display(Game* game, SDL_Renderer* renderer, TTF_Font* font, const SDL_Color& color)
{
    text->printText(text->text, 
        game->getPosXOnScreen(posX),
        game->getPosYOnScreen(posY),
        renderer, font, color);

    posY -= 2.0;

    currentLifeCycle++;
    if (currentLifeCycle > maxLifeCycle)
    {
        isToRemove = true;
    }
}

bool MyTextGameObject::isTextObjectToRemove(MyTextGameObject* o)
{
    bool res = o->isToRemove;
    if (res)
    {
        delete o;
    }
    return res;
}
