#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Basic.h"

SDL_Texture* LoadTexture(const char* filename, SDL_Rect* rect)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == NULL)
	{
		printf("Couldn't load image %s! Error: %s", filename, SDL_GetError());
		system("pause");
		DeInit(1);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	*rect = { 0, 0, surface->w, surface->h };

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* GenerateTextureText(const char* stringText, TTF_Font* font, SDL_Rect* area, SDL_Color colour)
{
	SDL_Surface* surface = TTF_RenderText_Blended(font, stringText, colour);
	*area = { 0, 0, surface->w, surface->h };
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void DeInit(int error)
{
	if (ren != NULL)
		SDL_DestroyRenderer(ren);
	if (win != NULL)
		SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error);
}

void Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Couldn't init SDL! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0)
	{
		printf("Couldn't init SDL_Image! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
	if (res & IMG_INIT_PNG)
		printf("Init PNG\n");
	if (res & IMG_INIT_JPG)
		printf("Init JPG\n");

	if (TTF_Init() != NULL)
	{
		printf("Couldn't init SDL_TTF! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	win = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("Couldn't create the window! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Couldn't create the renderer! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
}