#pragma once
#include "TransformVectorized.h"

struct  USceneComponent
{
	char UnKnown[0x1b8];
	FTransform ComponentToWorld; //0x1c0
};
