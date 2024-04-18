#pragma once
#include "Platform.h"
#include "Vector.h"

_declspec(align(16))
struct FTransform
{
	VectorRegister	Rotation;
	VectorRegister	Translation;
	VectorRegister	Scale3D;

	inline void Location(void* Ptr)
	{
		union { VectorRegister v; float f[4]; } Tmp;
		Tmp.v = Translation;
		float* FloatPtr = (float*)(Ptr);
		FloatPtr[0] = Tmp.f[0];
		FloatPtr[1] = Tmp.f[1];
		FloatPtr[2] = Tmp.f[2];
	}
};
