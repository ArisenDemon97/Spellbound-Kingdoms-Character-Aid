//Using SDL
#include <SDL.h>
#include <iostream>
#include <string>
#include <cstring>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Initializing functions
bool init();
bool drawMainMenu();
SDL_Texture* loadTexture(const std::string &path);
void close();


//Main window
SDL_Window* gWindow = NULL;

//Renderer for said window
SDL_Renderer* gRenderer = NULL;

//Textures to be rendered
SDL_Texture* mainMenuTexture;


int main(int argc, char* args[])
{
	init();
	SDL_Event event;
	mainMenuTexture = loadTexture("images/MainMenu.bmp");
	while (true)
	{
		drawMainMenu();
		SDL_RenderPresent(gRenderer);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				close();
				return 0;
			}
		}

	}
	return 0;
}

bool init()
{
	bool success = false;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cout << "SDL Error: " << SDL_GetError();
		return success;
	}
	else
	{
		gWindow = SDL_CreateWindow("Spellbound Kingdoms Character Aid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			std::cout << "SDL Error: " << SDL_GetError();
			return success;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr)
			{
				return success;
			}
			else
			{
				if (SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT) == -1)
				{
					std::cout << "SDL Error: " << SDL_GetError();
					return success;
				}
				else
				{
					if (SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255 == -1))
					{
						std::cout << "SDL Error: " << SDL_GetError();
						return success;
					}
					else
					{
						SDL_RenderClear(gRenderer);
						success = true;
						return success;
					}
				}
			}
		}
	}
}

bool drawMainMenu()
{
	SDL_Rect background;
	background.x = 0;
	background.y = 0;
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

	SDL_RenderFillRect(gRenderer, &background);

	//Create and draw the menu background
	SDL_Rect menuOptionsColumnBackground;
	menuOptionsColumnBackground.x = 600;
	menuOptionsColumnBackground.y = 0;
	menuOptionsColumnBackground.w = SCREEN_WIDTH - 600;
	menuOptionsColumnBackground.h = SCREEN_HEIGHT;

	SDL_SetRenderDrawColor(gRenderer, 100, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &menuOptionsColumnBackground);

	SDL_Rect mainMenuPos;
	mainMenuPos.x = 0;
	mainMenuPos.y = 0;
	mainMenuPos.w = 600;
	mainMenuPos.h = 480;
	SDL_RenderCopy(gRenderer, mainMenuTexture, NULL, &mainMenuPos);

	return true;
}

SDL_Texture* loadTexture(const std::string &path)
{
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	if (surface == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void close()
{
	//Free image
	SDL_DestroyTexture(mainMenuTexture);
	mainMenuTexture = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	SDL_Quit();
	return;
}
