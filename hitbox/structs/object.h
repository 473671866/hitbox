#pragma once
#include <stdint.h>
#include "action.h"

_declspec(align(8))
struct object
{
	void** vtbl;				//0x0
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

struct wrappers {
	attack_types attack;
	affected_types affected;
	body_types body;

	wrappers() {}

	wrappers(attack_types types) :attack(types) {
		affected = affected_types::none;
		body = body_types::none;
	};
	wrappers(affected_types types) :affected(types) {
		attack = attack_types::none;
		body = body_types::none;
	};
	wrappers(body_types types) :body(types) {
		attack = attack_types::none;
		affected = affected_types::none;
	};

	bool operator== (wrappers w) {
		if (attack == w.attack)
			return true;
		else if (affected == w.affected)
			return true;
		else if (body == w.body)
			return true;
		else
			return false;
	}

	bool operator!= (wrappers w) {
		if (attack != w.attack)
			return true;
		else if (affected != w.affected)
			return true;
		else if (body != w.body)
			return true;
		else
			return false;
	}
};

struct rect {
	bool left;
	float x1;
	float y1;
	float x2;
	float y2;

	rect() {}

	rect(object* obj, attack_boxs box, bool left) {
		this->left = left;
		if (left) {
			this->x1 = obj->x * 10 + box.x * 10 + obj->xoff * 10;
			this->y1 = obj->y * 10 + box.y * 10 + obj->yoff * 10;
			this->x2 = x1 + box.w * 10;
			this->y2 = y1 - box.h * 10;
		}
		else {
			this->x1 = obj->x * 10 - box.x * 10 + obj->xoff * 10;
			this->y1 = obj->y * 10 + box.y * 10 + obj->yoff * 10;
			this->x2 = x1 - box.w * 10;
			this->y2 = y1 - box.h * 10;
		}
	}

	rect(object* obj, body_boxs box, bool left) {
		this->left = left;
		if (left) {
			this->x1 = obj->x * 10 + box.x * 10 + obj->xoff * 10;
			this->y1 = obj->y * 10 + box.y * 10 + obj->yoff * 10;
			this->x2 = x1 + box.w * 10;
			this->y2 = y1 - box.h * 10;
		}
		else {
			this->x1 = obj->x * 10 - box.x * 10 + obj->xoff * 10;
			this->y1 = obj->y * 10 + box.y * 10 + obj->yoff * 10;
			this->x2 = x1 - box.w * 10;
			this->y2 = y1 - box.h * 10;
		}
	}

	rect(object* obj, affected_boxs box, bool left) {
		this->left = left;
		if (box.path >= 0) {
			if (left) {
				this->x1 = obj->x * 10 + box.x * 10 + obj->xoff * 10;
				this->y1 = obj->y * 10 + box.y * 10 + obj->yoff * 10;
				this->x2 = x1 + box.w * 10;
				this->y2 = y1 - box.h * 10;
			}
			else {
				this->x1 = obj->x * 10 - box.x * 10 + obj->xoff * 10;
				this->y1 = obj->y * 10 + box.y * 10 + obj->yoff * 10;
				this->x2 = x1 - box.w * 10;
				this->y2 = y1 - box.h * 10;
			}
		}
		else {
			if (left) {
				this->x1 = obj->x * 10 + box.x * 10;
				this->y1 = obj->y * 10 + box.y * 10;
				this->x2 = x1 + box.w * 10;
				this->y2 = y1 - box.h * 10;
			}
			else {
				this->x1 = obj->x * 10 - box.x * 10;
				this->y1 = obj->y * 10 + box.y * 10;
				this->x2 = x1 - box.w * 10;
				this->y2 = y1 - box.h * 10;
			}
		}
	}
};
