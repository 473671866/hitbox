#pragma once
#include <stdint.h>
#include "action.h"

_declspec(align(8))
struct object
{
	void** vftb;				//0x0
	char _0x8[0x30];			//0x8
	actions* acts;				//0x38
	char _0x40[0x28];			//0x40
	attacks* atcs;				//0x68
	char _0x70[0x30];			//0x70
	float x;					//0xa0
	float y;					//0xa4
	char _0xA8[0x34];			//0xa8
	float xoff;					//0xDC
	float yoff;					//0xE0
	char _0xE4[0x70];			//0xE4
	int toward;					//0x154：面向
	int _0x158;					//0x158
	int _0x15c;					//0x15c
	int _0x160;					//0x160
	int _0x164;					//0x164
	int number;					//0x168
	int _0x16c;					//0x16c
	int now;					//0x170: 正在执行帧数
	char _0x174[0x668];			//0x174
	int correctvalue;			//0x7DC
	char _0x7E0[0x4C];			//0x7E0
	int leadframe;				//0x82C
	char _0x830[0x28];			//0x830
	int avoidhit;				//0x858
	int avoidthrow;				//0x85C

	inline bool left() {
		return this->toward == 0;
	}
};

struct warpper {
	attack_types attack;
	affected_types affected;
	body_types body;

	warpper();
	warpper(attack_types types);
	warpper(affected_types types);
	warpper(body_types types);
	bool operator== (warpper b);
	bool operator!= (warpper b);
};

struct range {
	float left;
	float top;
	float right;
	float bottom;

	range();
	range(object* obj, attack_boxs box, bool left);
	range(object* obj, body_boxs box, bool left);
	range(object* obj, affected_boxs box, bool left);
};
