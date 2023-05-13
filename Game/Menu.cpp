#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Menu.h"
#include "Basic.h"
#include "Motion.h"

Menu menu;
MenuButtons StartGame, ChooseEnchantress, ChooseKnight, ResumeGame, ReturnToMainMenu, ContinueGame, Credits, Back, Exit;

void StartMenu(Menu& menu, MenuButtons& StartGame, MenuButtons& ContinueGame, MenuButtons& Credits, MenuButtons& Exit)
{
	SDL_RenderClear(ren);
	menu.backgroundTexture = LoadTexture("Menu\\MenuBackground.png", &menu.backgroundRect);

	TTF_Font* font = TTF_OpenFont("Monocraft.ttf", 100);

	StartGame.dstRect.w = 300;
	StartGame.dstRect.h = 60;
	StartGame.dstRect.x = winWidth * 1.f / 2  - StartGame.dstRect.w / 2;
	StartGame.dstRect.y = winHeight * 1.f / 2  - StartGame.dstRect.h / 2;

	ContinueGame.dstRect.w = 400;
	ContinueGame.dstRect.h = 60;
	ContinueGame.dstRect.x = winWidth * 1.f / 2 - ContinueGame.dstRect.w / 2;
	ContinueGame.dstRect.y = winHeight * 1.f / 2 + ContinueGame.dstRect.h / 2 + 10;

	Credits.dstRect.w = 200;
	Credits.dstRect.h = 60;
	Credits.dstRect.x = winWidth * 1.f / 2 - Credits.dstRect.w / 2;
	Credits.dstRect.y = winHeight * 1.f / 2 + Credits.dstRect.h / 2 * 3 + 20;

	Exit.dstRect.w = 100;
	Exit.dstRect.h = 60;
	Exit.dstRect.x = winWidth * 1.f / 2 - Exit.dstRect.w / 2;
	Exit.dstRect.y = winHeight * 1.f / 2 + Exit.dstRect.h / 2 * 5 + 30;

	strcpy_s(StartGame.stringText, 100, "Start Game");
	strcpy_s(ContinueGame.stringText, 100, "Continue Game");
	strcpy_s(Credits.stringText, 100, "Credits");
	strcpy_s(Exit.stringText, 100, "Exit");

	SDL_Event event;
	int mouseX, mouseY;
	while (menu.isStart)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				menu.isRunning = false;
				menu.isStart = false;
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (mouseX >= StartGame.dstRect.x * scaleX && mouseX <= (StartGame.dstRect.x + StartGame.dstRect.w) * scaleX && mouseY >= StartGame.dstRect.y * scaleY && mouseY <= (StartGame.dstRect.y + StartGame.dstRect.h) * scaleY)
					StartGame.colour = { 180, 180, 180, 255 };
				else
					StartGame.colour = { 0, 0, 0, 255 };

				if (mouseX >= ContinueGame.dstRect.x * scaleX && mouseX <= (ContinueGame.dstRect.x + ContinueGame.dstRect.w) * scaleX && mouseY >= ContinueGame.dstRect.y * scaleY && mouseY <= (ContinueGame.dstRect.y + ContinueGame.dstRect.h) * scaleY)
					ContinueGame.colour = { 180, 180, 180, 255 };
				else
					ContinueGame.colour = { 0, 0, 0, 255 };

				if (mouseX >= Credits.dstRect.x * scaleX && mouseX <= (Credits.dstRect.x + Credits.dstRect.w) * scaleX && mouseY >= Credits.dstRect.y * scaleY && mouseY <= (Credits.dstRect.y + Credits.dstRect.h) * scaleY)
					Credits.colour = { 180, 180, 180, 255 };
				else
					Credits.colour = { 0, 0, 0, 255 };

				if (mouseX >= Exit.dstRect.x * scaleX && mouseX <= (Exit.dstRect.x + Exit.dstRect.w) * scaleX && mouseY >= Exit.dstRect.y * scaleY && mouseY <= (Exit.dstRect.y + Exit.dstRect.h) * scaleY)
					Exit.colour = { 180, 180, 180, 255 };
				else
					Exit.colour = { 0, 0, 0, 255 };
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (mouseX >= StartGame.dstRect.x * scaleX && mouseX <= (StartGame.dstRect.x + StartGame.dstRect.w) * scaleX && mouseY >= StartGame.dstRect.y * scaleY && mouseY <= (StartGame.dstRect.y + StartGame.dstRect.h) * scaleY)
					{
						menu.isStart = false;
						menu.isHeroChoice = true;
					}

					if (mouseX >= ContinueGame.dstRect.x * scaleX && mouseX <= (ContinueGame.dstRect.x + ContinueGame.dstRect.w) * scaleX && mouseY >= ContinueGame.dstRect.y * scaleY && mouseY <= (ContinueGame.dstRect.y + ContinueGame.dstRect.h) * scaleY)
					{
						menu.isStart = false;
						menu.isHeroChoice = true;
					}

					if (mouseX >= Credits.dstRect.x * scaleX && mouseX <= (Credits.dstRect.x + Credits.dstRect.w) * scaleX && mouseY >= Credits.dstRect.y * scaleY && mouseY <= (Credits.dstRect.y + Credits.dstRect.h) * scaleY)
					{
						menu.isCredits = true;
						Credit(menu, Back);
					}

					if (mouseX >= Exit.dstRect.x * scaleX && mouseX <= (Exit.dstRect.x + Exit.dstRect.w) * scaleX && mouseY >= Exit.dstRect.y * scaleY && mouseY <= (Exit.dstRect.y + Exit.dstRect.h) * scaleY)
					{
						menu.isRunning = false;
						menu.isStart = false;
					}
				}
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
			}
		}
		SDL_RenderCopy(ren, menu.backgroundTexture, &menu.backgroundRect, NULL);

		SDL_DestroyTexture(StartGame.text);
		StartGame.text = GenerateTextureText(StartGame.stringText, font, &StartGame.textRect, StartGame.colour);
		SDL_RenderCopyF(ren, StartGame.text, &StartGame.textRect, &StartGame.dstRect);

		SDL_DestroyTexture(ContinueGame.text);
		ContinueGame.text = GenerateTextureText(ContinueGame.stringText, font, &ContinueGame.textRect, ContinueGame.colour);
		SDL_RenderCopyF(ren, ContinueGame.text, &ContinueGame.textRect, &ContinueGame.dstRect);

		SDL_DestroyTexture(Credits.text);
		Credits.text = GenerateTextureText(Credits.stringText, font, &Credits.textRect, Credits.colour);
		SDL_RenderCopyF(ren, Credits.text, &Credits.textRect, &Credits.dstRect);

		SDL_DestroyTexture(Exit.text);
		Exit.text = GenerateTextureText(Exit.stringText, font, &Exit.textRect, Exit.colour);
		SDL_RenderCopyF(ren, Exit.text, &Exit.textRect, &Exit.dstRect);

		SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(StartGame.text);
	SDL_DestroyTexture(ContinueGame.text);
	SDL_DestroyTexture(Credits.text);
	SDL_DestroyTexture(Exit.text);

	StartGame.text = NULL;
	ContinueGame.text = NULL;
	Credits.text = NULL;
	Exit.text = NULL;

	SDL_DestroyTexture(menu.backgroundTexture);
	menu.backgroundTexture = NULL;

	TTF_CloseFont(font);
}

