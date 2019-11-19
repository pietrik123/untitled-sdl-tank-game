#pragma once

#include <string>

class MyTexture;
class Game;
struct SDL_Color;
struct SDL_Renderer;

struct _TTF_Font;
typedef _TTF_Font TTF_Font;
/**
 * Represents a text texture.
 */
class MyText
{
public:
    /**
     * Saved text.
     */
    std::string text;
    MyTexture* texture;

    /**
     * Constructs dummy text object with '-' start value.
     * \param renderer
     * \param font a font to be used
     * \param color a color to be used
     */
    MyText(SDL_Renderer* renderer, TTF_Font* font, const SDL_Color& color);

    MyText(std::string aTextString, SDL_Renderer * renderer, TTF_Font* font, const SDL_Color& color);

    /**
     * Frees memory taken by \c MyTexture and \c SDL_Texture. 
     */
    ~MyText();

    /**
     * Prints text on game screen.
     * \param newText a text to be displayed.
     * \param x X screen coordinate for text texture
     * \param y Y screen coordinate for text texture
     * \param renderer
     * \param font
     * \param newColor
     */
    void printText(std::string newText, int x, int y,
        SDL_Renderer* renderer, TTF_Font* font, const SDL_Color& newColor);
};

class MyTextGameObject
{
public:
    MyText* text;
public:
    float posX;
    float posY;
    bool isToRemove;
    unsigned int currentLifeCycle;
    unsigned int maxLifeCycle;
    MyTextGameObject(MyText* text, float x, float y, unsigned int aMaxLifeCycle = 10);
    ~MyTextGameObject();
    void display(Game* game, SDL_Renderer * renderer, TTF_Font * font, const SDL_Color & color);
};