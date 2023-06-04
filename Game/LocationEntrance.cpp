#include "Basic.h"
#include "LocationEntrance.h"

SDL_EntranceRect* GetSpaceForEntrance()
{
	SDL_EntranceRect* rects = (SDL_EntranceRect*)malloc(entrance.count * sizeof(SDL_EntranceRect));

	return rects;
}

void FreeSpaceForEntrance()
{
	free(entrance.rects);
	entrance.rects = NULL;
}