void Credit(Menu& menu, MenuButtons& Back)
{
	TTF_Font* font = TTF_OpenFont("Monocraft.ttf", 100);

	SDL_Color colour1 = { 0, 0, 0, 255 };
	SDL_FRect dstRect1 = { 0, 0, 0, 0 };
	char stringText1[100] = "";
	SDL_Rect textRect1;
	SDL_Texture* text1 = NULL;

	SDL_Color colour2 = { 0, 0, 0, 255 };
	SDL_FRect dstRect2 = { 0, 0, 0, 0 };
	char stringText2[100] = "";
	SDL_Rect textRect2;
	SDL_Texture* text2 = NULL;

	dstRect1.w = 500;
	dstRect1.h = 60;
	dstRect1.x = winWidth * 1.f / 2 - dstRect1.w / 2;
	dstRect1.y = winHeight * 1.f / 2 - dstRect1.h / 2;

	dstRect2.w = 500;
	dstRect2.h = 60;
	dstRect2.x = winWidth * 1.f / 2 - dstRect1.w / 2;
	dstRect2.y = winHeight * 1.f / 2 + dstRect2.h / 2 + 10;

	Back.dstRect.w = 100;
	Back.dstRect.h = 60;
	Back.dstRect.x = winWidth * 1.f / 2 - Back.dstRect.w / 2;
	Back.dstRect.y = winHeight * 1.f / 2 + Back.dstRect.h / 2 * 3 + 20;

	strcpy_s(stringText1, 100, "Sidortzova Diana");
	strcpy_s(stringText2, 100, "Ishutenko Daniil");
	strcpy_s(Back.stringText, 100, "Back");

	SDL_Event event;
	int mouseX, mouseY;
	while (menu.isCredits)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				menu.isRunning = false;
				menu.isCredits = false;
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (mouseX >= Back.dstRect.x * scaleX && mouseX <= (Back.dstRect.x + Back.dstRect.w) * scaleX && mouseY >= Back.dstRect.y * scaleY && mouseY <= (Back.dstRect.y + Back.dstRect.h) * scaleY)
					Back.colour = { 180, 180, 180, 255 };
				else
					Back.colour = { 0, 0, 0, 255 };
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (mouseX >= Back.dstRect.x * scaleX && mouseX <= (Back.dstRect.x + Back.dstRect.w) * scaleX && mouseY >= Back.dstRect.y * scaleY && mouseY <= (Back.dstRect.y + Back.dstRect.h) * scaleY)
					{
						SDL_DestroyTexture(text1);
						SDL_DestroyTexture(text2);
						SDL_DestroyTexture(Back.text);

						text1 = NULL;
						text2 = NULL;
						Back.text = NULL;

						menu.isCredits = false;
						menu.isStart = true;
					}
				}
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
			}
		}

		SDL_RenderCopy(ren, menu.backgroundTexture, &menu.backgroundRect, NULL);

		SDL_DestroyTexture(text1);
		text1 = GenerateTextureText(stringText1, font, &textRect1, colour1);
		SDL_RenderCopyF(ren, text1, &textRect1, &dstRect1);

		SDL_DestroyTexture(text2);
		text2 = GenerateTextureText(stringText2, font, &textRect2, colour2);
		SDL_RenderCopyF(ren, text2, &textRect2, &dstRect2);

		SDL_DestroyTexture(Back.text);
		Back.text = GenerateTextureText(Back.stringText, font, &Back.textRect, Back.colour);
		SDL_RenderCopyF(ren, Back.text, &Back.textRect, &Back.dstRect);

		SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(text1);
	SDL_DestroyTexture(text2);
	SDL_DestroyTexture(Back.text);

	Back.text = NULL;

	TTF_CloseFont(font);
}

