#pragma once

enum class affected_types :int
{
	normal = 0x1,							//受击框
	capture = 0x2,							//被投框
	guard = 0x3,							//防御框
	ground = 0x4,							//地面受击框
	negative = 0x5,							//抵消飞行道具框
	reflects = 0x6,							//反弹飞行道具框
	invulnerability = 0x7,					//霸体框
	parries = 0x8,							//当身框
	nothing = 0x9,							//飞行道具当身框
	parriesex = 0xA,						//投技当身框
	none = 0x9999
};

struct affected_boxs						//受击框结构；每帧占用0x2C字节
{
	unsigned int frame;						//0x00；帧数
	unsigned int _0x04;						//0x04
	affected_types types;					//0x08；受击框类型
	unsigned int flag;						//0x0C；Flag在不同类型的受击框中对应的功能不一样
	unsigned int _0x10;						//0x10
	unsigned int path;						//0x14
	unsigned int _0x18;						//0x18
	float x;								//0x1C
	float y;								//0x20
	float w;								//0x24
	float h;								//0x28
};
static_assert(sizeof(affected_boxs) == 0x2C, "Size check");
