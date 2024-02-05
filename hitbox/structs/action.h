#pragma once
#include "body.h"
#include "attack.h"
#include "affected.h"

enum class action_types : int
{
	body = 0x3,									//身位框；0x3
	affected = 0x4,								//受击框；0x4
	attack = 0x5,								//攻击框；0x5
};

struct action_collections						//ACT指针集
{
	unsigned int capacity;						//0x0 总帧数；指针指向内容总大小 = TotalFrame * 0x2C
	action_types types;							//0x4 ACT类型；决定指针指向的内容
	union
	{
		attack_boxs* attack;
		body_boxs* body;
		affected_boxs* affected;
	};
};
static_assert(sizeof(action_collections) == 0x10, "Size check");

struct actions_entry							//动作实体类
{
	void* _0x0;									//0x0
	int max;									//0x08；动作最大帧数
	int reset;									//0x0C；动作重置帧数
	void* _0x10;								//0x10
	void* _0x18;								//0x18
	int unknown4;								//0x20
	int capacity;								//0x24；ACT指针集内指针数
	action_collections* actcs;					//0x28；ACT指针集
};
static_assert(sizeof(actions_entry) == 0x30, "Size check");

struct actions									//动作集
{
	char _0x0[0x20];							//0x0
	actions_entry* entry;						//0x20
	void* hold;									//0x28
};
static_assert(sizeof(actions) == 0x30, "Size check");
