#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Basic.h"

struct Menu
{
	SDL_Rect backgroundRect = {};
	SDL_Texture* backgroundTexture = NULL;
	bool isStart = true;
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