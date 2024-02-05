#pragma once

enum class body_types {
	none = 0x9999
};

struct body_boxs						//身位框结构；每帧占用0x2C字节
{
	unsigned int frame;					//0x00；帧数
	unsigned int _0x04;					//0x04
	unsigned int _0x08;					//0x08
	unsigned int _0x0C;					//0x0C
	unsigned int _0x10;					//0x10
	unsigned int _0x14;					//0x14
	unsigned int _0x18;					//0x18
	float x;							//0x1C
	float y;							//0x20
	float w;							//0x24
	float h;							//0x28
};
static_assert(sizeof(body_boxs) == 0x2C, "Size check");
