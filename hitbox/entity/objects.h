#pragma once
#include <stdint.h>
#include "object.h"
#include "props.h"

struct objects
{
	char _0x0[0x18];						//0x0
	object* p1;								//0x18
	object* p2;								//0x20
	char _0x28[0x10];						//0x28
	uint32_t complete;						//0x38
	char _00x3C[0x14];						//0x3C
	object* b1;								//0x50
	object* b2;								//0x58
	char _0x60[0x665F0];					//0x60
	projectile_header* props_list;			//0x66650
	char _0x66658[0x4fe8];
	uint32_t ready;
};
