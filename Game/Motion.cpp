#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Motion.h"
#include "Map.h"
#include "Basic.h"

Character character;

void Motion()
{
	float tmpx = character.x, tmpy = character.y;
	float tmpdstx = character.destinationRect.x, tmpdsty = character.destinationRect.y;

	bool isCanPass = true;

	if (character.isUp && character.y >= 0)
		tmpy -= character.speed * timer.dt / 1000;

	if (character.isDown && character.y < (tile.dstTile.h * map.heightR - character.destinationRect.h))
		tmpy += character.speed * timer.dt / 1000;

	if (character.isRight && character.x < (tile.dstTile.w * map.widthC - character.destinationRect.w))
	{
		character.direction = RIGHT;
		tmpx += character.speed * timer.dt / 1000;
	}

	if (character.isLeft && character.x >= 0)
	{
		character.direction = LEFT;
		tmpx -= character.speed * timer.dt / 1000;
	}

	character.destinationRect = { tmpx, tmpy, (float)character.playerRect.w, (float)character.playerRect.h };

	if (tmpx >= tile.dstTile.w * map.widthC - winWidth * 1.f / 2)
	{
		character.destinationRect.x = tmpx;
		while (character.destinationRect.x >= winWidth) 
			character.destinationRect.x -= (tile.dstTile.w * map.widthC - winWidth * 1.f / 2) - winWidth * 1.f / 2;
	}

	if (tmpy >= tile.dstTile.h * map.heightR - winHeight * 1.f / 2)
	{
		character.destinationRect.y = tmpy;
		while (character.destinationRect.y >= winHeight)
			character.destinationRect.y -= (tile.dstTile.h * map.heightR - winHeight * 1.f / 2) - winHeight * 1.f / 2;
	}

	if ((tmpx >= winWidth * 1.f / 2) && (tmpx < tile.dstTile.w * map.widthC - winWidth * 1.f / 2))
		character.destinationRect.x = (float)winWidth / 2;
	if ((tmpy >= winHeight * 1.f / 2) && (tmpy < tile.dstTile.h * map.heightR - winHeight * 1.f / 2))
		character.destinationRect.y = (float)winHeight / 2;
	
	character.animation = character.isUp || character.isDown || character.isRight || character.isLeft;

	character.playerHitbox.x = character.destinationRect.x + 45;
	character.playerHitbox.y = character.destinationRect.y + 109;
	character.playerHitbox.w = 40;
	character.playerHitbox.h = 19;

	for (int i = 0; i < hitbox.count; i++)
	{
		if (character.isLeft)
			if (character.playerHitbox.x >= hitbox.hitboxes[i].x 
				&& character.playerHitbox.x <= (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w) 
				&& (character.playerHitbox.y > hitbox.hitboxes[i].y || character.playerHitbox.y + character.playerHitbox.h > hitbox.hitboxes[i].y + 2) 
				&& character.playerHitbox.y < (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h - 2))
			{
				/*system("cls");
				printf("%d %d %d %d %d\n", i, hitbox.hitboxes[i].x, hitbox.hitboxes[i].y, hitbox.hitboxes[i].x + hitbox.hitboxes[i].w, hitbox.hitboxes[i].y + hitbox.hitboxes[i].h);
				printf("%f %f %f %f", character.playerHitbox.x, character.playerHitbox.y, character.playerHitbox.x + character.playerHitbox.w, character.playerHitbox.y + character.playerHitbox.h);*/
				isCanPass = false;
				break;
			}
		if (character.isUp)
			if ((character.playerHitbox.x > hitbox.hitboxes[i].x || character.playerHitbox.x + character.playerHitbox.w > hitbox.hitboxes[i].x + 2)
				&& character.playerHitbox.x < (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w - 2)
				&& character.playerHitbox.y >= hitbox.hitboxes[i].y 
				&& character.playerHitbox.y <= (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h))
			{
				/*system("cls");
				printf("%d %d %d %d %d\n", i, hitbox.hitboxes[i].x, hitbox.hitboxes[i].y, hitbox.hitboxes[i].x + hitbox.hitboxes[i].w, hitbox.hitboxes[i].y + hitbox.hitboxes[i].h);
				printf("%f %f %f %f", character.playerHitbox.x, character.playerHitbox.y, character.playerHitbox.x + character.playerHitbox.w, character.playerHitbox.y + character.playerHitbox.h);*/
				isCanPass = false;
				break;
			}
		if (character.isRight)
			if ((character.playerHitbox.x + character.playerHitbox.w >= hitbox.hitboxes[i].x 
				&& character.playerHitbox.x + character.playerHitbox.w <= (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w) 
				&& (character.playerHitbox.y > hitbox.hitboxes[i].y || character.playerHitbox.y + character.playerHitbox.h > hitbox.hitboxes[i].y + 2) 
				&& character.playerHitbox.y < (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h - 2)))
			{
				/*system("cls");
				printf("%d %d %d %d %d\n", i, hitbox.hitboxes[i].x, hitbox.hitboxes[i].y, hitbox.hitboxes[i].x + hitbox.hitboxes[i].w, hitbox.hitboxes[i].y + hitbox.hitboxes[i].h);
				printf("%f %f %f %f", character.playerHitbox.x, character.playerHitbox.y, character.playerHitbox.x + character.playerHitbox.w, character.playerHitbox.y + character.playerHitbox.h);*/
				isCanPass = false;
				break;
			}
		if (character.isDown)
		{
			if ((character.playerHitbox.x > hitbox.hitboxes[i].x || character.playerHitbox.x + character.playerHitbox.w > hitbox.hitboxes[i].x + 2) 
				&& character.playerHitbox.x < (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w - 2) 
				&& character.playerHitbox.y + character.playerHitbox.h >= hitbox.hitboxes[i].y 
				&& character.playerHitbox.y + character.playerHitbox.h <= (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h))
			{
				/*system("cls");
				printf("%d %d %d %d %d\n", i, hitbox.hitboxes[i].x, hitbox.hitboxes[i].y, hitbox.hitboxes[i].x + hitbox.hitboxes[i].w, hitbox.hitboxes[i].y + hitbox.hitboxes[i].h);
				printf("%f %f %f %f", character.playerHitbox.x, character.playerHitbox.y, character.playerHitbox.x + character.playerHitbox.w, character.playerHitbox.y + character.playerHitbox.h);*/
				isCanPass = false;
				break;
			}
		}
	}

	if (isCanPass)
	{
		character.x = tmpx;
		character.y = tmpy;
	}
	else
	{
		character.destinationRect.x = tmpdstx;
		character.destinationRect.y = tmpdsty;

		character.playerHitbox.x = character.destinationRect.x + 45;
		character.playerHitbox.y = character.destinationRect.y + 109;
		character.playerHitbox.w = 40;
		character.playerHitbox.h = 19;
	}
	//printf("%f %f %d %d | ", character.x, character.y, hitbox.hitboxes[110].x + hitbox.hitboxes[110].w, hitbox.hitboxes[110].y + hitbox.hitboxes[110].h);
	//printf("%f %f | ", character.destinationRect.x, character.destinationRect.y);
	//system("cls");
}