void HeroChoice(Menu& menu, MenuButtons& ChooseEnchantress, MenuButtons& ChooseKnight, Character& character)
{
	SDL_RenderClear(ren);
	menu.backgroundTexture = LoadTexture("Menu\\MenuBackground.png", &menu.backgroundRect);

	TTF_Font* font = TTF_OpenFont("Monocraft.ttf", 100);

	ChooseEnchantress.dstRect.w = 500;
	ChooseEnchantress.dstRect.h = 60;
	ChooseEnchantress.dstRect.x = 20;
	ChooseEnchantress.dstRect.y = winHeight * 1.f / 2 + ChooseEnchantress.dstRect.h / 2 + 10;

	ChooseKnight.dstRect.w = 350;
	ChooseKnight.dstRect.h = 60;
	ChooseKnight.dstRect.x = winWidth - ChooseEnchantress.dstRect.w;
	ChooseKnight.dstRect.y = winHeight * 1.f / 2 + ChooseKnight.dstRect.h / 2 + 10;

	strcpy_s(ChooseEnchantress.stringText, 100, "Choose Enchantress");
	strcpy_s(ChooseKnight.stringText, 100, "Choose Knight");

	SDL_FRect enchantressDstRect = { 190, winHeight * 1.f / 2 - 128, 128, 128 };
	SDL_Rect enchantressPNGRect;
	SDL_Texture* enchantressPNG = NULL;

	SDL_FRect knightDstRect = { 900, winHeight * 1.f / 2 - 128, 128, 128 };
	SDL_Rect knightPNGRect;
	SDL_Texture* knightPNG = NULL;

	SDL_Event event;
	int mouseX, mouseY;
	while (menu.isHeroChoice)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				menu.isRunning = false;
				menu.isHeroChoice = false;
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (mouseX >= ChooseEnchantress.dstRect.x * scaleX && mouseX <= (ChooseEnchantress.dstRect.x + ChooseEnchantress.dstRect.w) * scaleX && mouseY >= ChooseEnchantress.dstRect.y * scaleY && mouseY <= (ChooseEnchantress.dstRect.y + ChooseEnchantress.dstRect.h) * scaleY)
					ChooseEnchantress.colour = { 180, 180, 180, 255 };
				else
					ChooseEnchantress.colour = { 0, 0, 0, 255 };

				if (mouseX >= ChooseKnight.dstRect.x * scaleX && mouseX <= (ChooseKnight.dstRect.x + ChooseKnight.dstRect.w) * scaleX && mouseY >= ChooseKnight.dstRect.y * scaleY && mouseY <= (ChooseKnight.dstRect.y + ChooseKnight.dstRect.h) * scaleY)
					ChooseKnight.colour = { 180, 180, 180, 255 };
				else
					ChooseKnight.colour = { 0, 0, 0, 255 };
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (mouseX >= ChooseEnchantress.dstRect.x * scaleX && mouseX <= (ChooseEnchantress.dstRect.x + ChooseEnchantress.dstRect.w) * scaleX && mouseY >= ChooseEnchantress.dstRect.y * scaleY && mouseY <= (ChooseEnchantress.dstRect.y + ChooseEnchantress.dstRect.h) * scaleY)
					{
						SDL_DestroyTexture(ChooseEnchantress.text);
						SDL_DestroyTexture(ChooseKnight.text);

						ChooseEnchantress.text = NULL;
						ChooseKnight.text = NULL;

						menu.isRunning = true;

						character.isEnchantress = true;
						character.isKnight = false;
						menu.isHeroChoice = false;
					}

					if (mouseX >= ChooseKnight.dstRect.x * scaleX && mouseX <= (ChooseKnight.dstRect.x + ChooseKnight.dstRect.w) * scaleX && mouseY >= ChooseKnight.dstRect.y * scaleY && mouseY <= (ChooseKnight.dstRect.y + ChooseKnight.dstRect.h) * scaleY)
					{
						SDL_DestroyTexture(ChooseEnchantress.text);
						SDL_DestroyTexture(ChooseKnight.text);

						ChooseEnchantress.text = NULL;
						ChooseKnight.text = NULL;

						menu.isRunning = true;

						character.isEnchantress = false;
						character.isKnight = true;
						menu.isHeroChoice = false;
					}
				}
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
			}
		}

		SDL_RenderCopy(ren, menu.backgroundTexture, &menu.backgroundRect, NULL);

		SDL_DestroyTexture(ChooseEnchantress.text);
		ChooseEnchantress.text = GenerateTextureText(ChooseEnchantress.stringText, font, &ChooseEnchantress.textRect, ChooseEnchantress.colour);
		SDL_RenderCopyF(ren, ChooseEnchantress.text, &ChooseEnchantress.textRect, &ChooseEnchantress.dstRect);

		SDL_DestroyTexture(ChooseKnight.text);
		ChooseKnight.text = GenerateTextureText(ChooseKnight.stringText, font, &ChooseKnight.textRect, ChooseKnight.colour);
		SDL_RenderCopyF(ren, ChooseKnight.text, &ChooseKnight.textRect, &ChooseKnight.dstRect);

		SDL_DestroyTexture(enchantressPNG);
		enchantressPNG = LoadTexture("Menu\\Enchantress.png", &enchantressPNGRect);
		SDL_RenderCopyF(ren, enchantressPNG, &enchantressPNGRect, &enchantressDstRect);

		SDL_DestroyTexture(knightPNG);
		knightPNG = LoadTexture("Menu\\Knight.png", &knightPNGRect);
		SDL_RenderCopyF(ren, knightPNG, &knightPNGRect, &knightDstRect);

		SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(ChooseEnchantress.text);
	SDL_DestroyTexture(ChooseKnight.text);

	SDL_DestroyTexture(enchantressPNG);
	SDL_DestroyTexture(knightPNG);

	SDL_DestroyTexture(menu.backgroundTexture);
	menu.backgroundTexture = NULL;

	TTF_CloseFont(font);
}

