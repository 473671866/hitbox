#pragma once

enum class attack_types : int			//攻击框类型
{
	normal = 0x0,					//普通攻击
	projectile = 0x1,				//飞行道具
	grasp = 0x2,					//投技
	force = 0x3,					//强制命中
	guard = 0x5,					//引发防御

	none = 0x9999
};

struct attack_boxs						//攻击框；每帧占用0x2C字节
{
	unsigned int frame;					//0x00
	unsigned int number;				//0x04；对应ATK编号
	unsigned int hit;					//0x08；所属Hit数
	float x;							//0x0C
	float y;							//0x10
	float w;							//0x14
	float h;							//0x18
	unsigned int flag;					//0x1C；bit 8在重拳/重脚的攻击框中表示这一帧为C投/D投的判定框
	char unknown[0xc];
};
static_assert(sizeof(attack_boxs) == 0x2C, "Size check");

struct attack_collections
{
	attack_types types;
	int level;				//招式等级
	int damage;				//伤害
	int minimum;			//最低伤害
	int penetrate;			//穿透伤害
	int stun;				//晕值
	int loss;				//破防
	int selfaddpower;		//
	int oppoaddpower;
	char fill[0x1A4];
};
static_assert(sizeof(attack_collections) == 0x1C8, "Size check");

struct attacks
{
	char unknown[0x20];
	attack_collections* atccs;
};
