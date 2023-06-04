#include "Basic.h"
#include "Motion.h"
#include "Map.h"
#include "LocationEntrance.h"

SDL_EntranceRect* GetSpaceForEntrance()
{
	SDL_EntranceRect* rects = (SDL_EntranceRect*)malloc(entrance.count * sizeof(SDL_EntranceRect));

	return rects;
}

double CheckEntrance()
{
	double s = 0;
	double minS = LONG_MAX;
	for (int i = 0; i < entrance.count; i++)
	{
		s = sqrt((entrance.rects[i].dstRect.x - character.destinationRect.x) * (entrance.rects[i].dstRect.x - character.destinationRect.x) + (entrance.rects[i].dstRect.y - character.destinationRect.y) * (entrance.rects[i].dstRect.y - character.destinationRect.y));
		if (s < minS)
		{
			minS = s;
			entrance.index = i;
		}
	}
	return minS;
}

void Enter()
{
	switch(map.level)
	{
	case 1:
		switch (entrance.rects[entrance.index].type)
		{
		case 2:
			character.x = 200;
			character.y = 2944;
			break;
		}
		break;
	case 2:
		switch (entrance.rects[entrance.index].type)
		{
		case 1:
			character.x = 2844;
			character.y = 384;
			break;
		}
		break;
	}
	map.level = entrance.rects[entrance.index].type;
}

void FreeSpaceForEntrance()
{
	free(entrance.rects);
	entrance.rects = NULL;
}