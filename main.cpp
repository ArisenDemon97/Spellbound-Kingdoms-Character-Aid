//Using SDL and TTF
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cstring>


class Window
{
public:
	int windowWidth = 640;
	int windowHeight = 480;
	bool isRunning = true;

	//I'm using "m" to signify "main"
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;
	SDL_Surface* mSurface = nullptr; //For text purposes

	bool init()
	{
		return sdlInit();
	}

	bool close()
	{
		return sdlClose();
	}

private:
	bool sdlInit()
	{
		bool success = false;
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
		{
			std::cout << "SDL Error: " << SDL_GetError() << "\n";
			return success;
		}
		else
		{
			mWindow = SDL_CreateWindow("Spellbound Kingdoms Character Aid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
			if (mWindow == nullptr)
			{
				std::cout << "SDL Error: " << SDL_GetError() << "\n";
				return success;
			}
			else
			{
				mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
				if (mRenderer == nullptr)
				{
					std::cout << "SDL Error: " << SDL_GetError() << "\n";
					return success;
				}
				else
				{
					if (SDL_RenderSetLogicalSize(mRenderer, windowWidth, windowHeight) == -1)
					{
						std::cout << "SDL Error: " << SDL_GetError << "\n";
						return success;
					}
					else
					{
						if (SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255) == -1)
						{
							std::cout << "SDL Error: " << SDL_GetError << "\n";
							return success;
						}
						else
						{
							SDL_RenderClear(mRenderer);
							if (TTF_Init() == -1)
							{
								std::cout << "SDL Error: " << SDL_GetError << "\n";
								return success;
							}
							else
							{
								success = true;
								return success;
							}
						}
					}
				}
			}
		}
	}


	bool sdlClose()
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = NULL;
		SDL_DestroyWindow(mWindow);
		mWindow = NULL;

		isRunning = false;
		SDL_Quit();
		return true;
	}
};

class Menu
{
public:
	enum CurrentMenu
	{
		MAIN_MENU,
		CHARACTER_MENU,
		COMBAT_MENU,
		SETTINGS_MENU
	};
	CurrentMenu currentmenu;
	bool init()
	{
		currentmenu = MAIN_MENU;
		return true;
	}
};

int main(int argc, char* args[])
{
	Window window;
	window.init();
	
	Menu menu;
	menu.init();

	SDL_Event event;
	while (window.isRunning == true)
	{
		if (menu.currentmenu == menu.MAIN_MENU)
		{
			//TODO: make menu classes as well as media loader. Use  version 0.2.2 on Github to keep track of what's missing
		}
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				window.close();
				return 0;
			}
		}
	}
}
