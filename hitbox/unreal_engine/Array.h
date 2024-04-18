#pragma once
#include "Platform.h"

template<typename ElementType>
struct TArray
{
	ElementType* AllocatorInstance;
	int32		ArrayNum;
	int32       ArrayMax;
};
