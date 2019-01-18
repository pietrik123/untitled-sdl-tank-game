#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

/**
 * \c Wrapper for \c SDL_Texture.
 * Can load a texture from file or create a texture out of \c std::string, using \c TTF_Font.
 */
class MyTexture
{
public:
    /**
     * RenderMode enumeration.
     * 
     */
    enum RenderMode
    {
        RENDER_IN_CORNER = 1,
        RENDER_IN_CENTER = 2
    };

    SDL_Texture* sdlTexture;

    /**
     * Default constructor - creates object with no texture data (NULL).
     */
    MyTexture();

    /**
     * Constructor - creates concrete texture object.
     * \param renderer
     * \param fileName - texture filename (path + filename)
     */
    MyTexture(SDL_Renderer* renderer, std::string fileName);

    /**
     * Destructor.
     */
    virtual ~MyTexture();

    /**
     * Loads a texture, which represents a text.
     * \param text a text to be displayed
     * \param color a color of the \c text
     * \param renderer
     * \param ttfFont a font to be used
     */
    bool MyTexture::loadTextTexture(const std::string& text, const SDL_Color& color, SDL_Renderer* renderer, TTF_Font* ttfFont);

    /**
     * Renders texture on \c renderer.
     * \param x target coordinate
     * \param y target coordinate
     * \mode
     */
    void render(SDL_Renderer* renderer, int x, int y, RenderMode mode);

    /**
     * Renders a rotated texture on \c renderer.
     * \param x target coordinate
     * \param y target coordinate
     * \param mode
     * \param angle - angle in radians
     */
    void render(SDL_Renderer* renderer, int x, int y, RenderMode mode, float angle);

    /**
    * Renders an animated texture on \c renderer.
    * \param x coordinate
    * \param y coordinate
    * \param mode
    * \param numOfFrames - number in, which is texture divided
    * \frameIndex - index of frame, which is to be displayed
    * Texture is divided into tiles. Tiles stay along each other in X direction.
    *
    */
    void renderAnim(SDL_Renderer* renderer, int x, int y, RenderMode mode, int numOfFrames, int frameIndex);
};