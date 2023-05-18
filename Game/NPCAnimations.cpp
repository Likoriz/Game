#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "NPCAnimation.h"
#include "Basic.h"

SDL_NPCRect* GetSpaceForNPC()
{
	SDL_NPCRect* rects = (SDL_NPCRect*)malloc(npc.count * sizeof(SDL_NPCRect));

	return rects;
}

void NPCAnimation()
{
	for (int i = 0; i < npc.count; i++)
	{
		npc.rects[i].rect.w = 32;
		npc.rects[i].rect.h = 32;

		npc.rects[i].maxFrametime = 1000 / npc.rects[i].frameCount;
		npc.rects[i].currentFrametime += timer.dt;

		if (npc.rects[i].currentFrametime >= npc.rects[i].maxFrametime)
		{
			npc.rects[i].currentFrametime -= npc.rects[i].maxFrametime;
			npc.rects[i].frame = (npc.rects[i].frame + 1) % npc.rects[i].frameCount;
			npc.rects[i].rect.x = npc.rects[i].rect.w * npc.rects[i].frame;
		}
		SDL_RenderCopyF(ren, npc.Texture, &npc.rects[i].rect, &npc.rects[i].dstRect);
	}
}

void FreeSpaceForNPC()
{
	SDL_DestroyTexture(npc.Texture);
	npc.Texture = NULL;
	free(npc.rects);
	npc.rects = NULL;
}