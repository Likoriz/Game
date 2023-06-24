#include "Motion.h"
#include "Map.h"
#include "Basic.h"

Character character;

void Motion()
{
	float tmpx = character.x, tmpy = character.y;
	float tmpdstx = character.destinationRect.x, tmpdsty = character.destinationRect.y;

	character.isCanPass = true;
	float windSpeed = 0;

	if (character.isBlownAway)
		windSpeed = 50;

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

	if (tmpx + windSpeed * timer.dt / 1000 < (tile.dstTile.w * map.widthC - character.destinationRect.w))
		tmpx += windSpeed * timer.dt / 1000;

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

	character.isMoving = character.isUp || character.isDown || character.isRight || character.isLeft;

	character.playerHitbox.x = character.destinationRect.x + 45;
	character.playerHitbox.y = character.destinationRect.y + 109;
	character.playerHitbox.w = 40;
	character.playerHitbox.h = 19;

	for (int i = 0; i < hitbox.count; i++)
	{
		if (character.isLeft)
			if (character.playerHitbox.x >= hitbox.hitboxes[i].x
				&& character.playerHitbox.x <= (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w)
				&& (character.playerHitbox.y > hitbox.hitboxes[i].y || character.playerHitbox.y + character.playerHitbox.h > hitbox.hitboxes[i].y + 5)
				&& character.playerHitbox.y < (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h - 5))
			{
				character.isCanPass = false;
				break;
			}
		if (character.isUp)
			if ((character.playerHitbox.x > hitbox.hitboxes[i].x || character.playerHitbox.x + character.playerHitbox.w > hitbox.hitboxes[i].x + 5)
				&& character.playerHitbox.x < (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w - 5)
				&& character.playerHitbox.y >= hitbox.hitboxes[i].y
				&& character.playerHitbox.y <= (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h))
			{
				character.isCanPass = false;
				break;
			}

		if (character.isBlownAway && !character.isMoving)
			if ((character.playerHitbox.x + character.playerHitbox.w >= hitbox.hitboxes[i].x - 1
				&& character.playerHitbox.x + character.playerHitbox.w <= (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w)
				&& (character.playerHitbox.y > hitbox.hitboxes[i].y || character.playerHitbox.y + character.playerHitbox.h > hitbox.hitboxes[i].y + 5)
				&& character.playerHitbox.y < (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h - 5)))
			{
				character.isCanPass = false;
				break;
			}

		if (character.isRight)
			if ((character.playerHitbox.x + character.playerHitbox.w >= hitbox.hitboxes[i].x - 1
				&& character.playerHitbox.x + character.playerHitbox.w <= (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w)
				&& (character.playerHitbox.y > hitbox.hitboxes[i].y || character.playerHitbox.y + character.playerHitbox.h > hitbox.hitboxes[i].y + 5)
				&& character.playerHitbox.y < (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h - 5)))
			{
				character.isCanPass = false;
				break;
			}
		if (character.isDown)
		{
			if ((character.playerHitbox.x > hitbox.hitboxes[i].x || character.playerHitbox.x + character.playerHitbox.w > hitbox.hitboxes[i].x + 5)
				&& character.playerHitbox.x < (hitbox.hitboxes[i].x + hitbox.hitboxes[i].w - 5)
				&& character.playerHitbox.y + character.playerHitbox.h >= hitbox.hitboxes[i].y
				&& character.playerHitbox.y + character.playerHitbox.h <= (hitbox.hitboxes[i].y + hitbox.hitboxes[i].h))
			{
				character.isCanPass = false;
				break;
			}
		}
	}

	if (character.isCanPass)
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
}

void Animation()
{
	if (character.animationRestarted)
	{
		character.animationRestarted = false;
		character.animationState = USUAL;
		character.frame = 0;
	}

	if (character.attackClickThisFrame)
	{
		character.currentFrametime = 0;
		character.frame = 0;
	}

	if (character.isMoving)
		character.usualState = MOVE;
	else
		character.usualState = IDLE;

	if (character.animationState == ATTACK)
	{
		if (character.attackState == BASIC)
		{
			if (character.countAttack == 1)
				character.playerRect.y = character.playerRect.h * 4;
			else
				character.playerRect.y = character.playerRect.h * 5;
			character.frameCount = 6;
		}
		else
			if (character.attackState == ULT)
			{
				character.playerRect.y = character.playerRect.h * 6;
				character.frameCount = 10;
			}
	}
	else
		if (character.animationState == USUAL)
		{
			if (character.usualState == IDLE)
			{
				character.playerRect.y = 0;
				character.frameCount = 5;
			}
			else
				if (character.usualState == MOVE)
				{
					if (character.boostSpeed)
						character.playerRect.y = character.playerRect.h * 2;
					else
						character.playerRect.y = character.playerRect.h;
					character.frameCount = 8;
				}
		}

	character.maxFrametime = 1000 / character.frameCount;
	character.currentFrametime += timer.dt;

	if (character.currentFrametime >= character.maxFrametime)
	{
		character.currentFrametime = 0;
		character.frame = character.frame + 1;
		if (character.frame >= character.frameCount)
		{
			character.animationRestarted = true;
			if (character.animationState == ATTACK)
				character.frame--;
			else
				character.frame = 0;
		}
		character.playerRect.x = character.playerRect.w * character.frame;
	}

	if (character.direction == LEFT)
		SDL_RenderCopyExF(ren, character.playerTexture, &character.playerRect, &character.destinationRect, NULL, NULL, SDL_FLIP_HORIZONTAL);
	else
		SDL_RenderCopyF(ren, character.playerTexture, &character.playerRect, &character.destinationRect);
}