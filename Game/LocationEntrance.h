#pragma once
#include "Basic.h"

struct SDL_EntranceRect
{
	int type = 0;
	SDL_FRect dstRect = {};
};

struct Entrance
{
	int count = 0;
	SDL_EntranceRect* rects = NULL;
};
extern Entrance entrance;

SDL_EntranceRect* GetSpaceForEntrance();
void FreeSpaceForEntrance();