#include "menu.h"

#include <iostream>

int GameMenu::gameMenuLoop(SDL_Renderer* r)
{
	int result = START_GAME;
	bool stop = false;
	MenuWindow& w = windows[activeWindowIdx];
	while (!stop)
	{
		
		//user action...
		SDL_Event e;		
		while (SDL_PollEvent(&e) != 0)
        {
			const Uint8* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_UP])
			{

				if (w.activeOptionIdx != (w.options.size() - 1))
				{
					w.activeOptionIdx ++;
				}
				else
				{
					w.activeOptionIdx = 0;
				}		
			}

			if (state[SDL_SCANCODE_DOWN])
			{
				//
				
				if (w.activeOptionIdx != 0)
				{
					w.activeOptionIdx --;
				}
				else
				{
					w.activeOptionIdx = w.options.size()-1;
				}
			}
			if (state[SDL_SCANCODE_RETURN])
			{
				MenuItem& opt = w.options[w.activeOptionIdx];
				if (opt.getName() == "new_game")
				{
					result = START_GAME;
				}
				else
				{
					result = QUIT_GAME;
				}
				
				stop = true;
				break;
			}
			if (state[SDL_SCANCODE_ESCAPE])
			{
				stop = true;
				result = QUIT_GAME;
				break;
			}

		}
		displayGameMenu(r);
		SDL_Delay(50);
	}

	return result;
}

void GameMenu::addMenuWindow(MenuWindow window)
{
	windows.push_back(window);
	activeWindowIdx = windows.size()-1;
}

void GameMenu::displayGameMenu(SDL_Renderer* r)
{
	SDL_RenderClear(r);
	windows[activeWindowIdx].displayWindow(r);
	SDL_RenderPresent(r);	
}



bool MenuItem::setItem (SDL_Renderer* r, std::string name, std::string imgFileName)
{
	optionName = name;
	img = new MyTexture(r, imgFileName);

	return true;
}

void MenuItem::displayItem(SDL_Renderer* r,int x, int y, MyTexture::RenderMode mode)
{
	img->render(r, x, y, mode);
}

void MenuItem::displayItem(SDL_Renderer* r)
{
	img->render(r, posX, posY, MyTexture::RENDER_IN_CENTER);
}

std::string	MenuItem::getName()
{
	return optionName;
}

void MenuItem::setLocation(int x, int y)
{
	posX = x;
	posY = y;
}

int MenuItem::getPosX()
{
	return posX;
}

int MenuItem::getPosY()
{
	return posY;
}

void MenuWindow::setMenuWindow(SDL_Renderer* r, std::vector<MenuItem> items, std::string bgImgFileName, std::string indImgFileName)
{
	options = items;
	activeOptionIdx = 0;
	backgroundTex = new MyTexture(r, bgImgFileName);
	indicatorTex = new MyTexture(r, indImgFileName);
}


void MenuWindow::displayWindow(SDL_Renderer* r)
{
	//display menu background
	backgroundTex->render(r, 0, 0, MyTexture::RENDER_IN_CORNER);

	for (MenuItem item : options)
	{
		item.displayItem(r);
	}

	//display indicator
	MenuItem a = options[activeOptionIdx];

	int y = a.getPosY();
	int x = a.getPosX() - 130;

	indicatorTex->render(r, x, y, MyTexture::RENDER_IN_CENTER);
}

void MenuWindow::setIndPos(int x, int y)
{
	indPosX = x;
	indPosY = y;
}

int MenuWindow::getIndPosX()
{
	return indPosX;
}

int MenuWindow::getIndPosY()
{
	return indPosY;
}


/////////////////////
///validation

//these methods will check if all menu object are set up correctly

bool MenuItem::validate()
{
	bool res = true;
	if (img == nullptr || optionName == "")
	{
		res = false;
	}
    if (res == false)
    {
        std::cout << "Error in menu item validation!\n";
    }
	return res;
}

bool MenuWindow::validate()
{
	bool res = true;
	if (backgroundTex == nullptr || indicatorTex == nullptr)
	{
		res = false;
	}
	if (options.empty())
	{
		res = false;
	}
	else
	{
	//TODO
	//error "vector iterators incompatible"

		if (activeOptionIdx < 0 || activeOptionIdx >(options.size() - 1))
		{
			res = false;
		}

	}
	if (res != false)
	{
		for (auto e : options)
		{
			if (e.validate() == false)
			{
				res = false;
				break;
			}
		}
	}
    if (res == false)
    {
        std::cout << "Error in menu window validation!\n";
    }
	return res;
}

bool GameMenu::validate()
{
	bool res = true;

	if (windows.empty())
	{
		res = false;
	}
	else {
		for (auto e : windows)
		{
			if (e.validate() == false)
			{
				res = false;
			}
		}
	}
    if (res == false)
    {
        std::cout << "Error in game menu validation!\n";
    }
	return res;
}