#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

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

    SDL_Texture* texture;

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
     * Renders texture on \c renderer.
     * \x target coordinate
     * \y target coordinate
     * \mode
     */
    void render(SDL_Renderer* renderer, int x, int y, RenderMode mode);

    /**
    * Renders a rotated texture on \c renderer.
    * \x target coordinate
    * \y target coordinate
    * \mode
    * \angle - angle in radians
    */
    void render(SDL_Renderer* renderer, int x, int y, RenderMode mode, float angle);

    /**
    * Renders an animated texture on \c renderer.
    * \x coordinate
    * \y coordinate
    * \mode
    * \numOfFrames - number in, which is texture divided
    * \frameIndex - index of frame, which is to be displayed
    * Texure is divided into tiles. Tiles stay along each other in X direction.
    *
    */
    void renderAnim(SDL_Renderer* renderer, int x, int y, RenderMode mode, int numOfFrames, int frameIndex);
};