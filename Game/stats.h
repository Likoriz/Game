#pragma once
#include "Basic.h"
#include "Menu.h"
const unsigned int num_of_items = 11;
struct Player
{
	unsigned char class_of_player;
	unsigned char hp;
	unsigned char stamina;
	unsigned char mod_weapon;
	unsigned char mod_ult;
	unsigned char mana;
	unsigned char lvl;
	unsigned int xp;
	unsigned int money;
	unsigned char inventory[num_of_items];
	unsigned char is_invincible;
	unsigned char debug;
};


//struct A
//{
//	int b;
//};

//struct C
//{
//	A gkdfgldfgldsg;
//};


struct Enemy
{
	unsigned char hp;
	unsigned char type;
	unsigned char immune;
	unsigned char atk;
};

