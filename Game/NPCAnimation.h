#pragma once
#include "Basic.h"

struct SDL_NPCRect
{
	int type = 0;
	SDL_Rect rect = {};
	SDL_FRect dstRect = {};
	int frame = 0;
	int frameCount = 0;
	int currentFrametime = 0;
	int maxFrametime = 0;
};

struct NPC
{
	int count = 0;
	SDL_Rect rect = {};
	int index = 0;
	SDL_Texture* Texture = NULL;
	SDL_NPCRect* rects = NULL;
};
extern NPC npc;

SDL_NPCRect* GetSpaceForNPC();
void NPCAnimation();
void FreeSpaceForNPC();