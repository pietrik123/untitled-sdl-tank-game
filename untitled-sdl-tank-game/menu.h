#pragma once

#include "MyTexture.h"

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

enum GameOptionNames
{
	START_GAME = 1,
	QUIT_GAME = 2,
};

class MenuItem
{
protected:
	std::string optionName;
	MyTexture* img;
	int posX;
	int posY;
	
public:

	std::string getName();
	MenuItem() : img(nullptr), posX(0), posY(0) {}
	~MenuItem() {}

	int(*functionPtr)();
	bool setItem(SDL_Renderer* r, std::string name, std::string imgFileName);
	void setLocation(int posX, int posY);
	int getPosX();
	int getPosY();

	void displayItem(SDL_Renderer* r, int x, int y, int mode);
	void displayItem(SDL_Renderer* r );

	//TODO
	//validate method
	bool validate();
};

class MenuWindow
{
protected:
	
	std::string windowName;

	MyTexture* backgroundTex;
	MyTexture* indicatorTex;
	
	
	int indPosX;
	int indPosY;
	//SDL_Renderer *renderer;

public:
	//TODO

	int activeOptionIdx;
	std::vector<MenuItem>::iterator activeOption;
	std::vector<MenuItem> options;

	void setIndPos(int x, int y);
	MenuWindow(): backgroundTex (nullptr), indicatorTex(nullptr), activeOptionIdx(-1) {}
	~MenuWindow() {}

	int getIndPosX();
	int getIndPosY();
	

	void setMenuWindow(SDL_Renderer* r, std::vector<MenuItem> items, std::string bgImgFileName, std::string indImgFileName);
	//void MenuWindow::setActiveOption(std::vector<MenuItem>::iterator it);
	void displayWindow(SDL_Renderer* r);
	
	//TODO
	//validate method
	//TODO
	//problem with validation
	bool validate();	
};

class GameMenu
{
protected:
	std::vector<MenuWindow>::iterator activeWindow;
	std::vector<MenuWindow> windows;

public:
	GameMenu() : activeWindowIdx(-1){}
	~GameMenu() {}

	int activeWindowIdx;
	void addMenuWindow(MenuWindow window);
	void setActiveWindow(std::vector<MenuWindow>::iterator it);
		
	int gameMenuLoop(SDL_Renderer* r);
	
	void displayGameMenu(SDL_Renderer* r);

	//TODO
	//validate method
	bool validate();
};

