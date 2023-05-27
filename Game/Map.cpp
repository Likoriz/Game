#include "Map.h"
#include "Motion.h"
#include "NPCAnimation.h"
#include "Menu.h"
#include "Basic.h"

Map map;
TileSet tile;
MapHitbox hitbox;
NPC npc;

void Save()
{
	FILE* file;
	if (fopen_s(&file, map.fileSavePath, "wt") == 0)
	{
		fprintf(file, "%d\n", map.level);
		fprintf(file, "%f %f\n", character.x, character.y);
		fprintf(file, "%d %d\n", character.isEnchantress, character.isKnight);

		fclose(file);
	}
	else
	{
		printf("Couldn't open the save file!");
		DeInit(1);
	}
}

void LoadSave()
{
	FILE* file;
	if (fopen_s(&file, map.fileSavePath, "rt") == 0)
	{
		fscanf_s(file, "%d", &map.level);
		fscanf_s(file, "%f%f", &character.x, &character.y);

		int enchantress = 0, knight = 0;
		fscanf_s(file, "%d%d", &enchantress, &knight);
		character.isEnchantress = enchantress;
		character.isKnight = knight;

		fclose(file);
	}
	else
	{
		printf("Couldn't open the save file!");
		DeInit(1);
	}
}

void LoadMap()
{
	switch (map.level)
	{
	case 1:
		strcpy_s(map.fileMapPath, "Maps\\Map1\\map.txt");
		strcpy_s(tile.texturePath, "Maps\\Map1\\map.png");
		strcpy_s(hitbox.fileHitboxPath, "Maps\\Map1\\maphitbox.txt");
		break;
	}

	if (fopen_s(&map.file, map.fileMapPath, "rt") == 0)
	{
		fscanf_s(map.file, "%d%d", &map.widthC, &map.heightR);
		fscanf_s(map.file, "%d%d", &tile.width, &tile.height);
		fscanf_s(map.file, "%d%d", &tile.countC, &tile.countR);

		map.terrain = GetSpaceForMap();

		for (int i = 0; i < map.heightR; i++)
			for (int j = 0; j < map.widthC; j++)
				fscanf_s(map.file, "%d", &map.terrain[i][j]);
		fclose(map.file);
	}
	else
	{
		printf("Couldn't load the map!");
		DeInit(1);
	}

	if (fopen_s(&hitbox.file, hitbox.fileHitboxPath, "rt") == 0)
	{
		fscanf_s(hitbox.file, "%d%d", &hitbox.widthC, &hitbox.heightR);
		fscanf_s(hitbox.file, "%d%d", &hitbox.width, &hitbox.height);
	    fscanf_s(hitbox.file, "%d", &hitbox.count);
		fscanf_s(hitbox.file, "%d", &npc.count);

		hitbox.hitboxesCode = GetSpaceForHitboxesCode();

		for (int i = 0; i < hitbox.heightR; i++)
			for (int j = 0; j < hitbox.widthC; j++)
				fscanf_s(hitbox.file, "%d", &hitbox.hitboxesCode[i][j]);
		fclose(hitbox.file);
	}
	else
	{
		printf("Couldn't load the hitboxes!");
		DeInit(1);
	}

	hitbox.hitboxes = GetSpaceForHitboxes();
	npc.rects = GetSpaceForNPC();

	for (int i = 0; i < npc.count; i++)
		npc.rects[i].currentFrametime = 0;

	npc.Texture = LoadTexture("NPC\\NPC.png", &npc.rect);
}

