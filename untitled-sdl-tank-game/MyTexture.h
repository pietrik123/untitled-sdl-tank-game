#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#define RENDER_IN_CORNER 1
#define RENDER_IN_CENTER 2

class MyTexture
{
public:
	SDL_Texture* texture;

	MyTexture();
	MyTexture(SDL_Renderer* renderer, std::string fileName);
	~MyTexture();

	void render(SDL_Renderer* renderer, int x, int y, int mode);
    void render(SDL_Renderer* renderer, int x, int y, int mode, float angle);
	void renderAnim(SDL_Renderer* renderer, int x, int y, int mode, int numOfFrames, int frameIndex);
};