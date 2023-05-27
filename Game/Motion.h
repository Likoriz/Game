#pragma once
#include "Basic.h"

enum Direction { RIGHT = 1, LEFT = 2 };

struct Character
{
	SDL_Rect playerRect;
	SDL_Texture* playerTexture = NULL;
	SDL_FRect destinationRect = {};
	SDL_FRect playerHitbox = {};

	float x = 150, y = 2000, speed = 150;// x=150, y=2000 // 2500 1500

	int frame = 0, frameCount = 0, currentFrametime = 0, maxFrametime = 0;
	bool isMoving = false;

	bool isUp = false, isDown = false, isRight = false, isLeft = false;

	int direction = RIGHT;
	bool boostSpeed = false;
	//bool isAttack = false;
	int countAttack = 0;
	//bool isUlt = false;
	//bool isIdle = true;

	int animation = 0;
	int animationOld = 0;
	int animationNew = 0;

	bool isEnchantress = false;
	bool isKnight = false;
}; 
extern Character character;

enum StateAnimation { IDLE = 0, MOVING = 1, ATTACK = 2, ULT = 3 };

struct GameState
{
	bool isGaming = true;
	bool isDialouge = false;
};
extern GameState state;

void Motion();
void Animation();