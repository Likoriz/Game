#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Motion.h"
#include "Menu.h"
#include "Map.h"
#include "NPCAnimation.h"
#include "Basic.h"
#include "Dialogue.h"

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWidth = 1920;
int winHeight = 1017;

float scaleX = DEFAULTSCALE;
float scaleY = DEFAULTSCALE;

GameState state;
Time timer;

int main(int argc, char* argv[])
{
	Init();

	SDL_Event event;
	double minS = 0;

	SDL_RenderSetScale(ren, scaleX, scaleY);
	winWidth /= scaleX;
	winHeight /= scaleY;

	StartMenu(menu, StartGame, ContinueGame, Credits, Exit);
	if (menu.isHeroChoice)
		HeroChoice(menu, ChooseEnchantress, ChooseKnight, character);

	if (character.isEnchantress)
	{
		SDL_DestroyTexture(character.playerTexture);
		character.playerTexture = NULL;
		character.playerTexture = LoadTexture("Character\\EnchantressAnimation.png", &character.playerRect);
	}
	else
		if (character.isKnight)
		{
			SDL_DestroyTexture(character.playerTexture);
			character.playerTexture = NULL;
			character.playerTexture = LoadTexture("Character\\KnightAnimation.png", &character.playerRect);
		}

	character.playerRect.w = 128;
	character.playerRect.h = 128;

	timer.lastTime = SDL_GetTicks();

	LoadMap(map, tile, hitbox, npc);

	bool isp = true;

	while (menu.isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				menu.isRunning = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					SDL_GetWindowSize(win, &winWidth, &winHeight);
					scaleX = (winWidth * 1.f / WIDTH) * DEFAULTSCALE;
					scaleY = (winHeight * 1.f / HEIGHT) * DEFAULTSCALE;
					SDL_RenderSetScale(ren, scaleX, scaleY);
					winWidth /= scaleX;
					winHeight /= scaleY;
				}
				break;
			case SDL_KEYDOWN:
				if (state.isGaming)
				{
					switch (event.key.keysym.scancode)
					{
					case SDL_SCANCODE_W: character.isUp = true;	character.isIdle = false;									break;
					case SDL_SCANCODE_S: character.isDown = true; character.isIdle = false;									break;
					case SDL_SCANCODE_D: character.isRight = true; character.isIdle = false;								break;
					case SDL_SCANCODE_A: character.isLeft = true; character.isIdle = false;									break;
					case SDL_SCANCODE_LSHIFT: character.boostSpeed = true; character.speed = 225; character.isIdle = false;	break;
					case SDL_SCANCODE_E: 
						minS = CheckNPC(npc);
						if (minS <= MINSFROMNPC)
						{
							state.isGaming = false;
							state.isDialouge = true;
						}
						break;
					case SDL_SCANCODE_ESCAPE:
						menu.isOpen = true;
						ResumeMenu(menu, ResumeGame, ReturnToMainMenu, Exit);
						if (menu.isReturn)
						{
							menu.isReturn = false;
							StartMenu(menu, StartGame, ContinueGame, Credits, Exit);
							if (menu.isHeroChoice)
								HeroChoice(menu, ChooseEnchantress, ChooseKnight, character);

							if (character.isEnchantress)
							{
								SDL_DestroyTexture(character.playerTexture);
								character.playerTexture = NULL;
								character.playerTexture = LoadTexture("Character\\EnchantressAnimation.png", &character.playerRect);
							}
							else
								if (character.isKnight)
								{
									SDL_DestroyTexture(character.playerTexture);
									character.playerTexture = NULL;
									character.playerTexture = LoadTexture("Character\\KnightAnimation.png", &character.playerRect);
								}
							character.playerRect.w = 128;
							character.playerRect.h = 128;
							//character.x = 150;
							//character.y = 2000;
						}
						timer.lastTime = SDL_GetTicks();
					}
				}
				if (state.isDialouge)
				{
					switch (event.key.keysym.scancode)
					{
					case SDL_SCANCODE_SPACE:
						dialogueBox.progress++;
						//state.isDialouge = false;
						//state.isGaming = true;
						break;
					}
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_W: character.isUp = false; character.isIdle = true;									break;
				case SDL_SCANCODE_S: character.isDown = false; character.isIdle = true;									break;
				case SDL_SCANCODE_D: character.isRight = false;	character.isIdle = true;								break;
				case SDL_SCANCODE_A: character.isLeft = false; character.isIdle = true;									break;
				case SDL_SCANCODE_LSHIFT: character.boostSpeed = false; character.speed = 150; character.isIdle = true; break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (state.isGaming)
				{
					switch (event.button.button)
					{
					case SDL_BUTTON_LEFT:
						character.isAttack = true;
						character.countAttack++;
						if (character.countAttack == 2)
							character.countAttack = 0;
						break;
					case SDL_BUTTON_RIGHT:
						character.isUlt = true;
						break;
					}
				}
				break;
			}
		}

		timer.newTime = SDL_GetTicks();
		timer.dt = timer.newTime - timer.lastTime;
		timer.lastTime = timer.newTime;

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

		UpdateMap(map, tile, hitbox);
		NPCAnimation(npc, timer);

		if (state.isGaming)
			Motion(character, timer);

		Animation(character, timer);

		if (state.isDialouge)
			Dialogue(dialogueBox);

		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(character.playerTexture);
	DeleteMap(map, tile, hitbox);

	DeInit(0);

	return 0;
}