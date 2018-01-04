//Using SDL and TTF
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Initializing functions
bool init();
bool drawMainMenu();
void drawMainMenuBackground();
void drawMainMenuOptionsBackground();
void drawMainMenuBackgroundImage();
SDL_Texture* loadTexture(const std::string &path);
void drawMainMenuOptions();
SDL_Texture* loadMainMenuTitleText();
SDL_Texture* loadText(const std::string &input);
void drawMainMenuText();
void close();

enum CurrentMenu
{
	MAIN_MENU,
	CHARACTER_MENU,
	OPTIONS_MENU,
	COMBAT_MENU,
};


//Main window
SDL_Window* gWindow = NULL;

//Renderer for said window
SDL_Renderer* gRenderer = NULL;

//Textures to be rendered
SDL_Texture* mainMenuTexture;
SDL_Texture* titleTexture;
SDL_Texture* newCharacterTextTexture;
SDL_Texture* loadCharacterTextTexture;

//Surface for text
SDL_Surface* text;

//Text Rendering
TTF_Font* titleFont;
TTF_Font* mainFont;
SDL_Color white = { 255, 255, 255, 255 };
SDL_Color black = { 0, 0, 0, 255 };

std::vector<int> drawRects = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

int main(int argc, char* args[])
{
	CurrentMenu currentMenu = MAIN_MENU;
	init();
	titleFont = TTF_OpenFont("blackchancery.regular.ttf", 48);
	mainFont = TTF_OpenFont("blackchancery.regular.ttf", 36);
	SDL_Event event;
	mainMenuTexture = loadTexture("images/MainMenu.bmp");
	
	if (currentMenu == MAIN_MENU)
		{
			drawMainMenu();
			while (true)
			{
				if (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						close();
						return 0;
					}
					if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);
						std::cout << "Click!" << " " << mouseX << " " << mouseY << "\n";
						if (mouseX >= 500 && mouseX <= 630 && mouseY >= 330 && mouseY <= 370)
						{
							close();
							return 0;
						}
					}
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
						if (TTF_Init() == -1)
						{
							std::cout << "SDL Error: " << SDL_GetError();
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


bool drawMainMenu()
{
	
	drawMainMenuBackground();

	//Create the bar behind the menu options
	drawMainMenuOptionsBackground();

	drawMainMenuBackgroundImage();

	drawMainMenuOptions();

	SDL_RenderPresent(gRenderer);

	return true;
}

void drawMainMenuBackground()
{
	SDL_Rect background;
	background.x = 0;
	background.y = 0;
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

	SDL_RenderFillRect(gRenderer, &background);

	return;
}

void drawMainMenuOptionsBackground()
{
	SDL_Rect menuOptionsColumnBackground;
	menuOptionsColumnBackground.x = 600;
	menuOptionsColumnBackground.y = 0;
	menuOptionsColumnBackground.w = SCREEN_WIDTH - 600;
	menuOptionsColumnBackground.h = SCREEN_HEIGHT;

	SDL_SetRenderDrawColor(gRenderer, 100, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &menuOptionsColumnBackground);

	return;
}

void drawMainMenuBackgroundImage()
{
	SDL_Rect mainMenuPos;
	mainMenuPos.x = 0;
	mainMenuPos.y = 0;
	mainMenuPos.w = 600;
	mainMenuPos.h = 480;
	SDL_RenderCopy(gRenderer, mainMenuTexture, NULL, &mainMenuPos);

	return;
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

void drawMainMenuOptions()
{
	/*
	int menuOptionsHeight = 40;
	int menuOptionsXLoc = 500;
	int menuOptionsWidth = SCREEN_WIDTH - (menuOptionsXLoc + 10);

	SDL_Rect mainMenuNewCharacterOption;
	mainMenuNewCharacterOption.x = menuOptionsXLoc;
	mainMenuNewCharacterOption.y = 50;
	mainMenuNewCharacterOption.w = menuOptionsWidth;
	mainMenuNewCharacterOption.h = menuOptionsHeight;

	SDL_Rect mainMenuLoadCharacterOption;
	mainMenuLoadCharacterOption.x = menuOptionsXLoc;
	mainMenuLoadCharacterOption.y = 120;
	mainMenuLoadCharacterOption.w = menuOptionsWidth;
	mainMenuLoadCharacterOption.h = menuOptionsHeight;

	SDL_Rect mainMenuCombatOption;
	mainMenuCombatOption.x = menuOptionsXLoc;
	mainMenuCombatOption.y = 190;
	mainMenuCombatOption.w = menuOptionsWidth;
	mainMenuCombatOption.h = menuOptionsHeight;

	SDL_Rect mainMenuSettingsOption;
	mainMenuSettingsOption.x = menuOptionsXLoc;
	mainMenuSettingsOption.y = 260;
	mainMenuSettingsOption.w = menuOptionsWidth;
	mainMenuSettingsOption.h = menuOptionsHeight;

	SDL_Rect mainMenuExitOption;
	mainMenuExitOption.x = menuOptionsXLoc;
	mainMenuExitOption.y = 330;
	mainMenuExitOption.w = menuOptionsWidth;
	mainMenuExitOption.h = menuOptionsHeight;


	SDL_SetRenderDrawColor(gRenderer, 40, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &mainMenuNewCharacterOption);
	SDL_RenderFillRect(gRenderer, &mainMenuLoadCharacterOption);
	SDL_RenderFillRect(gRenderer, &mainMenuCombatOption);
	SDL_RenderFillRect(gRenderer, &mainMenuSettingsOption);
	SDL_RenderFillRect(gRenderer, &mainMenuExitOption);
	*/
	drawMainMenuText();

	return;
}

SDL_Texture* loadMainMenuTitleText()
{
	text = TTF_RenderText_Blended(titleFont, "Spellbound Kingdoms Character Aid", white);
	titleTexture = SDL_CreateTextureFromSurface(gRenderer, text);
	SDL_FreeSurface(text);
	text = nullptr;
	return titleTexture;
}

SDL_Texture* loadText(const std::string &input)
{
	text = TTF_RenderText_Blended(mainFont, input.c_str(), white);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, text);
	SDL_FreeSurface(text);
	text = nullptr;
	return textTexture;
}

void drawMainMenuText()
{
	loadMainMenuTitleText();
	SDL_Texture* newCharacterText = loadText("New Character");
	SDL_Texture* loadCharacterText = loadText("Load Character");
	SDL_Texture* combatText = loadText("Combat");
	SDL_Texture* settingsText = loadText("Settings");
	SDL_Texture* exitText = loadText("Exit");

	int textOptionsXLoc = 500;
	int textOptionsWidth = SCREEN_WIDTH - (textOptionsXLoc + 10);
	int textOptionsHeight = 40;

	SDL_Rect mainMenuTitle;
	mainMenuTitle.x = 20;
	mainMenuTitle.y = 10;
	mainMenuTitle.w = 400;
	mainMenuTitle.h = 60;

	SDL_Rect newCharacterOption;
	newCharacterOption.x = textOptionsXLoc;
	newCharacterOption.y = 50;
	newCharacterOption.w = textOptionsWidth;
	newCharacterOption.h = textOptionsHeight;

	SDL_Rect loadCharacterOption;
	loadCharacterOption.x = textOptionsXLoc;
	loadCharacterOption.y = 120;
	loadCharacterOption.w = textOptionsWidth;
	loadCharacterOption.h = textOptionsHeight;

	SDL_Rect combatOption;
	combatOption.x = textOptionsXLoc;
	combatOption.y = 190;
	combatOption.w = textOptionsWidth;
	combatOption.h = textOptionsHeight;

	SDL_Rect settingsOption;
	settingsOption.x = textOptionsXLoc + 5;
	settingsOption.y = 260;
	settingsOption.w = textOptionsWidth - 10;
	settingsOption.h = textOptionsHeight;

	SDL_Rect exitOption;
	exitOption.x = textOptionsXLoc + 10;
	exitOption.y = 330;
	exitOption.w = textOptionsWidth - 20;
	exitOption.h = textOptionsHeight;


	SDL_RenderCopy(gRenderer, titleTexture, nullptr, &mainMenuTitle);
	SDL_RenderCopy(gRenderer, newCharacterText, nullptr, &newCharacterOption);
	SDL_RenderCopy(gRenderer, loadCharacterText, nullptr, &loadCharacterOption);
	SDL_RenderCopy(gRenderer, combatText, nullptr, &combatOption);
	SDL_RenderCopy(gRenderer, settingsText, nullptr, &settingsOption);
	SDL_RenderCopy(gRenderer, exitText, nullptr, &exitOption);



	SDL_DestroyTexture(newCharacterText);
	SDL_DestroyTexture(loadCharacterText);
	SDL_DestroyTexture(combatText);
	SDL_DestroyTexture(settingsText);
	SDL_DestroyTexture(exitText);

	newCharacterText = NULL;
	loadCharacterText = NULL;
	combatText = NULL;
	settingsText = NULL;
	exitText = NULL;

	return;
}

void close()
{
	//Free image
	SDL_DestroyTexture(mainMenuTexture);
	SDL_DestroyTexture(titleTexture);
	mainMenuTexture = NULL;
	titleTexture = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	TTF_CloseFont(titleFont);

	SDL_Quit();
	return;
}
