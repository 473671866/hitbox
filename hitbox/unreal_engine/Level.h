#pragma once
#include "UObject.h"
#include "Array.h"
#include "World.h"
#include "AActor.h"

_declspec(align(8))
struct ULevel : public UObject
{
	char UnKnown1[0x68];			//0x30
	TArray<AActor*> Actors;			//0x98
};
