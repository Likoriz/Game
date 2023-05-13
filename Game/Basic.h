#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#define DEFAULTSCALE 1.5f
#define WIDTH 1920
#define HEIGHT 1017

extern SDL_Window* win;
extern SDL_Renderer* ren;

extern int winWidth;
extern int winHeight;

extern float scaleX;
extern float scaleY;

struct Time
{
	int lastTime = 0;
	int newTime = 0;
	int dt = 0;
};
extern Time timer;

SDL_Texture* LoadTexture(const char* filename, SDL_Rect* rect);

SDL_Texture* GenerateTextureText(const char* text, TTF_Font* font, SDL_Rect* area, SDL_Color colour);

struct Character;

void Init();

void DeInit(int error);