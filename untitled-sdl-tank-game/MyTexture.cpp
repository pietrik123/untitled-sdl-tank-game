#include "MyTexture.h"

#include <iostream>

MyTexture::MyTexture()
{
	texture = NULL;
	std::cout << "MyTexture::MyTexture() : Empty texture created!" << std::endl;
}

MyTexture :: MyTexture(SDL_Renderer* renderer, std::string fileName)
{

	SDL_Surface* textureSurface = NULL;

	textureSurface = IMG_Load(fileName.c_str());
	if (textureSurface == NULL)
    {
		std::cout << "MyTexture::MyTexture() : Error: " << SDL_GetError() << std::endl;
	}

	SDL_SetColorKey(textureSurface, SDL_TRUE, SDL_MapRGB(textureSurface->format, 0xFF, 0x00, 0xFF));

	texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
	if (texture == NULL)
    {
		std::cout << "MyTexture::MyTexture() : Error: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(textureSurface);
	std::cout << "MyTexture::MyTexture() : Texture created!" << std::endl;
}

MyTexture :: ~MyTexture()
{
    // TODO this needs to be thought over.
    // For now destroying texture results in segmentation faults.
	// SDL_DestroyTexture(texture);
	std::cout << "MyTexture::~MyTexture() : Destructor called!" << std::endl;
}

void MyTexture::render(SDL_Renderer* renderer, int x, int y, RenderMode mode)
{
	SDL_Rect rect;

	int w, h;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	if (mode == RENDER_IN_CENTER)
    {
		rect.x = x - w / 2;
		rect.y = y - h / 2;
	}
	else if (mode == RENDER_IN_CORNER)
    {
		rect.x = x;
		rect.y = y;
	}
    else
    {
        std::cout << "MyTexture::render() Incorrect mode used for rendering!\n";
    }

	rect.w = w;
	rect.h = h;

	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void MyTexture::renderAnim(SDL_Renderer* renderer, int x, int y, RenderMode mode, int numOfFrames, int frameIndex)
{
	SDL_Rect targetRect;
	SDL_Rect sourceRect;

	int w, h;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	int tileWidth = w / numOfFrames;

	sourceRect.x = frameIndex*tileWidth;
	sourceRect.y = 0;
	sourceRect.w = tileWidth;
	sourceRect.h = h;

	if (mode == RENDER_IN_CENTER)
    {
		targetRect.x = x - tileWidth / 2;
		targetRect.y = y - h / 2;
	}
	else if (mode == RENDER_IN_CORNER)
    {
		targetRect.x = x;
		targetRect.y = y;
	}
    else
    {
        std::cout << "MyTexture::renderAnim() Incorrect mode used for rendering!\n";
    }

	targetRect.w = tileWidth;
	targetRect.h = h;

	SDL_RenderCopy(renderer, texture, &sourceRect, &targetRect);
}

void MyTexture::render(SDL_Renderer* renderer, int x, int y, RenderMode mode, 
    float angle)
{
    SDL_Rect rect;

    int w, h;

    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    if (mode == RENDER_IN_CENTER)
    {
        rect.x = x - w / 2;
        rect.y = y - h / 2;
    }
    else if (mode == RENDER_IN_CORNER)
    {
        rect.x = x;
        rect.y = y;
    }
    else
    {
        std::cout << "MyTexture::render() Incorrect mode used for rendering!\n";
    }

    rect.w = w;
    rect.h = h;

    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}