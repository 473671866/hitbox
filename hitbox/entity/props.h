#pragma once
#include "action.h"

struct projectile
{
	char _0x0[0x38];			//0x0
	actions* acts;				//0x38
	char _0x40[0x28];			//0x40
	attacks* atcs;				//0x68
	char _0x68[0x30];			//0x70
	float x;					//0xa0
	float y;					//0xa4
	char unknown3[0xac];		//0xa8
	int toward;					//0x154：面向
	int _0x158;					//0x158
	int _0x15c;					//0x15c
	int _0x160;					//0x160
	int _0x164;					//0x164
	int number;					//0x168
	int _0x16c;					//0x16c
	int now;					//0x170: 正在执行帧数
};

struct projectile_list
{
	projectile_list* next;	//0x0
	void* hold;					//0x8
	projectile* props;		//0x10
};

struct projectile_header
{
	char hold[0x30];
	projectile_list* list;	//0x30
};
