#pragma once
#include "Basic.h"

struct Menu
{
	SDL_Rect backgroundRect = {};
	SDL_Texture* backgroundTexture = NULL;
	bool isStart = true;
	bool isLoad = false;
	bool isHeroChoice = false;
	bool isOpen = true;
	bool isReturn = false;
	bool isCredits = true;
	bool isRunning = false;
};
extern Menu menu;

struct MenuButtons
{
	SDL_Color colour = { 0, 0, 0, 255 };
	SDL_FRect dstRect = { 0, 0, 0, 0 };
	char stringText[100] = "";
	SDL_Rect textRect;
	SDL_Texture* text = NULL;
	int soundCount = 0;
};
extern MenuButtons StartGame;
extern MenuButtons ChooseEnchantress;
extern MenuButtons ChooseKnight;
extern MenuButtons ResumeGame;
extern MenuButtons ReturnToMainMenu;
extern MenuButtons ContinueGame;
extern MenuButtons Credits;
extern MenuButtons Back;
extern MenuButtons Exit;

void StartMenu();
void HeroChoice();
void ResumeMenu();
void Credit();