void UpdateMap()
{
	SDL_DestroyTexture(tile.texture);
	tile.texture = LoadTexture(tile.texturePath, &tile.tile);
	tile.tile.w = tile.width;
	tile.tile.h = tile.height;

	if (character.y >= winHeight * 1.f / 2)
	{
		if (character.y <= tile.dstTile.h * map.heightR - winHeight * 1.f / 2)
			tile.dstTile.y = winHeight * 1.f / 2 - character.y;
		else
			tile.dstTile.y = 0 - (tile.dstTile.h * map.heightR - winHeight);
	}
	else
		tile.dstTile.y = 0;

	int k = 0;
	int z = 0;
	for (int i = 0; i < map.heightR; i++)
	{
		for (int j = 0; j < map.widthC; j++)
		{
			tile.tile.x = tile.width * (map.terrain[i][j] % tile.countC);
			if (map.terrain[i][j] / 10 == 0)
				tile.tile.y = 0;
			else
				if (map.terrain[i][j] / 10 == 1)
					tile.tile.y = tile.height;
				else
					if (map.terrain[i][j] / 10 == 2)
						tile.tile.y = tile.height * 2;
			tile.dstTile.w = tile.width * MAPSCALE;
			tile.dstTile.h = tile.height * MAPSCALE;

			if (character.x >= winWidth * 1.f / 2)
			{
				if (character.x <= tile.dstTile.w * map.widthC - winWidth * 1.f / 2)
					tile.dstTile.x = winWidth * 1.f / 2 - character.x + tile.dstTile.w * j;
				else
					tile.dstTile.x = tile.dstTile.w * j - (tile.dstTile.w * map.widthC - winWidth);
			}
			else
				tile.dstTile.x = tile.dstTile.w * j;

			if (hitbox.hitboxesCode[i][j] == 1)
			{
				hitbox.hitboxes[k].x = tile.dstTile.x;
				hitbox.hitboxes[k].y = tile.dstTile.y;
				hitbox.hitboxes[k].w = tile.dstTile.w;
				hitbox.hitboxes[k].h = tile.dstTile.h;
				k++;
			}
			if (hitbox.hitboxesCode[i][j] > 1 && hitbox.hitboxesCode[i][j] < 13)
			{
				hitbox.hitboxes[k].x = tile.dstTile.x;
				hitbox.hitboxes[k].y = tile.dstTile.y;
				hitbox.hitboxes[k].w = tile.dstTile.w;
				hitbox.hitboxes[k].h = tile.dstTile.h;

				npc.rects[z].dstRect.x = hitbox.hitboxes[k].x;
				npc.rects[z].dstRect.y = hitbox.hitboxes[k].y;
				npc.rects[z].dstRect.w = hitbox.hitboxes[k].w;
				npc.rects[z].dstRect.h = hitbox.hitboxes[k].h;

				switch (hitbox.hitboxesCode[i][j])
				{
				case 8:
					npc.rects[z].type = 8;
					npc.rects[z].frameCount = 5;
					npc.rects[z].rect.y = npc.rects[z].rect.h * 6;
					break;
				case 12:
					npc.rects[z].type = 12;
					npc.rects[z].frameCount = 5;
					npc.rects[z].rect.y = npc.rects[z].rect.h * 10;
					break;
				}
				k++;
				z++;
			}

			SDL_RenderCopyF(ren, tile.texture, &tile.tile, &tile.dstTile);
		}
		tile.dstTile.y += tile.dstTile.h;
	}
	//SDL_RenderDrawRects(ren, hitbox.hitboxes, hitbox.count);
}

void DeleteMap()
{
	FreeSpaceForMap();
	FreeSpaceForHitboxesCode();
	FreeSpaceForHitboxes();
	FreeSpaceForNPC();
}

int** GetSpaceForMap()
{
	int** terrain = (int**)malloc(map.heightR * sizeof(int*));
	for (int i = 0; i < map.heightR; i++)
		terrain[i] = (int*)malloc(map.widthC * sizeof(int));
	return terrain;
}

void FreeSpaceForMap()
{
	for (int i = 0; i < map.heightR; i++)
		free(map.terrain[i]);
	free(map.terrain);
	map.terrain = NULL;
}

int** GetSpaceForHitboxesCode()
{
	int** hitboxesCode = (int**)malloc(hitbox.heightR * sizeof(int*));
	for (int i = 0; i < hitbox.heightR; i++)
		hitboxesCode[i] = (int*)malloc(hitbox.widthC * sizeof(int));
	return hitboxesCode;
}

void FreeSpaceForHitboxesCode()
{
	for (int i = 0; i < hitbox.heightR; i++)
		free(hitbox.hitboxesCode[i]);
	free(hitbox.hitboxesCode);
	hitbox.hitboxesCode = NULL;
}

SDL_Rect* GetSpaceForHitboxes()
{
	SDL_Rect* hitboxes = (SDL_Rect*)malloc(hitbox.count * sizeof(SDL_Rect));

	return hitboxes;
}

void FreeSpaceForHitboxes()
{
	free(hitbox.hitboxes);
	hitbox.hitboxes = NULL;
}