void ResumeMenu(Menu& menu, MenuButtons& ResumeGame, MenuButtons& ReturnToMainMenu, MenuButtons& Exit)
{
	SDL_RenderClear(ren);
	menu.backgroundTexture = LoadTexture("Menu\\MenuBackground.png", &menu.backgroundRect);

	TTF_Font* font = TTF_OpenFont("Monocraft.ttf", 100);

	ResumeGame.dstRect.w = 300;
	ResumeGame.dstRect.h = 60;
	ResumeGame.dstRect.x = winWidth * 1.f / 2 - ResumeGame.dstRect.w / 2;
	ResumeGame.dstRect.y = winHeight * 1.f / 2 - ResumeGame.dstRect.h / 2;

	ReturnToMainMenu.dstRect.w = 500;
	ReturnToMainMenu.dstRect.h = 60;
	ReturnToMainMenu.dstRect.x = winWidth * 1.f / 2 - ReturnToMainMenu.dstRect.w / 2;
	ReturnToMainMenu.dstRect.y = winHeight * 1.f / 2 + ReturnToMainMenu.dstRect.h / 2;

	Exit.dstRect.w = 100;
	Exit.dstRect.h = 60;
	Exit.dstRect.x = winWidth * 1.f / 2 - Exit.dstRect.w / 2;
	Exit.dstRect.y = winHeight * 1.f / 2 + Exit.dstRect.h / 2 * 5 + 30;

	strcpy_s(ResumeGame.stringText, 100, "Resume Game");
	strcpy_s(ReturnToMainMenu.stringText, 100, "Return To Main Menu");
	strcpy_s(Exit.stringText, 100, "Exit");

	SDL_Event event;
	int mouseX, mouseY;
	while (menu.isOpen)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				menu.isRunning = false;
				menu.isOpen = false;
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (mouseX >= ResumeGame.dstRect.x * scaleX && mouseX <= (ResumeGame.dstRect.x + ResumeGame.dstRect.w) * scaleX && mouseY >= ResumeGame.dstRect.y * scaleY && mouseY <= (ResumeGame.dstRect.y + ResumeGame.dstRect.h) * scaleY)
					ResumeGame.colour = { 180, 180, 180, 255 };
				else
					ResumeGame.colour = { 0, 0, 0, 255 };

				if (mouseX >= ReturnToMainMenu.dstRect.x * scaleX && mouseX <= (ReturnToMainMenu.dstRect.x + ReturnToMainMenu.dstRect.w) * scaleX && mouseY >= ReturnToMainMenu.dstRect.y * scaleY && mouseY <= (ReturnToMainMenu.dstRect.y + ReturnToMainMenu.dstRect.h) * scaleY)
					ReturnToMainMenu.colour = { 180, 180, 180, 255 };
				else
					ReturnToMainMenu.colour = { 0, 0, 0, 255 };

				if (mouseX >= Exit.dstRect.x * scaleX && mouseX <= (Exit.dstRect.x + Exit.dstRect.w) * scaleX && mouseY >= Exit.dstRect.y * scaleY && mouseY <= (Exit.dstRect.y + Exit.dstRect.h) * scaleY)
					Exit.colour = { 180, 180, 180, 255 };
				else
					Exit.colour = { 0, 0, 0, 255 };
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (mouseX >= ResumeGame.dstRect.x * scaleX && mouseX <= (ResumeGame.dstRect.x + ResumeGame.dstRect.w) * scaleX && mouseY >= ResumeGame.dstRect.y * scaleY && mouseY <= (ResumeGame.dstRect.y + ResumeGame.dstRect.h) * scaleY)
					{
						menu.isOpen = false;
						menu.isRunning = true;
					}

					if (mouseX >= ReturnToMainMenu.dstRect.x * scaleX && mouseX <= (ReturnToMainMenu.dstRect.x + ReturnToMainMenu.dstRect.w) * scaleX && mouseY >= ReturnToMainMenu.dstRect.y * scaleY && mouseY <= (ReturnToMainMenu.dstRect.y + ReturnToMainMenu.dstRect.h) * scaleY)
					{
						menu.isOpen = false;
						menu.isStart = true;
						menu.isRunning = false;
						menu.isReturn = true;
					}

					if (mouseX >= Exit.dstRect.x * scaleX && mouseX <= (Exit.dstRect.x + Exit.dstRect.w) * scaleX && mouseY >= Exit.dstRect.y * scaleY && mouseY <= (Exit.dstRect.y + Exit.dstRect.h) * scaleY)
					{
						menu.isRunning = false;
						menu.isOpen = false;
					}
				}
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
			}
		}
		SDL_RenderCopy(ren, menu.backgroundTexture, &menu.backgroundRect, NULL);

		SDL_DestroyTexture(ResumeGame.text);
		ResumeGame.text = GenerateTextureText(ResumeGame.stringText, font, &ResumeGame.textRect, ResumeGame.colour);
		SDL_RenderCopyF(ren, ResumeGame.text, &ResumeGame.textRect, &ResumeGame.dstRect);

		SDL_DestroyTexture(ReturnToMainMenu.text);
		ReturnToMainMenu.text = GenerateTextureText(ReturnToMainMenu.stringText, font, &ReturnToMainMenu.textRect, ReturnToMainMenu.colour);
		SDL_RenderCopyF(ren, ReturnToMainMenu.text, &ReturnToMainMenu.textRect, &ReturnToMainMenu.dstRect);

		SDL_DestroyTexture(Exit.text);
		Exit.text = GenerateTextureText(Exit.stringText, font, &Exit.textRect, Exit.colour);
		SDL_RenderCopyF(ren, Exit.text, &Exit.textRect, &Exit.dstRect);

		SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(ResumeGame.text);
	SDL_DestroyTexture(ReturnToMainMenu.text);
	SDL_DestroyTexture(Exit.text);

	ResumeGame.text = NULL;
	ReturnToMainMenu.text = NULL;
	Exit.text = NULL;

	SDL_DestroyTexture(menu.backgroundTexture);
	menu.backgroundTexture = NULL;

	TTF_CloseFont(font);
}