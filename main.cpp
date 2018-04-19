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

class Media
{
public:
	SDL_Texture * loadTexture(const std::string &path, Window &window)
	{
		SDL_Surface* surface = SDL_LoadBMP(path.c_str());
		if (surface == nullptr)
		{
			std::cout << "SDL Error: " << SDL_GetError << "\n";
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(window.mRenderer, surface);
		SDL_FreeSurface(surface);
		return texture;
	}
	SDL_Texture* loadTitleText(const std::string &input, Window &window)
	{
		text = TTF_RenderText_Blended(titleFont, input.c_str(), white);
		SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(window.mRenderer, text);
		SDL_FreeSurface(text);
		text = nullptr;
		return titleTexture;
	}
	SDL_Texture* loadMainText(const std::string &input, Window &window)
	{
		text = TTF_RenderText_Blended(mainFont, input.c_str(), white);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(window.mRenderer, text);
		SDL_FreeSurface(text);
		text = nullptr;
		return textTexture;
	}
private:
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Color black = { 0, 0, 0, 255 };

	SDL_Surface * text;
	TTF_Font * titleFont = TTF_OpenFont("blackchancery.regular.ttf", 48);
	TTF_Font * mainFont = TTF_OpenFont("blackchancery.regular.ttf", 36);
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

	class MainMenu
	{
	public:
		bool loadMainMenu(Window &window, Media &media)
		{
			//In newly found knowledge and restrospect, I could have done a lot of stuff like
			//this as a constructor and then just have a destructor for it too. Ever learning.
			mainMenuTexture = media.loadTexture("images/MainMenu.bmp", window);
			mainMenuTitleText = media.loadTitleText("Spellbound Kingdoms Character Aid", window);
			mainMenuNewCharacterText = media.loadMainText("New Character", window);
			mainMenuLoadCharacterText = media.loadMainText("Load Character", window);
			mainMenuCombatText = media.loadMainText("Combat", window);
			mainMenuSettingsText = media.loadMainText("Settings", window);
			mainMenuExitText = media.loadMainText("Exit", window);

			return true;
		}
		bool drawMainMenu(Window &window, Media media)
		{
			drawMainMenuBackgroundImage(window, media);
			drawMainMenuTitleText(window, media);
			drawMainMenuNewCharacterText(window, media);
			drawMainMenuLoadCharacterText(window, media);
			drawMainMenuCombatText(window, media);
			drawMainMenuSettingsText(window, media);
			drawMainMenuExitText(window, media);
			SDL_RenderPresent(window.mRenderer);
			return true;
		}
	private:
		SDL_Texture * mainMenuTexture;
		SDL_Texture * mainMenuTitleText;
		SDL_Texture * mainMenuNewCharacterText;
		SDL_Texture * mainMenuLoadCharacterText;
		SDL_Texture * mainMenuCombatText;
		SDL_Texture * mainMenuSettingsText;
		SDL_Texture * mainMenuExitText;

		int textOptionsXLoc = 500;
		int textOptionsWidth = 640 - (textOptionsXLoc + 10); //Hard-coded because I'm awful and lazy. Never again.
		int textOptionsHeight = 40;

		void drawMainMenuBackgroundImage(Window &window, Media &media)
		{
			SDL_Rect mainMenuPos;
			mainMenuPos.x = 0;
			mainMenuPos.y = 0;
			mainMenuPos.w = 600;
			mainMenuPos.h = 480;
			SDL_RenderCopy(window.mRenderer, mainMenuTexture, NULL, &mainMenuPos);

			return;
		}

		void drawMainMenuTitleText(Window &window, Media &media)
		{
			SDL_Rect mainMenuTitle;
			mainMenuTitle.x = 20;
			mainMenuTitle.y = 10;
			mainMenuTitle.w = 400;
			mainMenuTitle.h = 60;
			SDL_RenderCopy(window.mRenderer, mainMenuTitleText, nullptr, &mainMenuTitle);
		}

		void drawMainMenuNewCharacterText(Window &window, Media &media)
		{
			SDL_Rect mainMenuNewCharacter;
			mainMenuNewCharacter.x = textOptionsXLoc - 10;
			mainMenuNewCharacter.y = 50 - 5;
			mainMenuNewCharacter.w = textOptionsWidth + 10;
			mainMenuNewCharacter.h = textOptionsHeight + 10;
			SDL_RenderCopy(window.mRenderer, mainMenuNewCharacterText, nullptr, &mainMenuNewCharacter);
		}

		void drawMainMenuLoadCharacterText(Window &window, Media &media)
		{
			SDL_Rect mainMenuLoadCharacter;
			mainMenuLoadCharacter.x = textOptionsXLoc - 15;
			mainMenuLoadCharacter.y = 120 - 5;
			mainMenuLoadCharacter.w = textOptionsWidth + 15;
			mainMenuLoadCharacter.h = textOptionsHeight + 10;
			SDL_RenderCopy(window.mRenderer, mainMenuLoadCharacterText, nullptr, &mainMenuLoadCharacter);
		}

		void drawMainMenuCombatText(Window &window, Media &media)
		{
			SDL_Rect mainMenuCombat;
			mainMenuCombat.x = textOptionsXLoc;
			mainMenuCombat.y = 190;
			mainMenuCombat.w = textOptionsWidth;
			mainMenuCombat.h = textOptionsHeight;
			SDL_RenderCopy(window.mRenderer, mainMenuCombatText, nullptr, &mainMenuCombat);
		}

		//settings
		void drawMainMenuSettingsText(Window &window, Media &media)
		{
			SDL_Rect mainMenuSettings;
			mainMenuSettings.x = textOptionsXLoc + 5;
			mainMenuSettings.y = 260;
			mainMenuSettings.w = textOptionsWidth - 10;
			mainMenuSettings.h = textOptionsHeight;
			SDL_RenderCopy(window.mRenderer, mainMenuSettingsText, nullptr, &mainMenuSettings);
		}

		//exit
		void drawMainMenuExitText(Window &window, Media &media)
		{
			SDL_Rect mainMenuExit;
			mainMenuExit.x = textOptionsXLoc + 20;
			mainMenuExit.y = 330;
			mainMenuExit.w = textOptionsWidth - 20;
			mainMenuExit.h = textOptionsHeight;
			SDL_RenderCopy(window.mRenderer, mainMenuExitText, nullptr, &mainMenuExit);
		}
	};
	
private:
	

	
};

int main(int argc, char* args[])
{
	Window window;
	window.init();
	
	Menu menu;
	menu.init();



	SDL_RenderPresent(window.mRenderer);

	SDL_Event event;
	while (window.isRunning == true)
	{
		if (menu.currentmenu == menu.MAIN_MENU)
		{
			Media media;
			Menu::MainMenu mainMenu;
			mainMenu.loadMainMenu(window, media);
			while (true)
			{
				SDL_RenderClear(window.mRenderer);
				mainMenu.drawMainMenu(window, media);
				if (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						window.close();
						return 0;
					}
				}
			}
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
	return 0;
}

