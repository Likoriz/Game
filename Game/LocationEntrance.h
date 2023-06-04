#pragma once
#include "Basic.h"

#define MINSFROMENTRANCE 140.f

struct SDL_EntranceRect
{
	int type = 0;
	SDL_FRect dstRect = {};
};

struct Entrance
{
	int count = 0;
	int index = 0;
	SDL_EntranceRect* rects = NULL;
};
extern Entrance entrance;

SDL_EntranceRect* GetSpaceForEntrance();
double CheckEntrance();
void Enter();
void FreeSpaceForEntrance();