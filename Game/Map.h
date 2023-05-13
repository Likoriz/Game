#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "NPCAnimation.h"
#include "Basic.h"

#define MAPSCALE 4.f

struct Map
{
	int widthC = 0, heightR = 0;
	int** terrain = NULL;
	int level = 1;

	char fileMapPath[30] = "";

	FILE* file;
};
extern Map map;

struct MapHitbox
{
	SDL_FRect dstHitbox = {};
	char fileHitboxPath[30] = "";

	int count = 0;
	int countR = 0, countC = 0;
	int widthC = 0, heightR = 0;
	int width = 0, height = 0;

	int** hitboxesCode = NULL;
	SDL_Rect* hitboxes = NULL;

	FILE* file;
};
extern MapHitbox hitbox;

struct TileSet
{
	SDL_Rect tile = {};
	SDL_FRect dstTile = {};
	SDL_Texture* texture = NULL;
	char texturePath[30] = "";

	int countR = 0, countC = 0;
	int width = 0, height = 0;
};
extern TileSet tile;

void LoadMap(Map& map, TileSet& tile, MapHitbox& hitbox, NPC& npc);
void UpdateMap(Map& map, TileSet& tile, MapHitbox& hitbox);
void DeleteMap(Map& map, TileSet& tile, MapHitbox& hitbox);
int** GetSpaceForMap();
void FreeSpaceForMap(Map& map);
int** GetSpaceForHitboxesCode();
void FreeSpaceForHitboxesCode(MapHitbox& hitbox);
SDL_Rect* GetSpaceForHitboxes();
void FreeSpaceForHitboxes(MapHitbox& hitbox);