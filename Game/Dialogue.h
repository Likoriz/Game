#pragma once
#include "NPCAnimation.h"

#define MINSFROMNPC 50.f

struct DialogueBox
{
	int progress = 0;

	SDL_Texture* boxTexture = NULL;
	SDL_Rect boxTextureRect = {};
	SDL_Rect boxDstRect = { 350, 450, 600, 200 };
	SDL_Color colour = { 0, 0, 0, 255 };

	char stringText1[50] = "";
	SDL_Rect textRect1;
	SDL_Rect dstRect1 = { 400, 475, 500, 30 };
	SDL_Texture* text1 = NULL;

	char stringText2[50] = "";
	SDL_Rect textRect2;
	SDL_Rect dstRect2 = { 400, 515, 500, 30 };
	SDL_Texture* text2 = NULL;

	char stringText3[50] = "";
	SDL_Rect textRect3;
	SDL_Rect dstRect3 = { 400, 555, 500, 30 };
	SDL_Texture* text3 = NULL;

	char stringText4[50] = "";
	SDL_Rect textRect4;
	SDL_Rect dstRect4 = { 400, 595, 500, 30 };
	SDL_Texture* text4 = NULL;
};
extern DialogueBox dialogueBox;

void Dialogue();
double CheckNPC();