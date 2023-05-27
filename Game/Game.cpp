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
Audio audio;

int main(int argc, char* argv[])
{
	Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 4, 2048) < 0)
		printf("%s\n", Mix_GetError());

	SDL_Event event;
	double minS = 0;

	SDL_RenderSetScale(ren, scaleX, scaleY);
	winWidth /= scaleX;
	winHeight /= scaleY;

	StartMenu();
	if (menu.isHeroChoice)
		HeroChoice();

	if (menu.isLoad)
	{
		LoadSave();
		menu.isLoad = false;
	}

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

	LoadMap();

	PlayMusic("Music\\Usual.wav");

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
					case SDL_SCANCODE_W:
						//character.animation = MOVING; 
						character.isUp = true;
						break;//character.isUp = true;	character.isIdle = false;									break;
					case SDL_SCANCODE_S:
						//character.animation = MOVING; 
						character.isDown = true;
						break;//character.isDown = true; character.isIdle = false;									break;
					case SDL_SCANCODE_D:
						//character.animation = MOVING; 
						character.isRight = true;
						break;//character.isRight = true; character.isIdle = false;								break;
					case SDL_SCANCODE_A:
						//character.animation = MOVING; 
						character.isLeft = true;
						break;//character.isLeft = true; character.isIdle = false;									break;
					case SDL_SCANCODE_LSHIFT:
						//character.animation = MOVING; 
						character.boostSpeed = true;
						character.speed = 225;
						break;//character.boostSpeed = true; character.speed = 225; character.isIdle = false;	break;
					case SDL_SCANCODE_E:
						minS = CheckNPC();
						if (minS <= MINSFROMNPC && !character.isMoving)
						{
							state.isGaming = false;
							state.isDialouge = true;
						}
						break;
					case SDL_SCANCODE_ESCAPE:
						menu.isOpen = true;
						ResumeMenu();
						if (menu.isReturn)
						{
							menu.isReturn = false;
							Mix_FreeMusic(audio.music);
							StartMenu();
							if (menu.isHeroChoice)
								HeroChoice();

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
							character.x = 150;
							character.y = 2000;

							PlayMusic("Music\\Usual.wav");
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
						break;
					}
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
					character.isUp = false;
					break;//character.isUp = false; character.isIdle = true;									break;
				case SDL_SCANCODE_S:
					character.isDown = false;
					break;//character.isDown = false; character.isIdle = true;									break;
				case SDL_SCANCODE_D:
					character.isRight = false;
					break;//character.isRight = false;	character.isIdle = true;								break;
				case SDL_SCANCODE_A:
					character.isLeft = false;
					break;//character.isLeft = false; character.isIdle = true;									break;
				case SDL_SCANCODE_LSHIFT:
					character.speed = 150;
					character.boostSpeed = false;
					break;// character.isIdle = true; break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (state.isGaming)
				{
					switch (event.button.button)
					{
					case SDL_BUTTON_LEFT:
						if (!Mix_Playing(1))
							PlaySound("Music\\FastSwing.wav", 1);
						//character.isAttack = true;
						character.animation = ATTACK;
						character.animationNew = ATTACK;
						character.countAttack++;
						if (character.countAttack == 2)
							character.countAttack = 0;
						break;
					case SDL_BUTTON_RIGHT:
						if (character.isEnchantress && !Mix_Playing(1))
							PlaySound("Music\\Spell.wav", 1);
						else
							if (!Mix_Playing(1))
								PlaySound("Music\\SeveralSwings.wav", 1);
						character.animation = ULT;
						character.animationNew = ULT;
						//character.isUlt = true;
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

		UpdateMap();
		NPCAnimation();

		if (state.isGaming)
			Motion();

		if (character.isMoving && !Mix_Playing(0))
			PlaySound("Music\\Step.wav", 0);

		Animation();

		if (state.isDialouge)
			Dialogue();

		character.animationOld = character.animationNew;

		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(character.playerTexture);
	DeleteMap();

	Mix_CloseAudio();

	DeInit(0);

	return 0;
}