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
		case 3:
			character.x = 200;
			character.y = 864;
			break;
		case 4:
			character.x = 160;
			character.y = 2700;
			break;
		}
		break;
	case 3:
		switch (entrance.rects[entrance.index].type)
		{
		case 2:
			character.x = 3868;
			character.y = 3328;
			break;
		}
		break;
	case 4:
		switch (entrance.rects[entrance.index].type)
		{
		case 2:
			character.x = 2220;
			character.y = 3540;
			break;
		case 5:
			character.x = 512;
			character.y = 1536;
			break;
		}
		break;
	case 5:
		switch (entrance.rects[entrance.index].type)
		{
		case 4:
			character.x = 128;
			character.y = 1408;
			break;
		case 6:
			character.x = 512;
			character.y = 1536;
			break;
		}
		break;
	case 6:
		switch (entrance.rects[entrance.index].type)
		{
		case 5:
			character.x = 2048;
			character.y = 1156;
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