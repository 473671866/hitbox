#pragma once
#include "Platform.h"
#include "NameTypes.h"

_declspec(align(8))
struct UObject
{
	void* VritualTable;	//0x0
	void* UnKnown1;		//0x8
	void* UnKnown2;		//0x10
	FName NamePrivate;	//0x18
	void* UnKnown3;		//0x20
	void* UnKnown4;		//0x28
};