void Animation()
{
	if (character.animation)
	{
		if (character.boostSpeed)
			character.playerRect.y = character.playerRect.h * 2;
		else
			character.playerRect.y = character.playerRect.h;
		character.frameCount = 8;
		character.maxFrametime = 1000 / character.frameCount;
		character.currentFrametime += timer.dt;
		if (character.currentFrametime >= character.maxFrametime)
		{
			character.currentFrametime -= character.maxFrametime;
			character.frame = (character.frame + 1) % character.frameCount;
			character.playerRect.x = character.playerRect.w * character.frame;
		}
	}
	else
		if (character.isIdle)
		{
			character.playerRect.y = 0;
			character.frameCount = 10;
			character.maxFrametime = 1000 / character.frameCount;
			character.currentFrametime += timer.dt;
			if (character.currentFrametime >= character.maxFrametime)
			{
				character.currentFrametime -= character.maxFrametime;
				character.frame = (character.frame + 1) % character.frameCount;
				character.playerRect.x = character.playerRect.w * character.frame;
			}
		}

	if (character.isAttack)
	{
		if (character.countAttack == 1)
			character.playerRect.y = character.playerRect.h * 4;
		else
			character.playerRect.y = character.playerRect.h * 5;
		character.frameCount = 6;
		character.maxFrametime = 1000 / character.frameCount;
		character.currentFrametime += timer.dt;
		if (character.currentFrametime >= character.maxFrametime)
		{
			character.currentFrametime -= character.maxFrametime;
			character.frame = (character.frame + 1) % character.frameCount;
			character.playerRect.x = character.playerRect.w * character.frame;
		}
		else
			if (character.frame == character.frameCount)
				character.isAttack = false;
	}

	if (character.isUlt)
	{
		character.playerRect.y = character.playerRect.h * 6;
		character.frameCount = 9;
		character.maxFrametime = 1000 / character.frameCount;
		character.currentFrametime += timer.dt;
		if (character.currentFrametime >= character.maxFrametime)
		{
			character.currentFrametime -= character.maxFrametime;
			character.frame = (character.frame + 1) % character.frameCount;
			character.playerRect.x = character.playerRect.w * character.frame;
		}
		else
			if (character.frame == character.frameCount)
				character.isUlt = false;
	}
	if (character.direction == LEFT)
		SDL_RenderCopyExF(ren, character.playerTexture, &character.playerRect, &character.destinationRect, NULL, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopyF(ren, character.playerTexture, &character.playerRect, &character.destinationRect);
	//SDL_RenderDrawRectF(ren, &character.destinationRect);
	//SDL_RenderDrawRectF(ren, &character.playerHitbox);
}