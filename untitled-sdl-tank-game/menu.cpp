#include "menu.h"

int GameMenu::gameMenuLoop(SDL_Renderer* r)
{
	int result = START_GAME;
	bool stop = false;
	MenuWindow& w = windows[0];
	w.activeOption = w.options.begin();
	while (!stop)
	{
		
		//user action...
		SDL_Event e;		
		while (SDL_PollEvent(&e) != 0) {

			const Uint8* state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_UP])
			{

				if (w.activeOption != (-- w.options.end()) )
				{
					w.activeOption ++;
				}
				else
				{
					w.activeOption = w.options.begin();
				}		
			}

			if (state[SDL_SCANCODE_DOWN])
			{
				//
				
				if (w.activeOption != w.options.begin())
				{
					w.activeOption --;
				}
				else
				{
					w.activeOption = -- w.options.end();
				}
			}
			if (state[SDL_SCANCODE_RETURN])
			{
				MenuItem& opt = *w.activeOption;
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
	activeWindow = -- windows.end();
}

void GameMenu::displayGameMenu(SDL_Renderer* r)
{
	SDL_RenderClear(r);
	(*activeWindow).displayWindow(r);
	SDL_RenderPresent(r);	
}

void GameMenu::setActiveWindow(std::vector<MenuWindow>::iterator it)
{	
	activeWindow = it;
}

bool MenuItem::setItem (SDL_Renderer* r, std::string name, std::string imgFileName)
{
	optionName = name;
	img = new MyTexture(r, imgFileName);

	return true;
}

void MenuItem::displayItem(SDL_Renderer* r,int x, int y, int mode)
{
	img->render(r, x, y, mode);
}

void MenuItem::displayItem(SDL_Renderer* r)
{
	img->render(r, posX, posY, RENDER_IN_CENTER);
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
	activeOption = options.begin();
	backgroundTex = new MyTexture(r, bgImgFileName);
	indicatorTex = new MyTexture(r, indImgFileName);
}

/*void MenuWindow::setActiveOption(std::vector<MenuItem>::iterator it)
{
	activeOption = it;
}*/

void MenuWindow::displayWindow(SDL_Renderer* r)
{
	//display menu background
	backgroundTex->render(r, 0, 0, RENDER_IN_CORNER);

	for (MenuItem item : options)
	{
		//TODO
		item.displayItem(r);
	}

	//TODO

	//display indicator
	MenuItem a = *activeOption;
	int y = a.getPosY();
	int x = a.getPosX() - 130;

	indicatorTex->render(r, x, y, RENDER_IN_CENTER);
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

		/*if (activeOption == options.begin())
		{
			res = false;
		}*/
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
	return res;
}