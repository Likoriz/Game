#include "Map.h"
#include "Motion.h"
#include "NPCAnimation.h"
#include "Menu.h"
#include "LocationEntrance.h"
#include "Basic.h"

Map map;
TileSet tile;
MapHitbox hitbox;
NPC npc;
Entrance entrance;
Environment environment;

void Save()
{
	FILE* file;
	if (fopen_s(&file, map.fileSavePath, "wt") == 0)
	{
		fprintf(file, "%d\n", map.level);
		fprintf(file, "%f %f\n", character.x, character.y);
		fprintf(file, "%d %d\n", character.isEnchantress, character.isKnight);

		fprintf(file, "%d\n", character.quest);

		fprintf(file, "%d\n", quest.bread);
		fprintf(file, "%d\n", quest.monsters);
		fprintf(file, "%d\n", quest.sewers);
		fprintf(file, "%d\n", quest.boss);
		fprintf(file, "%d\n", quest.end);

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

		int questy = 0;
		fscanf_s(file, "%d", &questy);
		character.quest = questy;

		int bread = 0, monsters = 0, sewers = 0, boss = 0, ending = 0;
		fscanf_s(file, "%d%d%d%d%d", &bread, &monsters, &sewers, &boss, &ending);
		quest.bread = bread;
		quest.monsters = monsters;
		quest.sewers = sewers;
		quest.boss = boss;
		quest.end = ending;

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
		//environment.isDark = false;
		//environment.isMisty = false;
		//character.isBlownAway = false;
		break;
	case 2:
		strcpy_s(map.fileMapPath, "Maps\\Map2\\map.txt");
		strcpy_s(tile.texturePath, "Maps\\Map2\\map.png");
		strcpy_s(hitbox.fileHitboxPath, "Maps\\Map2\\maphitbox.txt");
		environment.isDark = false;
		environment.isMisty = false;
		//character.isBlownAway = false;
		break;
	case 3:
		strcpy_s(map.fileMapPath, "Maps\\Map3\\map.txt");
		strcpy_s(tile.texturePath, "Maps\\Map3\\map.png");
		strcpy_s(hitbox.fileHitboxPath, "Maps\\Map3\\maphitbox.txt");
		environment.isDark = true;
		//environment.isMisty = false;
		//character.isBlownAway = false;
		break;
	case 4:
		strcpy_s(map.fileMapPath, "Maps\\Map4\\map.txt");
		strcpy_s(tile.texturePath, "Maps\\Map4\\map.png");
		strcpy_s(hitbox.fileHitboxPath, "Maps\\Map4\\maphitbox.txt");

		environment.isMisty = true;
		character.isBlownAway = false;
		break;
	case 5:
		strcpy_s(map.fileMapPath, "Maps\\Map5\\map.txt");
		strcpy_s(tile.texturePath, "Maps\\Map5\\map.png");
		strcpy_s(hitbox.fileHitboxPath, "Maps\\Map5\\maphitbox.txt");
		environment.isMisty = false;
		character.isBlownAway = true;
		break;
	case 6:
		strcpy_s(map.fileMapPath, "Maps\\Map6\\map.txt");
		strcpy_s(tile.texturePath, "Maps\\Map6\\map.png");
		strcpy_s(hitbox.fileHitboxPath, "Maps\\Map6\\maphitbox.txt");
		character.isBlownAway = false;
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
		fscanf_s(hitbox.file, "%d", &entrance.count);

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
	entrance.rects = GetSpaceForEntrance();

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

	int barrierCount = 0;
	int npcCount = 0;
	int entranceCount = 0;
	for (int i = 0; i < map.heightR; i++)
	{
		for (int j = 0; j < map.widthC; j++)
		{
			tile.tile.x = tile.width * (map.terrain[i][j] % tile.countC);
			tile.tile.y = tile.height * (map.terrain[i][j] / 10);
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

			hitbox.hitboxes[barrierCount].x = tile.dstTile.x;
			hitbox.hitboxes[barrierCount].y = tile.dstTile.y;
			hitbox.hitboxes[barrierCount].w = tile.dstTile.w;
			hitbox.hitboxes[barrierCount].h = tile.dstTile.h;

			if (hitbox.hitboxesCode[i][j] < 0 && hitbox.hitboxesCode[i][j] > -7)
			{
				entrance.rects[entranceCount].dstRect.x = hitbox.hitboxes[barrierCount].x;
				entrance.rects[entranceCount].dstRect.y = hitbox.hitboxes[barrierCount].y;
				entrance.rects[entranceCount].dstRect.w = hitbox.hitboxes[barrierCount].w;
				entrance.rects[entranceCount].dstRect.h = hitbox.hitboxes[barrierCount].h;

				switch (hitbox.hitboxesCode[i][j])
				{
				case -1:
					entrance.rects[entranceCount].type = 1;
					break;
				case -2:
					entrance.rects[entranceCount].type = 2;
					break;
				case -3:
					entrance.rects[entranceCount].type = 3;
					break;
				case -4:
					entrance.rects[entranceCount].type = 4;
					break;
				case -5:
					entrance.rects[entranceCount].type = 5;
					break;
				case -6:
					entrance.rects[entranceCount].type = 6;
					break;
				}
				barrierCount++;
				entranceCount++;
			}

			if (hitbox.hitboxesCode[i][j] == 1)
			{
				barrierCount++;
			}

			if (hitbox.hitboxesCode[i][j] > 1 && hitbox.hitboxesCode[i][j] < 15)
			{
				npc.rects[npcCount].dstRect.x = hitbox.hitboxes[barrierCount].x;
				npc.rects[npcCount].dstRect.y = hitbox.hitboxes[barrierCount].y;
				npc.rects[npcCount].dstRect.w = hitbox.hitboxes[barrierCount].w;
				npc.rects[npcCount].dstRect.h = hitbox.hitboxes[barrierCount].h;

				switch (hitbox.hitboxesCode[i][j])
				{
				case 2:
					npc.rects[npcCount].type = 2;
					npc.rects[npcCount].frameCount = 4;
					npc.rects[npcCount].rect.y = 0;
					break;
				case 3:
					npc.rects[npcCount].type = 3;
					npc.rects[npcCount].frameCount = 4;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h;
					break;
				case 4:
					npc.rects[npcCount].type = 4;
					npc.rects[npcCount].frameCount = 4;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 2;
					break;
				case 5:
					npc.rects[npcCount].type = 5;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 3;
					break;
				case 6:
					npc.rects[npcCount].type = 6;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 4;
					break;
				case 7:
					npc.rects[npcCount].type = 7;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 5;
					break;
				case 8:
					npc.rects[npcCount].type = 8;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 6;
					break;
				case 9:
					npc.rects[npcCount].type = 9;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 7;
					break;
				case 10:
					npc.rects[npcCount].type = 10;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 8;
					break;
				case 11:
					npc.rects[npcCount].type = 11;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 9;
					break;
				case 12:
					npc.rects[npcCount].type = 12;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 10;
					break;
				case 13:
					npc.rects[npcCount].type = 13;
					npc.rects[npcCount].frameCount = 5;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 11;
					break;
				case 14:
					npc.rects[npcCount].type = 14;
					npc.rects[npcCount].frameCount = 2;
					npc.rects[npcCount].rect.y = npc.rects[npcCount].rect.h * 12;
					break;
				}
				barrierCount++;
				npcCount++;
			}

			SDL_RenderCopyF(ren, tile.texture, &tile.tile, &tile.dstTile);
		}
		tile.dstTile.y += tile.dstTile.h;
	}

	if (environment.isDark)
	{
		SDL_DestroyTexture(environment.darkness);
		environment.darkDst = { character.destinationRect.x - 1250, character.destinationRect.y - 630, 2600, 1439 };
		environment.darkness = LoadTexture("Assets\\Dark.png", &environment.darkRect);
		SDL_RenderCopyF(ren, environment.darkness, &environment.darkRect, &environment.darkDst);
	}
	else
		if (environment.darkness)
			SDL_DestroyTexture(environment.darkness);

	if (environment.enemies_list_DOT_amount_of_enemies_at_the_field == 0 && environment.isMisty)//ÑÞÄÀ ÊÎËÈ×ÅÑÒÂÎ ÂÐÀÃÎÂ ÍÀ ÏÎËÅ
	{
		SDL_DestroyTexture(environment.mist);
		environment.mist = LoadTexture("Assets\\Mist.png", &environment.mistRect);
		SDL_RenderCopyF(ren, environment.mist, &environment.mistRect, NULL);
		if (environment.mistTimer > 150)
		{
			printf("-5 hp\n");
			environment.mistTimer = 0;
		}
		else
			environment.mistTimer++;
	}
	else
		if (environment.mist)
			SDL_DestroyTexture(environment.mist);
}

void DeleteMap()
{
	FreeSpaceForMap();
	FreeSpaceForHitboxesCode();
	FreeSpaceForHitboxes();
	FreeSpaceForNPC();
	FreeSpaceForEntrance();
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