#pragma once
#include "Basic.h"

enum Direction { RIGHT = 1, LEFT = 2 };

enum questState { BREAD = 0, MONSTERS = 1, SEWERS = 2, BOSS = 3, END = 4 };

enum AnimationState { USUAL, ATTACK };
enum UsualState { IDLE, MOVE };
enum AttackState { BASIC, ULT };

struct Quests
{
	bool bread = false;
	bool monsters = false;
	bool sewers = false;
	bool boss = false;
	bool end = false;
};
extern Quests quest;

struct Environment
{
	SDL_Texture* darkness = NULL;
	SDL_Rect darkRect = {};
	SDL_FRect darkDst = {};
	bool isDark = false;

	SDL_Texture* mist = NULL;
	SDL_Rect mistRect = {};
	int enemies_list_DOT_amount_of_enemies_at_the_field = 0;
	int mistTimer = 0;
	bool isMisty = false;
};
extern Environment environment;

struct Character
{
	SDL_Rect playerRect;
	SDL_Texture* playerTexture = NULL;
	SDL_FRect destinationRect = {};
	SDL_FRect playerHitbox = {};

	float x = 150, y = 2000, speed = 150;// x=150, y=2000 // 2500 1500

	int frame = 0, frameCount = 0, currentFrametime = 0, maxFrametime = 0;
	bool isMoving = false;
	bool isCanPass = true;
	bool isBlownAway = false;

	bool isUp = false, isDown = false, isRight = false, isLeft = false;

	int direction = RIGHT;
	bool boostSpeed = false;

	int countAttack = 0;

	AnimationState animationState;
	AttackState attackState;
	UsualState usualState;
	bool attackClickThisFrame = false;
	bool animationRestarted = false;

	bool isEnchantress = false;
	bool isKnight = false;

	int quest = BREAD;
}; 
extern Character character;

struct GameState
{
	bool isGaming = true;
	bool isDialouge = false;
};
extern GameState state;

void Motion();
void Animation();